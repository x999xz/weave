// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "ragebot.hpp"
#include <format>
#include "../../Logging.h"
#include <tinyformat/tinyformat.h>

void c_rage_bot::update_cache() {

	m_mutex.lock();

	for (auto it = m_players.begin(); it != m_players.end();)
	{
		auto& handle = it->handle;
		auto player = Interfaces::entity_list->get_entity(it->handle.get_index());
		if (!it->handle.is_valid() || !player || !player->find_class(HASH("C_CSPlayerPawn")) || player != it->pawn || !player->is_alive() || !player->is_enemy())
		{
			it = m_players.erase(it);
			continue;
		}

		it++;
	}


	for (int i{}; i < 65; i++) {
		auto controller = Interfaces::entity_list->get_controller(i);

		if (!controller || !controller->find_class(HASH("CCSPlayerController")))
			continue;

		auto player = controller->get_player_pawn();

		if (!player || !player->find_class(HASH("C_CSPlayerPawn")))
			continue;

		if (!player->is_alive())
			continue;

		if (!player->is_enemy())
			continue;

		auto handle = controller->handle_player_pawn();

		auto element = std::find_if(m_players.begin(), m_players.end(), [&handle](c_player_cache x) {
			return x.handle.get_handle() == handle.get_handle();
			});

		if (element != m_players.end())
			continue;

		m_players.emplace_back(handle, player);
	}

	m_mutex.unlock();
}

void c_rage_bot::setup_config()
{
	m_config.autostop = g_user->IsActive(tfm::format(xorstr_("ragebot_autostop_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_autostop_%d"), g_cs2->m_current_group),0);
	m_config.beetwen = g_user->IsActive(tfm::format(xorstr_("ragebot_autostop_beetwen_shots_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_autostop_beetwen_shots_%d"), g_cs2->m_current_group),0);
	m_config.accuracy = g_user->IsActive(tfm::format(xorstr_("ragebot_autostop_accuracy_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_autostop_beetwen_shots_%d"), g_cs2->m_current_group),1);
	m_config.molotov = g_user->IsActive(tfm::format(xorstr_("ragebot_autostop_molotov_ignore_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_autostop_beetwen_shots_%d"), g_cs2->m_current_group),2);
	m_config.damage = g_user->IsActive(tfm::format(xorstr_("ragebot_damage_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_damage_%d"), g_cs2->m_current_group),0);
	m_config.m_head = g_user->IsActive(tfm::format(xorstr_("ragebot_hitbox_head_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_hitbox_head_%d"), g_cs2->m_current_group),0);
	m_config.m_chest = g_user->IsActive(tfm::format(xorstr_("ragebot_hitbox_chest_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_hitbox_head_%d"), g_cs2->m_current_group),1);
	m_config.m_stomach = g_user->IsActive(tfm::format(xorstr_("ragebot_hitbox_stomach_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_hitbox_head_%d"), g_cs2->m_current_group),2);
	m_config.m_arms = g_user->IsActive(tfm::format(xorstr_("ragebot_hitbox_arms_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_hitbox_head_%d"), g_cs2->m_current_group),3);
	m_config.m_legs = g_user->IsActive(tfm::format(xorstr_("ragebot_hitbox_legs_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_hitbox_head_%d"), g_cs2->m_current_group),4);
	m_config.m_feet = g_user->IsActive(tfm::format(xorstr_("ragebot_hitbox_foot_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_hitbox_head_%d"), g_cs2->m_current_group),5);
	m_config.m_head2 = g_user->IsActive(tfm::format(xorstr_("ragebot_multipoint_head_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_multipoint_head_%d"), g_cs2->m_current_group),0);
	m_config.m_chest2 = g_user->IsActive(tfm::format(xorstr_("ragebot_multipoint_chest_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_multipoint_head_%d"), g_cs2->m_current_group),1);
	m_config.m_stomach2 = g_user->IsActive(tfm::format(xorstr_("ragebot_multipoint_stomach_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_multipoint_head_%d"), g_cs2->m_current_group),2);
	m_config.m_arms2 = g_user->IsActive(tfm::format(xorstr_("ragebot_multipoint_arms_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_multipoint_head_%d"), g_cs2->m_current_group),3);
	m_config.m_legs2 = g_user->IsActive(tfm::format(xorstr_("ragebot_multipoint_legs_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_multipoint_head_%d"), g_cs2->m_current_group),4);
	m_config.m_feet2 = g_user->IsActive(tfm::format(xorstr_("ragebot_multipoint_foot_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_multipoint_head_%d"), g_cs2->m_current_group),5);
	m_config.point_scale = g_user->IsActive(tfm::format(xorstr_("ragebot_multipoint_scale_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_multipoint_scale_%d"), g_cs2->m_current_group),0) / 100.f;
	m_config.hitchance = g_user->IsActive(tfm::format(xorstr_("ragebot_hitchance_amount_%d"), g_cs2->m_current_group), tfm::format(xorstr_("ragebot_hitchance_amount_%d"), g_cs2->m_current_group),0);
	m_config.penetration = g_user->IsActive(xorstr_("ragebot_penetration"), xorstr_("ragebot_penetration"),0);
	m_config.no_spread = g_user->IsActive(xorstr_("ragebot_nospread"), xorstr_("ragebot_nospread"),0);
	m_config.auto_fire = g_user->IsActive(xorstr_("ragebot_auto_fire"), xorstr_("ragebot_auto_fire"),0);
	m_config.silent = g_user->IsActive(xorstr_("ragebot_auto_silent"), xorstr_("ragebot_auto_silent"),0);
	m_config.hide_shot = g_user->IsActive(xorstr_("ragebot_hideshots"), xorstr_("ragebot_hideshots"),0);
	m_config.enabled = g_user->IsActive(xorstr_("ragebot_enable"), xorstr_("ragebot_enable"),0);
	m_config.scope = g_user->IsActive(xorstr_("ragebot_auto_scope"), xorstr_("ragebot_auto_scope"),0);
}

