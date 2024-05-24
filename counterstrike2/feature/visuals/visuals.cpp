// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "visuals.hpp"
#include "../../Logging.h"
#include "../../hooks/hooks.hpp"

#include "../../sdk/classes/c_grenade_trace.h"
#include <tinyformat/tinyformat.h>

void c_visuals::run_hit_capibara()
{
	if (!g_user->IsActive(xorstr_("misc_onshot_capsule"), xorstr_("misc_blur"), 1))
		return;

	m_mutex.lock();

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 54 24 10 55 53 56 41 55 48" );

	for (auto it = hit_capibara.begin(); it != hit_capibara.end();)
	{
		if (it->time < Interfaces::globals->global_storage.curtime)
		{
			it = hit_capibara.erase(it);
			continue;
		}

		std::uint8_t ptr[4];
		ptr[0] = 0xFF;
		ptr[1] = 0xFF;
		ptr[2] = 0xFF;
		ptr[3] = 0xFF;

		it->hitbox_data.hitbox_data = it->hitbox_data.hitbox_array;
		it->hitbox_position.hitbox_data = it->hitbox_position.hitbox_array;


		pattern.as<int* (_fastcall*)(scene_hitbox_data*, scene_hitbox_position*, c_scene_view_debug_overlays*, __int64, __int64, char, std::uint32_t*)>()(&it->hitbox_data, &it->hitbox_position, Interfaces::m_scene_view_debug_overlays, 0, 0, 1, (std::uint32_t*)ptr);
		it++;
	}
	m_mutex.unlock();
}

void c_visuals::run_removables() {
	if (!Interfaces::engine->is_connected() || !Interfaces::engine->is_in_game())
		return;
}

render_position RotateVertex2(const vector& p, const render_position& v, float angle) {
	// convert theta angle to sine and cosine representations.
	float c = std::cos(math::deg2rad(angle));
	float s = std::sin(math::deg2rad(angle));

	return {
		p.x + (v.x - p.x) * c - (v.y - p.y) * s,
		p.y + (v.x - p.x) * s + (v.y - p.y) * c
	};
}

