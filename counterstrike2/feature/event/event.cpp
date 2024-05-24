// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "event.h"

#include "../../utilities/utilities.hpp"
#include "../../sdk/sdk.hpp"
#include "../../sdk/math/math.hpp"
#include "../../Logging.h"
#include <tinyformat/tinyformat.h>
#include "../feature.hpp"
#include "../../utilities/channel_system.h"
#include "../misc/hitsound.h"
#include "../feature/misc/hitmarker.h"
#include "../inventory_changer/inventory_changer.h"

void penis(c_cs_player_pawn* entity)
{
	if (!g_user->IsActive(xorstr_("misc_onshot_capsule"), xorstr_("misc_blur"),1))
		return;

	auto skeleton = entity->get_skeleton();

	if (skeleton)
	{

		auto model = skeleton->get_model();

		if (model)
		{
			scene_hitbox_data hitbox_data_;
			scene_hitbox_position hitbox_position_;
			hitbox_data_.hitbox_count = hitbox_position_.hitbox_count = 19;

			for (int i{}; i < 19; i++)
			{
				auto hitbox_data = model->get_hitbox(i);

				if (!hitbox_data)
					continue;

				skeleton->calc_world_space_bones(FLAG_HITBOX);

				auto bone_index = entity->get_bone_index(hitbox_data->m_name);

				auto bone_data = skeleton->m_modelState().get_bone_data()[bone_index];

				hitbox_data_.hitbox_array[i].hitbox = hitbox_data;
				hitbox_position_.hitbox_array[i].position = bone_data.pos;
				hitbox_position_.hitbox_array[i].scale = bone_data.scale;
				hitbox_position_.hitbox_array[i].rotate = bone_data.rot;
			}

			clr_t clr;
			clr.r = 0xFF;
			clr.g = 0xFF;
			clr.b = 0xFF;
			clr.a = 0xFF;

			hit_t hit_temp;
			hit_temp.time = Interfaces::globals->global_storage.curtime + 4.f;
			hit_temp.hitbox_data = hitbox_data_;
			hit_temp.hitbox_position = hitbox_position_;
			hit_temp.clr = clr;

			
			g_visuals->m_mutex.lock();
			g_visuals->hit_capibara.push_back(hit_temp);
			g_visuals->m_mutex.unlock();
		}
	}
}

void c_event::initilization() {
	Interfaces::event_manager->add_listeners(this, xorstr_("player_hurt"), false);
	Interfaces::event_manager->add_listeners(this, xorstr_("player_death"), false);
	Interfaces::event_manager->add_listeners(this, xorstr_("add_bullet_hit_marker"), false);
	Interfaces::event_manager->add_listeners(this, xorstr_("bullet_impact"), false);
	Interfaces::event_manager->add_listeners(this, xorstr_("round_start"), false);
	Interfaces::event_manager->add_listeners(this, xorstr_("weapon_fire"), false);
}

std::string get_hitgroup(int hitgroup)
{
	switch (hitgroup)
	{
	case e_hitgroups::hitgroup_head:
		return "head";
	case e_hitgroups::hitgroup_chest:
		return "chest";
	case e_hitgroups::hitgroup_generic:
		return "generic";
	case e_hitgroups::hitgroup_leftarm:
	case e_hitgroups::hitgroup_rightarm:
		return "arms";
	case e_hitgroups::hitgroup_neck:
		return "neck";
	case e_hitgroups::hitgroup_leftleg:
	case e_hitgroups::hitgroup_rightleg:
		return "legs";
	case e_hitgroups::hitgroup_stomach:
		return "stomach";
	}

	return "unknown";
}

void c_event::player_hurt(c_game_event* event)
{
	add_trace(__PRETTY_FUNCTION__);
	auto player = event->get_event_helper().get_player_controller();
	auto attacker = event->get_event_helper().get_attacker_controller();

	if (!player || !attacker)
		return;

	if (!player->is_controller() || !attacker->is_controller())
		return;

	if (!attacker->is_local_player_controller())
		return;

	if (player->is_local_player_controller())
		return;

	auto damage = event->get_event_helper().get_damage();

	if (damage < 1)
		return;

	auto hitbox = event->get_int2(xorstr_("hitgroup"), false);

	penis(player->get_player_pawn());

	auto skeleton = player->get_player_pawn()->get_skeleton();

	if (skeleton)
	{
		auto model = skeleton->get_model();

		if (model)
		{
			for (int i{}; i < 19; i++)
			{
				auto hitbox_data = model->get_hitbox(i);

				if (!hitbox_data)
					continue;

				if (hitbox_data->m_nGroupId == hitbox)
				{
					auto bone_index = player->get_player_pawn()->get_bone_index(hitbox_data->m_name);
					if (g_user->IsActive(xorstr_("misc_hitmarker"), xorstr_("misc_hitmarker"), 0))
						g_hitmarker->add(skeleton->m_modelState().get_bone_data()[bone_index].pos);

					g_visuals->add_damage(std::to_string(damage), skeleton->m_modelState().get_bone_data()[bone_index].pos);
					break;
				}
			}
		}
	}

	if (g_user->IsActive(xorstr_("misc_hitsound"), xorstr_("misc_hitsound"), 0))
		g_hitsounds->run();

	//g_notify->add(tfm::format(xorstr_("hit %s in hitbox for %d dmg"), player->name(), damage));
	if (g_channel_system->is_enable(g_channel_system->weave_channel))
		g_channel_system->add_log(g_channel_system->weave_channel, tfm::format(xorstr_("hit %s in %s for %d dmg"), player->name(), get_hitgroup(hitbox), damage).c_str());
}