void c_rage_bot::revolver_cock(c_user_cmd* cmd) const {
	if (!g_cs2->local_player)
	if (!g_cs2->local_player)
		return;

	if (!g_cs2->local_player->get_weapon_active())
		return;

	auto weapon = g_cs2->local_player->get_weapon_active();

	auto base = weapon->get_weapon_base();

	auto econ_item_view = weapon->get_econ_view_item();

	if (!econ_item_view)
		return;

	if (econ_item_view->item_index() != weapon_revolver)
		return;

	if (bool valid_revolver = !(cmd->buttons.buttonstate[0] & InputBitMask_t::IN_RELOAD) && !(cmd->buttons.buttonstate[0] & InputBitMask_t::IN_ATTACK) && weapon->clip1(); !valid_revolver)
		return;

	if (base->m_nPostponeFireReadyTicks() > cmd->base->tick_count) {
		if (cmd->base->tick_count > next_cock_time && g_cs2->local_player->get_weapon_active()->next_primary_attack_tick() <= cmd->base->tick_count) {
			cmd->buttons.buttonstate[0] |= IN_ATTACK;
		}
	}
	else {
		g_ragebot->next_cock_time = cmd->base->tick_count + int(0.25f * 64.f);
	}
}

bool c_rage_bot::can_shoot(int tick) const
{
	add_trace(__PRETTY_FUNCTION__);

	if (!g_cs2->local_player)
		return false;

	if (!g_cs2->local_player->get_controller())
		return false;

	if (!g_cs2->local_player->get_weapon_active())
		return false;

	auto service = g_cs2->local_player->weapon_services();

	if (!service)
		return false;

	auto econ_item_view = g_cs2->local_player->get_weapon_active()->get_econ_view_item();

	if (!econ_item_view)
		return false;

	auto base = g_cs2->local_player->get_weapon_active()->get_weapon_base();

	if (!base->clip1())
		return false;

	if (g_cs2->local_player->m_bWaitForNoAttack())
		return false;

	if (g_cs2->local_player->get_weapon_active()->next_primary_attack_tick() > tick)
		return false;

	return true;
}

unsigned int get_hash_seed(c_cs_player_pawn* player, vector angle, int attack_tick)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 81 EC F8 00 00 00 F3 0F 10 0A" );
	return g_cs2->m_patterns[FNV32("get_hash_seed")].as<unsigned int(__fastcall*)(c_cs_player_pawn*, vector, int)>()(player, angle, attack_tick);
}

void get_spread_pattern(unsigned short item_index, int bullets, int recoil_index, float* r3, float* r4)
{
	static auto pattern2 = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 05 ?? ?? ?? ?? 48 8D 3C CD 00 00 00 00 48 03 D7 48 8D 4C 24 30 FF D0 84 C0 74 12 66 3B DE 74 4A" ).get_absolute_address(3, 0); 
	static auto pattern3 = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "66 89 54 24 10 55 48" );

	auto pattern = pattern2.as<std::uintptr_t*>();
	auto func = *reinterpret_cast<std::uintptr_t**>(pattern);

	pattern3.as<void(__fastcall*)(std::uintptr_t*, unsigned short, std::uintptr_t*, int, float*, float*)>()(pattern, item_index, nullptr, bullets * recoil_index, r3, r4);
}