std::pair<bool, std::array<render_position, 3>> create_arrow(c_cs_player_pawn* player) {

	vector view_origin, target_pos, delta;
	vector screen_pos, offscreen_pos;
	float  leeway_x, leeway_y, radius, offscreen_rotation;
	bool   is_on_screen;
	std::array<render_position, 3> verts;

	// todo - dex; move this?
	auto get_offscreen_data = [](const vector& delta, float radius, vector& out_offscreen_pos, float& out_rotation) {
		vector  view_angles(Interfaces::csgo_input->view_angle);
		vector fwd, right, up(0.f, 0.f, 1.f);
		float  front, side, yaw_rad, sa, ca;

		// get viewport angles forward directional vector.
		math::angle_vectors(view_angles, fwd);

		// convert viewangles forward directional vector to a unit vector.
		fwd.z = 0.f;
		fwd.normalize();

		// calculate front / side positions.
		right = up.cross(fwd);
		front = delta.dot(fwd);
		side = delta.dot(right);

		// setup offscreen position.
		out_offscreen_pos.x = radius * -side;
		out_offscreen_pos.y = radius * -front;

		// get the rotation ( yaw, 0 - 360 ).
		out_rotation = math::rad2deg(std::atan2(out_offscreen_pos.x, out_offscreen_pos.y) + math::get_pi());

		// get needed sine / cosine values.
		yaw_rad = math::deg2rad(-out_rotation);
		sa = std::sin(yaw_rad);
		ca = std::cos(yaw_rad);

		// rotate offscreen position around.
		out_offscreen_pos.x = (int)((g_cs2->screen.x / 2.f) + (radius * sa));
		out_offscreen_pos.y = (int)((g_cs2->screen.y / 2.f) - (radius * ca));
		};

	// get the player's center screen position.
	target_pos = player->game_scene_node()->abs_origin();
	is_on_screen = math::world_to_screen(target_pos, screen_pos);

	// give some extra room for screen position to be off screen.
	leeway_x = g_cs2->screen.x / 18.f;
	leeway_y = g_cs2->screen.y / 18.f;

	// origin is not on the screen at all, get offscreen position data and start rendering.
	if (!is_on_screen
		|| screen_pos.x < -leeway_x
		|| screen_pos.x >(g_cs2->screen.x + leeway_x)
		|| screen_pos.y < -leeway_y
		|| screen_pos.y >(g_cs2->screen.y + leeway_y)) {

		// get viewport origin.
		view_origin = g_cs2->local_player->game_scene_node()->abs_origin();

		// get direction to target.
		delta = (target_pos - view_origin).normalized();

		// note - dex; this is the 'YRES' macro from the source sdk.
		radius = 200.f * (g_cs2->screen.y / 480.f);

		// get the data we need for rendering.
		get_offscreen_data(delta, radius, offscreen_pos, offscreen_rotation);

		// bring rotation back into range... before rotating verts, sine and cosine needs this value inverted.
		// note - dex; reference: 
		// https://github.com/VSES/SourceEngine2007/blob/43a5c90a5ada1e69ca044595383be67f40b33c61/src_main/game/client/tf/tf_hud_damageindicator.cpp#L182
		offscreen_rotation = -offscreen_rotation;

		// setup vertices for the triangle.
		verts[0] = { offscreen_pos.x, offscreen_pos.y };        // 0,  0
		verts[1] = { offscreen_pos.x - 12.f, offscreen_pos.y + 24.f }; // -1, 1
		verts[2] = { offscreen_pos.x + 12.f, offscreen_pos.y + 24.f }; // 1,  1

		// rotate all vertices to point towards our target.
		verts[0] = RotateVertex2(offscreen_pos, verts[0], offscreen_rotation);
		verts[1] = RotateVertex2(offscreen_pos, verts[1], offscreen_rotation);
		verts[2] = RotateVertex2(offscreen_pos, verts[2], offscreen_rotation);
		return { true, verts };
	}

	return {};
}

std::array<skeleton_t, 128> get_skeleton(c_cs_player_pawn* player)
{
	auto game_scene = player->game_scene_node();
	if (!game_scene)
		return {};

	auto skeleton = game_scene->get_skeleton_instance();
	if (!skeleton)
		return {};

	auto& model_state = skeleton->m_modelState();
	auto& model = model_state.m_hModel();
	const auto num_bones = skeleton->get_bone_count();
	auto bones = skeleton->m_modelState().get_bone_data();

	if (!bones || num_bones <= 0)
		return {};

	auto delta_penisov = bones[4].pos - bones[5].pos;
	auto bone_penis_fix = bones[5].pos + delta_penisov * 0.5f;

	std::array<skeleton_t, 128> skeleton_data{};

	for (uint32_t i = 0; i < num_bones; i++) {
		if (!(model->bone_flags(i) & bone_flags::FLAG_HITBOX)) {
			continue;
		}

		auto parent_index = model->bone_parent(i);
		if (parent_index == -1)
			continue;

		auto child = bones[i].pos;
		auto parent = bones[parent_index].pos;

		if (parent_index == 7 || parent_index == 12)
			parent = bone_penis_fix;

		skeleton_data[i] = { child, parent };
	}

	return skeleton_data;
}