void c_event::player_harmed(c_game_event* event)
{
	add_trace(__PRETTY_FUNCTION__);
	auto player = event->get_event_helper().get_player_controller();
	auto attacker = event->get_event_helper().get_attacker_controller();

	if (!player || !attacker)
		return;

	if (!player->is_controller() || !attacker->is_controller())
		return;

	if (!player->is_local_player_controller() || attacker->is_local_player_controller())
		return;

	if (event->get_event_helper().get_damage() < 1)
		return;

}

void c_event::player_death(c_game_event* event)
{
	add_trace(__PRETTY_FUNCTION__);
	auto player = event->get_event_helper().get_player_controller();
	auto attacker = event->get_event_helper().get_attacker_controller();

	if (!player || !attacker)
		return;

	if (!player->is_controller() || !attacker->is_controller())
		return;

	if (player == g_cs2->local_player->get_controller())
		g_cs2->m_should_clear_notice = true;

	if (!attacker->is_local_player_controller())
		return;
}

void c_event::bullet_impact(c_game_event* event)
{
	add_trace(__PRETTY_FUNCTION__);
	auto player = event->get_event_helper().get_player_controller();
	auto position = vector(event->get_float2(xorstr_("x"), 0), event->get_float2(xorstr_("y"), 0), event->get_float2(xorstr_("z"), 0));

	if (!player)
		return;

	if (!player->is_controller())
		return;

	if (!player->is_local_player_controller())
	{
		if (player->get_player_pawn() && player->get_player_pawn()->is_enemy() && g_user->IsActive(xorstr_("misc_bullet_trace_enemy"), xorstr_("misc_bullet_trace_enemy"), 0) && player->get_player_pawn()->weapon_services())
			g_misc->add_bullet_trace(player->get_player_pawn()->weapon_services()->get_shoot_pos(), position, color_t(g_user->GetConfig()[xorstr_("misc_bullet_trace_enemy_color")]));
		return;
	}

	if (g_user->IsActive(xorstr_("misc_bullet_trace"), xorstr_("misc_bullet_trace"), 0))
		g_misc->add_bullet_trace(g_cs2->eye_position, position, color_t(g_user->GetConfig()[xorstr_("misc_bullet_trace_color")]));

	if (g_user->IsActive(xorstr_("misc_server_impact"), xorstr_("misc_server_impact"), 0))
		Interfaces::client->get_scene_debug_overlay()->add_box(position, vector(-2, -2, -2), vector(2, 2, 2), vector(), color_t(0, 0, 255, 127));
}

void weapon_fire(c_game_event* event) {
	auto player = event->get_event_helper().get_player_controller();

	if (!player)
		return;

	if (!player->is_controller())
		return;

	if (!player->is_local_player_controller())
		return;

	if (g_cs2->rapid_fire_shoots > 0) {
		g_cs2->rapid_fire_shoots--;
		g_cs2->start_time = Interfaces::globals->global_storage.curtime + g_cs2->cycle_time;
	}
}

void c_event::fire_game_event(c_game_event* event) {
	if (!Interfaces::engine->is_in_game() || !event)
		return;

	std::string name = event->get_name();

	if (name.find("player_hurt") != std::string::npos)
	{
		player_hurt(event);
		player_harmed(event);
	}

	if (name.find("weapon_fire") != std::string::npos) {
		weapon_fire(event);
	}

	if (name.find("player_death") != std::string::npos)
		player_death(event);

	if (name.find("bullet_impact") != std::string::npos)
		bullet_impact(event);

	if (name.find("round_start") != std::string::npos) {
		g_cs2->on_round = true;
		g_inventory_changer->force_update = true;
		g_cs2->m_should_clear_notice = true;
		g_visuals->hit_capibara.clear();
	}
}