vector c_rage_bot::calculate_spread(unsigned int index, int bullets, float accuracy, float spread, unsigned short item_index, int recoil_index)
{
	add_trace(__PRETTY_FUNCTION__);
	vector spread_;

	g_utils->random_seed(index + 1);

	float r1 = g_utils->random_float(0.0f, 1.0f);
	float r2 = g_utils->random_float(0.0f, 6.2831855f);

	float r3{};
	float r4{};
	float c1{};
	float c2{};
	float s1{};
	float s2{};

	if (g_cs2->weapon_accuracy_shotgun_spread_patterns->GetValue<bool>())
	{
		get_spread_pattern(item_index, bullets, recoil_index, &r3, &r4);
	}
	else
	{
		r3 = r1;
		r4 = r2;
	}

	if (item_index == weapon_revolver)
	{
		r1 = 1.f - (r1 * r1);
		r3 = 1.f - (r3 * r3);
	}
	else if (item_index == weapon_negev && recoil_index < 3)
	{
		for (int i{ 3 }; i > recoil_index; --i) {
			r1 *= r1;
			r3 *= r3;
		}

		r1 = 1.f - r1;
		r3 = 1.f - r3;
	}

	// get needed sine / cosine values.
	c1 = std::cosf(r2);
	c2 = std::cosf(r4);
	s1 = std::sinf(r2);
	s2 = std::sinf(r4);

	float acc = r1 * accuracy;
	float sp = r3 * spread;

	return {
		(c1 * acc) + (c2 * sp),
		(s1 * acc) + (s2 * sp),
		0.f
	};
}

float c_rage_bot::get_max_speed() const
{
	if (!g_cs2->local_player)
		return 260.f;

	if (!g_cs2->local_player->is_alive())
		return 260.f;

	auto movement = g_cs2->local_player->movement_services();

	if (!movement)
		return 260.f;

	auto max_speed = movement->m_max_speed();

	if (g_cs2->local_player->get_weapon_active() && g_cs2->local_player->get_weapon_active()->get_weapon_data())
		max_speed = g_cs2->local_player->get_weapon_active()->get_weapon_data()->max_speed();

	return max_speed;
}

bool c_rage_bot::auto_stop(c_user_cmd* cmd)
{
	add_trace(__PRETTY_FUNCTION__);
	if (!(g_cs2->local_player->flags() & fl_onground))
		return false;

	if (!g_cs2->local_player->movement_services())
		return false;

	if (g_cs2->m_current_group == -1)
		return false;

	if (m_config.no_spread)
		return true;

	if (!m_config.autostop)
		return false;

	//if (!can_shoot() && !m_config.autostop_options.empty() && !m_config.autostop_options[0])
	//	return false;

	if (!m_auto_stop)
		return false;

	if (!cmd || !cmd->base)
		return false;

	vector velocity = g_cs2->local_player->velocity();

	float max_speed = get_max_speed() * 0.2f;
	float speed = std::fabsf(g_cs2->local_player->speed_move());

	auto newspeed = speed - ((speed * 0.17f) * g_cs2->sv_friction->GetValue<float>()) * g_cs2->local_player->movement_services()->m_flSurfaceFriction();
	auto max_accelspeed = fabsf((0.17f * g_cs2->local_player->movement_services()->m_flSurfaceFriction()) * (get_max_speed() * g_cs2->sv_accelerate->GetValue<float>()));
	auto accelspeed = fabsf(fminf((0.17f * g_cs2->local_player->movement_services()->m_flSurfaceFriction()) * ((speed * 0.8f) * g_cs2->sv_accelerate->GetValue<float>()),
		(speed * 0.8f) - newspeed));

	auto new_speed = max_accelspeed / accelspeed;
	new_speed *= Interfaces::globals->interval_per_ticks; // interval per subtick

	if (speed <= max_speed)
	{
		g_movement->clamp_movement(max_speed);
	}
	else
	{
		vector angle;
		math::vector_angles(g_cs2->local_player->velocity(), angle);

		float speed = g_cs2->local_player->velocity().length_2d();

		angle.y = g_cs2->angle.y - angle.y;

		vector direction;
		math::angle_vectors(angle, direction);

		vector stop = direction * -speed;

		if (speed > 13.f)
		{
			cmd->base->forwardmove = stop.x * new_speed;
			cmd->base->sidemove = stop.y * new_speed;
		}
		else
		{
			cmd->base->forwardmove = 0.f;
			cmd->base->sidemove = 0.f;
		}
	}

	return true;
}

int /*CounterStrikeGlobalOffensive::Client::*/HitboxToHitgroup(int hitbox)
{
	if (hitbox == hitbox_head)
		return e_hitgroups::hitgroup_head;
	else if (hitbox == hitbox_stomach || hitbox == hitbox_pelvis)
		return e_hitgroups::hitgroup_stomach;
	else if (hitbox >= hitbox_chest && hitbox <= hitbox_upper_chest)
		return e_hitgroups::hitgroup_chest;
	else if (hitbox == hitbox_left_upper_arm || hitbox == hitbox_left_forearm || hitbox == hitbox_left_hand)
		return e_hitgroups::hitgroup_leftarm;
	else if (hitbox == hitbox_right_forearm || hitbox == hitbox_right_upper_arm || hitbox == hitbox_right_hand)
		return e_hitgroups::hitgroup_rightarm;
	else if (hitbox == hitbox_neck)
		return e_hitgroups::hitgroup_neck;
	else if (hitbox == hitbox_left_foot || hitbox == hitbox_left_calf || hitbox == hitbox_left_thigh)
		return e_hitgroups::hitgroup_leftleg;
	else if (hitbox == hitbox_right_foot || hitbox == hitbox_right_calf || hitbox == hitbox_right_thigh)
		return e_hitgroups::hitgroup_rightleg;
	else
		return e_hitgroups::hitgroup_generic;
}