std::vector<std::string> get_flags(c_cs_player_pawn* player)
{
	std::vector<std::string> m_flags;
	if (g_visuals->m_flags[0])
	{
		if (player->has_c4())
		{
			m_flags.push_back(xorstr_("c4"));
		}
	}

	if (g_visuals->m_flags[1])
	{
		if (player->item_services()->m_has_defuser())
		{
			m_flags.push_back(xorstr_("kits"));
		}
	}

	if (g_visuals->m_flags[2])
	{
		if (player->armor_value() > 0)
		{
			if (player->item_services()->m_has_helmet())
				m_flags.push_back(xorstr_("HK"));
			else
				m_flags.push_back(xorstr_("H"));
		}
	}

	if (g_visuals->m_flags[3])
	{
		if (player->flash_duration() > 0)
		{
			m_flags.push_back(xorstr_("flashed"));
		}
	}

	if (g_visuals->m_flags[4])
	{
		if (player->weapon_services() && player->weapon_services()->weapon_owns_this_type(xorstr_("weapon_taser")))
		{
			m_flags.push_back(xorstr_("zeus"));
		}
	}

	if (g_visuals->m_flags[5])
	{
		if (player == g_visuals->defuser_bomb_pawn)
		{
			m_flags.push_back(xorstr_("defuser"));
		}
	}

	return m_flags;
}

void update_player(c_cs_player_pawn* player, c_player_storage& player_storage) {
	if (!player->is_alive())
	{
		player_storage.is_dead = true;
		return;
	}

	if (!player->get_weapon_active())
		return;

	if (!player->get_controller())
		return;

	if (!player->get_controller()->name())
		return;

	if (!player->game_scene_node())
		return;

	if (!player->collision_property())
		return;

	player_storage.is_invalid = false;

	if ((player->flags() & 0x10) == 0)
		g_misc->setup_avatar(player);

	box_t box = { };

	player_storage.is_dead = false;

	player_storage.abs_origin = player->game_scene_node()->abs_origin();
	player_storage.mins = player->collision_property()->mins();
	player_storage.maxs = player->collision_property()->maxs();

	player_storage.username = player->get_controller()->name();
	player_storage.steamid = player->get_controller()->steam_id();
	player_storage.health = player->health();
	player_storage.m_arrow = create_arrow(player);

	if (player->get_weapon_active()->attribute_manager() && player->get_weapon_active()->attribute_manager()->item() && player->get_weapon_active()->attribute_manager()->item()->static_data()) {
		player_storage.weapon_name = Interfaces::m_localize->find_safe(player->get_weapon_active()->attribute_manager()->item()->static_data()->item_base_name);
		player_storage.item_index = player->get_weapon_active()->get_econ_view_item()->item_index();
	}

	player_storage.m_skeleton = get_skeleton(player);
	player_storage.m_flags = get_flags(player);
}