void c_rage_bot::setup_hitboxes(c_cs_player_pawn* pawn)
{
	add_trace(__PRETTY_FUNCTION__);
	m_hitboxes.clear();

	auto active_weapon = g_cs2->local_player->get_weapon_active();

	if (!active_weapon)
		return;

	auto weapon_data = active_weapon->get_weapon_data();

	if (!weapon_data)
		return;

	for (int i{}; i < hitbox_max; i++)
	{
		if (i == hitbox_neck)
			continue;
		float scaled_damage = weapon_data->damage(); 

		g_firebullet->scale_damage(HitboxToHitgroup(i), pawn, weapon_data, scaled_damage);

		if (scaled_damage >= std::min(pawn->health(), m_config.damage))
			m_hitboxes.push_back((e_hitboxes)i);
	}

	for (auto it = m_hitboxes.begin(); it != m_hitboxes.end();)
	{
		int hitbox = *it;
		if (!m_config.m_head && hitbox == hitbox_head)
		{
			it = m_hitboxes.erase(it);
			continue;
		}

		if (!m_config.m_chest && HitboxToHitgroup(hitbox) == e_hitgroups::hitgroup_chest)
		{
			it = m_hitboxes.erase(it);
			continue;
		}

		if (!m_config.m_stomach && HitboxToHitgroup(hitbox) == e_hitgroups::hitgroup_stomach)
		{
			it = m_hitboxes.erase(it);
			continue;
		}

		if (!m_config.m_arms && (HitboxToHitgroup(hitbox) == e_hitgroups::hitgroup_leftarm || HitboxToHitgroup(hitbox) == e_hitgroups::hitgroup_rightarm))
		{
			it = m_hitboxes.erase(it);
			continue;
		}

		if (!m_config.m_legs)
		{
			if (hitbox == hitbox_left_calf || hitbox == hitbox_left_thigh || hitbox == hitbox_right_calf || hitbox == hitbox_right_thigh) {
				it = m_hitboxes.erase(it);
				continue;
			}
		}

		if (!m_config.m_feet && (hitbox == hitbox_left_foot || hitbox == hitbox_right_foot))
		{
			it = m_hitboxes.erase(it);
			continue;
		}

		it++;
	}
}

struct backtrack_data
{
	int64 command_number;
	float time;
	int64 tick;
	vector eye_position;
	vector eye_angles;
	std::byte pad[40];
} __attribute__((packed));

backtrack_data* get_data(c_base_player_weapon* weapon, backtrack_data* data, c_unkown_information* class_info, int value)
{

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 18 48 89 74 24 20 57 48 83 EC 30 48 8B 41" );
	return pattern.as<backtrack_data * (__fastcall*)(c_base_player_weapon*, backtrack_data*, int, int)>()(weapon, data, 15, value);
}

int adjust_pause_tick(int attack_tick, c_base_player_weapon* weapon)
{
	if (!Interfaces::m_game_rules || weapon->get_class_information()->number)
		return attack_tick;
	else
		return attack_tick + Interfaces::m_game_rules->pause;
}

matrix3x4_t TransToMatrix(const c_bone_data& in2) {
	matrix3x4_t  matrix;

	vector_4d rot;
	rot = in2.rot;
	vector pos;
	pos = in2.pos;


	matrix[0][0] = 1.0f - 2.0f * rot.y * rot.y - 2.0f * rot.z * rot.z;
	matrix[1][0] = 2.0f * rot.x * rot.y + 2.0f * rot.w * rot.z;
	matrix[2][0] = 2.0f * rot.x * rot.z - 2.0f * rot.w * rot.y;

	matrix[0][1] = 2.0f * rot.x * rot.y - 2.0f * rot.w * rot.z;
	matrix[1][1] = 1.0f - 2.0f * rot.x * rot.x - 2.0f * rot.z * rot.z;
	matrix[2][1] = 2.0f * rot.y * rot.z + 2.0f * rot.w * rot.x;

	matrix[0][2] = 2.0f * rot.x * rot.z + 2.0f * rot.w * rot.y;
	matrix[1][2] = 2.0f * rot.y * rot.z - 2.0f * rot.w * rot.x;
	matrix[2][2] = 1.0f - 2.0f * rot.x * rot.x - 2.0f * rot.y * rot.y;



	matrix[0][3] = pos.x;
	matrix[1][3] = pos.y;
	matrix[2][3] = pos.z;

	return matrix;
}

bool c_rage_bot::hitchance(vector& pos, c_bone_data* matrix, c_cs_player_pawn* player, int index)
{
	add_trace(__PRETTY_FUNCTION__);
	auto weapon = g_cs2->local_player->get_weapon_active();

	if (!weapon)
		return false;

	auto weapon_data = weapon->get_weapon_data();

	if (!weapon_data)
		return false;

	auto econ_item_view = weapon->get_econ_view_item();

	if (!econ_item_view)
		return false;

	auto skeleton = player->get_skeleton();

	if (!skeleton)
		return false;

	auto model = skeleton->get_model();

	if (!model)
		return false;

	auto hitbox_data = model->get_hitbox(index);

	if (!hitbox_data)
		return false;

	weapon = g_cs2->local_player->get_weapon_active();

	econ_item_view = weapon->get_econ_view_item();
	weapon_data = weapon->get_weapon_data();

	auto recoil_index = weapon->get_weapon_base()->recoil_index();
	auto weapon_index = econ_item_view->item_index();

	vector dir{};
	vector end{};
	vector fwd{};
	vector right{};
	vector up{};


	int hits{};
	int aw_hits{};
	float range = weapon_data->range();

	weapon->update_accuracy();
	auto accuracy = weapon->get_accuracy();
	auto spread = weapon->get_spread();

	auto needed_hits{ (size_t)std::ceil((m_config.hitchance * 255) / 100.f) };

	math::angle_vectors(best_point, &fwd, &right, &up);

	auto bone_index = player->get_bone_index(hitbox_data->m_name);
	auto bone_trasform = TransToMatrix(matrix[bone_index]);

	vector vMin = hitbox_data->m_vMinBounds.transform(bone_trasform), vMax = hitbox_data->m_vMaxBounds.transform(bone_trasform);

	float damage = 0;

	c_trace_filter filter(0x1C3003, g_cs2->local_player, nullptr, 4);

	for (int i = 0; i < 256; i++)
	{
		auto spread_calc = calculate_spread(i, weapon->get_weapon_data()->bullets(), accuracy, spread, weapon_index, recoil_index);

		// get spread direction.
		dir = vector(fwd - (right * spread_calc.x) + (up * spread_calc.y));

		end = g_cs2->eye_position + dir * range;

		c_ray ray{};
		c_game_trace trace{};
		Interfaces::trace->clip_ray_to_entity(&ray, g_cs2->eye_position, end, player, &filter, &trace);

		if (trace.entity == player)
			hits++;
	}

	return hits >= needed_hits;
}

bool c_rage_bot::no_spread(c_user_cmd* cmd, vector& pos, c_cs_player_pawn* player, int index)
{
	add_trace(__PRETTY_FUNCTION__);
	auto weapon = g_cs2->local_player->get_weapon_active();

	if (!weapon)
		return false;

	auto weapon_data = weapon->get_weapon_data();

	if (!weapon_data)
		return false;

	auto econ_item_view = weapon->get_econ_view_item();

	if (!econ_item_view)
		return false;

	weapon = g_cs2->local_player->get_weapon_active();
	econ_item_view = weapon->get_econ_view_item();
	weapon_data = weapon->get_weapon_data();

	float acc = weapon->get_accuracy();
	float spread = weapon->get_spread();
	auto recoil_index = weapon->get_weapon_base()->recoil_index();
	auto weapon_index = econ_item_view->item_index();

	//backtrack_data* backtrack_data_ = new backtrack_data;
	//get_data(weapon, backtrack_data_, weapon->get_class_information(), 0);

	vector dir{}, end{}, fwd{}, right{}, up{};

	c_game_trace trace{};

	c_trace_filter filter(0x1C3003, g_cs2->local_player, nullptr, 4);

	int hits{};
	float range = weapon_data->range();

	math::angle_vectors(best_point, &fwd, &right, &up);

	auto spread_calc = calculate_spread(get_hash_seed(g_cs2->local_player, best_point, g_cs2->prediction_tick + 1), weapon->get_weapon_data()->bullets(), acc, spread, weapon_index, recoil_index);

	// get spread direction.
	dir = vector(fwd + (right * spread_calc.x) + (up * spread_calc.y));

	end = g_cs2->eye_position + dir * range;

	c_ray ray{};
	Interfaces::trace->clip_ray_to_entity(&ray, g_cs2->eye_position, end, player, &filter, &trace);

	if (trace.entity == player && trace.trace_model->m_nHitBoxIndex == index)
		return true;

	return false;
}