void c_visuals::update(int stage) {

	if (stage != frame_net_update_end)
		return;

	auto penis = g_cs2->get_localplayer();

	m_mutex.lock();

	for (auto it = m_players.begin(); it != m_players.end();)
	{
		auto player = Interfaces::entity_list->get_entity(it->handle & 0x7FFF);

		if (!player || !player->is_player() || !player->is_enemy(penis)) {
			it = m_players.erase(it);
			continue;
		}

		it++;
	}

	for (auto it = m_dropped_weapons.begin(); it != m_dropped_weapons.end();)
	{
		auto player = Interfaces::entity_list->get_entity(it->handle & 0x7FFF);

		if (!player || !player->find_class(HASH("C_BasePlayerWeapon")) || player->owner_handle().is_valid()) {
			it = m_dropped_weapons.erase(it);
			continue;
		}

		it++;
	}

	for (int i{}; i <= Interfaces::entity_list->get_highest_entity_index(); i++) {

		auto player = Interfaces::entity_list->get_entity(i);

		if (!player)
			continue;

		if (!player->find_class(HASH("C_CSPlayerPawn")))
			continue;

		if (!player->is_enemy(penis))
			continue;

		auto handle = g_cs2->get_handle_entity(player);

		auto player_ = std::find_if(m_players.begin(), m_players.end(), [handle](c_player_storage& x) {
			return x.handle == handle;
			});

		if (player_ == m_players.end()) {
			auto& player_storage = m_players.emplace_back();
			player_storage.handle = handle;
			update_player(player, player_storage);
		}
		else {
			player_->m_arrow.first = false;
			player_->m_arrow.second.fill({});
			update_player(player, *player_);
		}
	}

	for (int i{}; i <= Interfaces::entity_list->get_highest_entity_index(); i++) {
		auto entity = Interfaces::entity_list->get_entity(i);

		if (!entity)
			continue;

		if (!entity->find_class(HASH("C_BasePlayerWeapon")))
			continue;

		if (!entity->game_scene_node())
			continue;

		if (entity->owner_handle().is_valid())
			continue;

		auto handle = g_cs2->get_handle_entity(entity);

		auto find = std::find_if(m_dropped_weapons.begin(), m_dropped_weapons.end(), [handle](c_dropped_weapons x) {
			return x.handle == handle;
			});

		if (find != m_dropped_weapons.end())
		{
			auto& weapon = *find;
			weapon.handle = handle;
			weapon.abs_origin = entity->game_scene_node()->abs_origin();
			weapon.mins = entity->collision_property()->mins();
			weapon.maxs = entity->collision_property()->maxs();

			auto weapon_ = (c_weapon_cs_base*)(entity);

			if (weapon_->attribute_manager() && weapon_->attribute_manager()->item() && weapon_->attribute_manager()->item()->static_data()) {
				weapon.weapon_name = Interfaces::m_localize->find_safe(weapon_->attribute_manager()->item()->static_data()->item_base_name);
				weapon.item_index = weapon_->get_econ_view_item()->item_index();
			}
		}
		else
		{
			auto& weapon = m_dropped_weapons.emplace_back();
			weapon.handle = handle;
			weapon.abs_origin = entity->game_scene_node()->abs_origin();
			weapon.mins = entity->collision_property()->mins();
			weapon.maxs = entity->collision_property()->maxs();

			auto weapon_ = (c_weapon_cs_base*)(entity);

			if (weapon_->attribute_manager() && weapon_->attribute_manager()->item() && weapon_->attribute_manager()->item()->static_data()) {
				weapon.weapon_name = Interfaces::m_localize->find_safe(weapon_->attribute_manager()->item()->static_data()->item_base_name);
				weapon.item_index = weapon_->get_econ_view_item()->item_index();
			}
		}
	}

	m_mutex.unlock();
}

void c_visuals::update_damage()
{
	m_damage_mutex.lock();

	for (int i = 0; i < m_damage_marker.size(); i++) {
		m_damage_marker[i].is_world_screen = math::world_to_screen(m_damage_marker[i].position, m_damage_marker[i].world_position);
	}

	m_damage_mutex.unlock();
}

void c_visuals::add_damage(std::string damage, vector position)
{
	m_damage_mutex.lock();
	m_damage_marker.push_back(c_damage_marker(damage, position, Interfaces::globals->global_storage.curtime + 4.f));
	m_damage_mutex.unlock();
}

void c_visuals::render_damage()
{
	if (!g_user->IsActive(xorstr_("misc_hitmarker"), xorstr_("misc_hitmarker"), 0))
		return;

	m_damage_mutex.lock();

	for (int i = 0; i < m_damage_marker.size(); i++) {

		if (Interfaces::m_network_game_service && Interfaces::m_network_game_service->get_network_game_client() && Interfaces::m_network_game_service->get_network_game_client()->global_vars.global_storage.curtime >= m_damage_marker[i].time)
			m_damage_marker[i].time = 0.f;

		if (!m_damage_marker[i].is_world_screen)
			continue;

		m_damage_marker[i].animation.run(m_damage_marker[i].time > 0.f, 0.25);
		m_damage_marker[i].animation2.run(m_damage_marker[i].time > 0.f, 2.f);

		g_render->add_text(m_damage_marker[i].damage, render_position(m_damage_marker[i].world_position.x, m_damage_marker[i].world_position.y - (22.f * m_damage_marker[i].animation2.base)), render_color::white().override_alpha(m_damage_marker[i].animation.base), g_render->get_font(6), 11);

	}

	m_damage_mutex.unlock();
}