bool c_rage_bot::multipoints(c_cs_player_pawn* pawn, c_bone_data* bones, int index, std::vector<c_points>& points, bool predicted)
{

	points.clear();

	auto skeleton = pawn->get_skeleton();

	if (!skeleton)
		return false;

	auto model = skeleton->get_model();

	if (!model)
		return false;

	auto hitbox_data = model->get_hitbox(index);

	if (!hitbox_data)
		return false;

	auto bone_index = pawn->get_bone_index(hitbox_data->m_name);
	bool is_chest = index == hitbox_chest || index == hitbox_upper_chest || index == hitbox_lower_chest;

	if (predicted) {
		add_point(bones[bone_index].pos, false, points);
		return true;
	}

	if (index == hitbox_head && !m_config.m_head2)
	{
		add_point(bones[bone_index].pos, false, points);
		return true;
	}

	if (is_chest && !m_config.m_chest2)
	{
		add_point(bones[bone_index].pos, false, points);
		return true;
	}

	if (index == hitbox_stomach && !m_config.m_stomach2)
	{
		add_point(bones[bone_index].pos, false, points);
		return true;
	}

	if ((HitboxToHitgroup(index) == e_hitgroups::hitgroup_leftarm || HitboxToHitgroup(index) == e_hitgroups::hitgroup_rightarm) && !m_config.m_arms2)
	{
		add_point(bones[bone_index].pos, false, points);
		return true;
	}

	if ((HitboxToHitgroup(index) == e_hitgroups::hitgroup_leftleg || HitboxToHitgroup(index) == e_hitgroups::hitgroup_rightleg) && !m_config.m_legs2)
	{
		add_point(bones[bone_index].pos, false, points);
		return true;
	}

	if ((index == hitbox_left_foot || index == hitbox_right_foot) && !m_config.m_feet2)
	{
		add_point(bones[bone_index].pos, false, points);
		return true;
	}

	float radius = hitbox_data->m_flShapeRadius * (m_config.point_scale / 100.f);

	vector center{};
	vector left = vector(0.f, 0.f, radius);
	vector right = vector(0.f, 0.f, -radius);
	vector back = vector(0.f, -radius, 0.f);

	if (radius <= 0.f)
		return false;

	matrix3x4_t mat = TransToMatrix(bones[bone_index]);

	if (hitbox_data->m_flShapeRadius > 0.f)
	{
		switch (index)
		{
		case hitbox_head:
		{
			auto mini_peka = vector(hitbox_data->m_vMaxBounds.x + radius, hitbox_data->m_vMaxBounds.y - radius, hitbox_data->m_vMaxBounds.z);
			left = vector(hitbox_data->m_vMaxBounds.x, hitbox_data->m_vMaxBounds.y, hitbox_data->m_vMaxBounds.z - radius);
			right = vector(hitbox_data->m_vMaxBounds.x, hitbox_data->m_vMaxBounds.y, hitbox_data->m_vMaxBounds.z + radius);
			add_point(left.transform(mat), false, points);
			add_point(right.transform(mat), false, points);
			add_point(mini_peka.transform(mat), false, points);
		}
		break;
		case hitbox_chest:
		case hitbox_lower_chest:
		case hitbox_upper_chest:
		case hitbox_stomach:
			add_point(left.transform(mat), false, points);
			add_point(right.transform(mat), false, points);
			add_point(back.transform(mat), false, points);
			break;
		default:
			add_point(bones[bone_index].pos, false, points);
			break;
		}
	}

	return true;
}

bool c_rage_bot::valid_interpolation_timing()
{
	for (int i{}; i < Interfaces::csgo_input->input_message.size; i++)
	{
		auto history = Interfaces::csgo_input->input_message.pb->history[i];
		int player_tick_count = history.player_tick_count;
		float player_fraction = history.player_fraction;

		if (player_fraction >= float(1.0 - 0.0099999998))
			player_tick_count += 1;

		float time = player_tick_count;
		time += player_fraction;

		auto tick = g_cs2->local_player->get_lerp_tick(player_tick_count);

		if (tick >= player_tick_count)
			return false;
	}

	return true;
}

bool is_range_angle(c_user_cmd* cmd, c_cs_player_pawn* pawn)
{
	if (!pawn->is_enemy())
		return false;

	auto abs_origin = g_cs2->local_player->game_scene_node()->abs_origin();
	auto player_abs_origin = pawn->game_scene_node()->abs_origin();
	
	auto movement = pawn->movement_services();

	float max_speed = 260.f;

	if (movement) {
		max_speed = movement->m_max_speed();
	}

	auto delta_origin = player_abs_origin - abs_origin;

	if (delta_origin.length() < (max_speed * 1.5f) * g_cs2->sv_maxunlag->GetValue<float>())
		return true;

	vector fwd;

	math::angle_vectors(cmd->base->view->angles, fwd);

	float average_hyeta = (fwd.x + delta_origin.x) + (fwd.y + delta_origin.y) + (fwd.z + delta_origin.z);

	return average_hyeta >= 0.70710701f;
}

std::optional<c_best_scan> c_rage_bot::Scan(c_cs_player_pawn* player, bool predicted)
{
	auto animation = g_lagcompensation->get_animation(player);

	if (!animation)
		return std::nullopt;

	auto& record = g_lagcompensation->get_animation(player)->m_lag_records_;

	if (record.empty())
		return std::nullopt;

	setup_hitboxes(player);

	auto& latest_record = record.front();
	std::optional<c_lagrecord> oldest_record = std::nullopt;

	for (auto it = record.rbegin(); it != record.rend(); it++)
	{
		if (it->record_of_bounds())
		{
			oldest_record = std::make_optional(*it);
			break;
		}
	}

	std::vector<c_lagrecord> records{};
	//records.push_back(latest_record);

	if (oldest_record.has_value() && !predicted)
		records.push_back(oldest_record.value());

	std::optional<c_best_scan> m_best_scan = std::nullopt;

	for (auto& record : records) {

		record.apply(player, m_should_extapolation);

		bool done = false;
		float damage{};
		c_lagrecord best_record{};
		int hitbox_index{};
		float best_damage{};

		for (auto& hitbox : m_hitboxes)
		{
			std::vector<c_points> points;

			if (!multipoints(player, player->get_skeleton()->m_modelState().get_bone_data(), hitbox, points, predicted))
				continue;

			for (auto& point : points)
			{

				damage = 0.f;
				int hitbox_ = -1;

				auto start = g_cs2->eye_position;
				auto direction = (point.m_vecPosition - start).normalized();
				direction *= g_cs2->local_player->get_weapon_active()->get_weapon_data()->range();

				if (!g_fx_firebullet->run(player, start, direction, damage, hitbox_) && !m_config.penetration)
					continue;

				if (damage < 1)
					continue;

				if (hitbox_ != hitbox)
					continue;

				if (damage < std::min(player->health(), m_config.damage))
					continue;

				if (hitbox_ == hitbox_stomach || hitbox_ == hitbox_chest || hitbox_ == hitbox_lower_chest || hitbox_ == hitbox_upper_chest)
				{
					if (damage >= player->health())
					{
						m_best_scan = std::make_optional(c_best_scan());
						m_best_scan->damage = damage;
						m_best_scan->hitbox = hitbox;
						m_best_scan->point = point.m_vecPosition;
						m_best_scan->record = record;
						m_best_scan->player = player;
						break;
					}
				}

				if (damage > best_damage)
				{
					m_best_scan = std::make_optional(c_best_scan());
					m_best_scan->damage = damage;
					m_best_scan->hitbox = hitbox;
					m_best_scan->point = point.m_vecPosition;
					m_best_scan->record = record;
					m_best_scan->player = player;
					best_damage = damage;
				}
			}
		}

		record.restore(player);

		if (m_best_scan.has_value())
			break;
	}

	return m_best_scan;
}

void c_rage_bot::on_post(c_user_cmd* cmd)
{

	g_ragebot->revolver_cock(cmd);
	g_ragebot->auto_stop(cmd);

	add_trace(__PRETTY_FUNCTION__);
	if (!Interfaces::engine->is_connected() || !Interfaces::engine->is_in_game())
		return;

	if (!g_cs2->local_player || !g_cs2->local_player->is_alive())
		return;

	if (g_cs2->m_current_group == -1)
		return;

	g_cs2->did_shoot = false;

	if (g_cs2->local_player->move_type() == movetype_t::movetype_ladder || g_cs2->local_player->move_type() == movetype_t::movetype_noclip)
		return;

	if (!g_cs2->local_player->get_weapon_active())
		return;

	if (g_cs2->local_player->get_weapon_active()->is_knife())
		return;

	if (g_cs2->local_player->get_weapon_active()->is_grenade())
		return;

	m_auto_stop = false;

	if (!m_config.enabled)
		return;

	float delta_y = std::fabsf(cmd->base->view->angles.y - g_cs2->store_angle.y);
	float delta_x = std::fabsf(cmd->base->view->angles.x - g_cs2->store_angle.x);

	m_should_extapolation = delta_y >= 45.f || delta_x >= 45.f;

	std::optional<c_best_scan> m_best_scan = std::nullopt;

	m_mutex.lock();

	auto find = m_dropped_players.empty() || Interfaces::globals->global_storage.tick_count > m_dropped_players.back().tick;

	if (find) {

		auto tick = Interfaces::globals->global_storage.tick_count;
		m_dropped_players.clear();

		int i = 0;
		int max_players = 2;

		for (auto& cache : m_players) {
			
			if (m_dropped_players.empty() || tick > m_dropped_players.back().tick) {
				auto& dropped_players = m_dropped_players.emplace_back();
				dropped_players.tick = tick;
			}

			auto& dropped_players = m_dropped_players.back();
			dropped_players.m_players.push_back(cache);

			if ((i % max_players) == max_players - 1) {
				tick++;
				i = 0;
			}
			else {
				i++;
			}
		}
	}

	m_mutex.unlock();

	auto current_cache_player = std::find_if(m_dropped_players.begin(), m_dropped_players.end(), [](dropped_players& x) {
		return x.tick == Interfaces::globals->global_storage.tick_count;
		});

	if (current_cache_player == m_dropped_players.end())
	{
		m_dropped_players.clear();
		return;
	}


	if (m_better_player.has_value()) {
		auto player = m_better_player.value().pawn;

		if (player && player->is_player() && !player->has_gun_immunity() && player->is_enemy())
		{
			m_best_scan = Scan(player, false);

			if (!m_best_scan.has_value()) {
				m_better_player = std::nullopt;
			}
		}
		else {
			m_better_player = std::nullopt;
		}
	}
	else {

		m_mutex.lock();

		auto backup_eye = g_cs2->eye_position;

		g_cs2->eye_position = g_cs2->store_position[Interfaces::csgo_input->sequence % 150];

		for (auto& cache : current_cache_player->m_players)
		{
			auto player = cache.pawn;

			if (!player)
				continue;

			if (!player->is_player())
				continue;

			if (player->has_gun_immunity())
				continue;

			if (!player->is_enemy())
				continue;

			m_best_scan = Scan(player, true);

			if (m_best_scan.has_value())
			{
				m_auto_stop = true;
				auto_stop(cmd);
			}
		}

		g_cs2->eye_position = backup_eye;

		for (auto& cache : current_cache_player->m_players)
		{
			auto player = cache.pawn;

			if (!player)
				continue;

			if (!player->is_player())
				continue;

			if (player->has_gun_immunity())
				continue;

			if (!player->is_enemy())
				continue;

			m_best_scan = Scan(player, false);

			if (m_best_scan.has_value())
			{
				m_better_player = std::make_optional<c_player_cache>(cache);
				break;
			}
		}

		m_mutex.unlock();

	}

	if (!m_best_scan.has_value())
		return;

	vector angle{};
	vector aim_punch{};
	math::vector_angles(m_best_scan.value().point - g_cs2->eye_position, angle);

	best_point = angle;

	m_auto_stop = true;

	if (!g_cs2->local_player->is_scoped() && g_cs2->local_player->get_weapon_active() && g_cs2->local_player->get_weapon_active()->is_sniper() && m_config.scope && !m_config.no_spread)
	{
		cmd->buttons.buttonstate[0] |= 2048;
		cmd->buttons.buttonstate[1] |= 2048;
	}

	auto_stop(cmd);

	m_best_scan.value().record.apply(m_best_scan.value().player, m_should_extapolation);

	if (m_config.no_spread)
	{
		if (!no_spread(cmd, angle, m_best_scan.value().player, m_best_scan.value().hitbox))
			return m_best_scan.value().record.restore(m_best_scan.value().player);
	}
	else
	{
		if (!hitchance(angle, m_best_scan.value().player->get_skeleton()->m_modelState().get_bone_data(), m_best_scan.value().player, m_best_scan.value().hitbox))
			return m_best_scan.value().record.restore(m_best_scan.value().player);
	}

	m_best_scan.value().record.restore(m_best_scan.value().player);

	if (g_cs2->local_player->aim_punch_cache().get_size() > 0)
	{
		best_point -= g_cs2->local_player->aim_punch_cache().get_element(g_cs2->local_player->aim_punch_cache().get_size() - 1) * 2;
		angle = best_point;
	}

	math::normalize_angles(angle);

	if (!can_shoot(cmd->input_history.m_pRep->m_tElements[cmd->input_history.m_nCurrentSize - 1]->player_tick_count) && !g_user->IsActive(xorstr_("ragebot_rapidfire"), xorstr_("ragebot_rapidfire"), 0))
		return;

	if (m_config.auto_fire)
	{
		if (g_cs2->m_current_group == 3)
		{
			cmd->buttons.buttonstate[0] |= 2048;
		}
		else {
			if (!(cmd->buttons.buttonstate[0] & 1)) {
				cmd->buttons.buttonstate[0] |= 1;
				cmd->buttons.buttonstate[1] |= 1;
				cmd->base->buttons->buttons[0] |= 1;
				cmd->base->buttons->buttons[1] |= 1;
				cmd->add_subtick(true, 1);
				cmd->add_subtick(false, 1);
			}
		}
		cmd->set_attack_history(cmd->input_history.m_nCurrentSize - 1);
	}

	bool is_fire = cmd->buttons.buttonstate[0] & 1;

	if (g_cs2->m_current_group == 3)
		is_fire = cmd->buttons.buttonstate[0] & 2048;

	if (is_fire) {

		if (!g_user->IsActive(xorstr_("ragebot_hideshots"), xorstr_("ragebot_hideshots"), 0))
			cmd->base->view->angles = angle;

		cmd->set_input_history_angle(angle);

		int best_tick = TIME_TO_TICKS(m_best_scan.value().record.get_sim_time() + Interfaces::client->get_lerp_time());
		for (std::int32_t i = 0; i < cmd->input_history.m_nCurrentSize; i++)
		{
			csgo_input_history_entry* tick = cmd->input_history.m_pRep->m_tElements[i];

			if (tick) {
				tick->render_tick_count = best_tick + 1;

				if (tick->cl_interp) {
					tick->cl_interp->src_tick = best_tick + 1;
					tick->cl_interp->dst_tick = best_tick;
				}

				if (tick->sv_interp0) {
					tick->sv_interp0->src_tick = best_tick + 1;
					tick->sv_interp0->dst_tick = best_tick;
				}

				if (tick->sv_interp1) {
					tick->sv_interp1->src_tick = best_tick + 1;
					tick->sv_interp1->dst_tick = best_tick;
				}

				if (tick->player_interp) {
					tick->player_interp->src_tick = best_tick + 1;
					tick->player_interp->dst_tick = best_tick;
				}
			}
		}

		g_cs2->did_shoot = true;
	}

	if (!m_config.silent)
		Interfaces::csgo_input->view_angle = angle;
}