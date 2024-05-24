// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../feature.hpp"



bool c_legit_bot::can_see_player_position(c_cs_player_pawn* player, vector& position)
{
	c_trace_filter filter(0x1C300B, g_cs2->local_player, nullptr, 3);
	c_ray ray = { };
	c_game_trace trace = { };

	Interfaces::trace->trace_shape(&ray, g_cs2->eye_position, position, &filter, &trace);

	return trace.entity == player || trace.fraction > 0.97f;
}

vector c_legit_bot::get_aim_punch() {
	vector aim_punch{};
	if (g_cs2->local_player->aim_punch_cache().get_size() <= 0)
		return vector();

	return g_cs2->local_player->aim_punch_cache().get_element(g_cs2->local_player->aim_punch_cache().get_size() - 1);
}

vector c_legit_bot::get_prev_aim_punch() {
	vector aim_punch{};
	if (g_cs2->local_player->aim_punch_cache().get_size() < 1)
		return vector();

	return g_cs2->local_player->aim_punch_cache().get_element(g_cs2->local_player->aim_punch_cache().get_size() - 2);
}

bool c_legit_bot::perform_checks() {

	if (!g_user->IsActive(xorstr_("legitbot_enabled"), xorstr_("legitbot_enabled"), 0))
		return false;

	if (!Interfaces::engine->is_connected() ||
		!Interfaces::engine->is_in_game())
		return false;

	if (!g_cs2->local_player ||
		!g_cs2->local_player->is_alive())
		return false;

	if (g_cs2->local_player->actual_move_type() == movetype_t::movetype_ladder ||
		g_cs2->local_player->actual_move_type() == movetype_t::movetype_noclip)
		return false;
	if (!g_cs2->local_player->get_weapon_active())
		return false;

	if (g_cs2->local_player->get_weapon_active()->is_knife())
		return false;

	if (g_cs2->local_player->get_weapon_active()->is_grenade())
		return false;
	return true;
}

void c_legit_bot::get_hitbox_selection() {
	if (g_user->IsActive(xorstr_("legitbot_hitbox_head"), xorstr_("legitbot_hitbox_head"), 0))
	{
		m_hitboxes.emplace_back(hitbox_head);
	}

	if (g_user->IsActive(xorstr_("legitbot_hitbox_body"), xorstr_("legitbot_hitbox_head"), 1))
	{
		m_hitboxes.emplace_back(hitbox_pelvis);
		m_hitboxes.emplace_back(hitbox_stomach);
		m_hitboxes.emplace_back(hitbox_lower_chest);
		m_hitboxes.emplace_back(hitbox_chest);
		m_hitboxes.emplace_back(hitbox_upper_chest);
	}

	if (g_user->IsActive(xorstr_("legitbot_hitbox_arms"), xorstr_("legitbot_hitbox_head"), 2))
	{
		m_hitboxes.emplace_back(hitbox_right_hand);
		m_hitboxes.emplace_back(hitbox_right_forearm);
		m_hitboxes.emplace_back(hitbox_right_upper_arm);

		m_hitboxes.emplace_back(hitbox_left_hand);
		m_hitboxes.emplace_back(hitbox_left_forearm);
		m_hitboxes.emplace_back(hitbox_left_upper_arm);
	}

	if (g_user->IsActive(xorstr_("legitbot_hitbox_legs"), xorstr_("legitbot_hitbox_head"), 3))
	{
		m_hitboxes.emplace_back(hitbox_right_foot);
		m_hitboxes.emplace_back(hitbox_right_calf);
		m_hitboxes.emplace_back(hitbox_right_thigh);

		m_hitboxes.emplace_back(hitbox_left_foot);
		m_hitboxes.emplace_back(hitbox_left_calf);
		m_hitboxes.emplace_back(hitbox_left_thigh);
	}
}

void c_legit_bot::on_post(c_user_cmd* cmd)
{
	m_final_target.reset();
	m_hitboxes.clear();

	if (!perform_checks())
		return;

	m_original_viewangles = Interfaces::csgo_input->view_angle;
	
	recoil_control_system(cmd);
	get_hitbox_selection();
	if (m_force_target){
		if (scan(cmd, m_force_target.player)) {
			fire(cmd, true);
			return;
		}else 
			m_force_target.reset();
	}
	scan(cmd);
	fire(cmd);
	trigger(cmd);
}
void c_legit_bot::fire(c_user_cmd* cmd, bool force_attack)
{
	if (!m_final_target.player)
		return;

	if (!force_attack && !(cmd->buttons.buttonstate[0] & InputBitMask_t::IN_ATTACK))
		return;

	vector punch_angle;
	auto aim_punch = get_aim_punch();
	if (g_user->IsActive(xorstr_("legitbot_standalone_rcs"), xorstr_("legitbot_standalone_rcs"), 0) && !aim_punch.is_zero()) {
		punch_angle.x = aim_punch.x * 2 * 0.01f * (float)g_user->IsActive(xorstr_("legitbot_rcs_coefficient"), xorstr_("legitbot_rcs_coefficient"), 0);
		punch_angle.y = aim_punch.y * 2 * 0.01f * (float)g_user->IsActive(xorstr_("legitbot_rcs_coefficient"), xorstr_("legitbot_rcs_coefficient"), 0);
	}

	auto angle = math::calc_angle(g_cs2->eye_position, m_final_target.point) - m_original_viewangles - punch_angle;

	math::normalize_angles(angle);

	auto smooth_value = get_smooth_value();
	if (smooth_value > 1.0f)
		angle /= smooth_value;

	m_force_target.reset();
	vector final_angle = m_original_viewangles + angle;
	math::normalize_angles(final_angle);
	cmd->set_input_history_angle(final_angle);

	if (!g_user->IsActive(xorstr_("legitbot_silent"), xorstr_("legitbot_silent"), 0))
		Interfaces::csgo_input->view_angle = final_angle;
}

bool valid_interpolation_timing2()
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

		// минус 1 тик ебливый предикт
		if (tick >= player_tick_count)
			return false;
	}

	return true;
}

void c_legit_bot::trigger(c_user_cmd* cmd)
{
	if (!g_user->IsActive(xorstr_("legitbot_trigger_bot"), xorstr_("legitbot_trigger_bot"), 0))
		return;

	if (!g_ragebot->can_shoot(cmd->base->tick_count))
		return;

	if (!cmd->input_history.m_pRep)
		return;

	auto history = cmd->input_history.m_pRep->m_tElements[cmd->input_history.m_nCurrentSize - 1];

	vector tmp;
	math::angle_vectors(history->angle->angles, tmp);
	auto end_pos = g_cs2->eye_position + tmp * g_cs2->local_player->get_weapon_active()->get_weapon_data()->range();

	c_ray ray{};
	c_trace_filter filter(0x1C300B, g_cs2->local_player, nullptr, 4);
	c_game_trace trace{};
	Interfaces::trace->trace_shape(&ray, g_cs2->eye_position, end_pos, &filter, &trace);

	if (!trace.entity) return;
	if (!trace.entity->is_player()) return;
	if (!trace.entity->health()) return;
	if (!trace.entity->is_enemy()) return;
	if (trace.entity->is_smoke_view()) return;
	if (!valid_interpolation_timing2()) return;

	vector angle{};
	math::vector_angles(trace.end_pos - g_cs2->eye_position, angle);

	//if (!g_ragebot->no_spread(cmd, angle, trace.entity, trace.trace_model->m_nHitBoxIndex)) return;

	cmd->buttons.buttonstate[0] |= 1;
	cmd->base->buttons->buttons[0] |= 1;


	cmd->set_button_state(InputBitMask_t::IN_ATTACK, EInButtonState::IN_BUTTON_DOWN);
	cmd->set_attack_history(cmd->input_history.m_nCurrentSize - 1);
}
float c_legit_bot::get_smooth_value()
{
	if (!g_user->IsActive(xorstr_("legitbot_smooth"), xorstr_("legitbot_smooth"), 0))
		return 0.0f;

	auto smooth_value = (float)g_user->IsActive(xorstr_("legitbot_smooth"), xorstr_("legitbot_smooth"), 0) * 3.0f;
	auto field_of_view = math::clamp(m_final_target.field_of_view, 0.0f, 30.0f);

	if (g_user->IsActive(xorstr_("legitbot_smooth"), xorstr_("legitbot_smooth"), 0) == 1)
		smooth_value *= field_of_view * 0.1f;
	else
		smooth_value *= pow(field_of_view, 2.0f) * 0.01f;
	return smooth_value;
}
bool c_legit_bot::scan(c_user_cmd* cm, c_cs_player_pawn* force_player)
{
	auto legitbot_fov = g_user->IsActive(xorstr_("legitbot_fov"), xorstr_("legitbot_fov"), 0);

	auto max_fov = legitbot_fov;

	if (!max_fov) {
		m_last_point_render.invalidate();
		return false;
	}

	if (force_player)
	{
		if (!force_player->is_alive() || force_player->game_scene_node()->dormant() || force_player->has_gun_immunity())
			return false;

		if (!force_player->is_enemy())
			return false;

		auto skeleton = force_player->get_skeleton();

		if (!skeleton)
			return false;

		auto model = skeleton->get_model();

		if (!model)
			return false;

		auto bone_data = skeleton->m_modelState().get_bone_data();

		if (!bone_data)
			return false;

		for (auto hitbox : m_hitboxes)
		{
			auto hitbox_data = model->get_hitbox(hitbox);

			if (!hitbox_data || !hitbox_data->m_name)
				continue;

			auto bone_index = force_player->get_bone_index(hitbox_data->m_name);
			auto bone_data_ = bone_data[bone_index];

			auto angle = math::calc_angle(g_cs2->eye_position, bone_data_.pos);
			auto field_of_view = math::get_fov(m_original_viewangles, angle);
			
			if (!can_see_player_position(force_player, bone_data_.pos))
				continue;

			if (m_final_target.field_of_view < field_of_view)
				continue;

			m_final_target.field_of_view = field_of_view;
			m_final_target.hitbox = hitbox;
			m_final_target.visible = true;
			m_final_target.player = force_player;
			m_final_target.point = bone_data_.pos;
		}
		if (m_final_target.player) {
			if (!math::world_to_screen(m_final_target.point, m_last_point_render))
				m_last_point_render.invalidate();
		}
		else
			m_last_point_render.invalidate();

		return m_final_target;
	
	}
	for (std::uint32_t i = 0; i < Interfaces::globals->max_client; i++)
	{
		c_cs_player_controller* controller = Interfaces::entity_list->get_controller(i);

		if (!controller)
			continue;

		if (!controller->find_class(HASH("CCSPlayerController")))
			continue;

		auto player = controller->get_player_pawn();

		if (!player)
			continue;

		if (!player->find_class(HASH("C_CSPlayerPawn")))
			continue;

		if (!player->is_alive() || player->game_scene_node()->dormant() || player->has_gun_immunity())
			continue;

		if (!player->is_enemy())
			continue;
		
		for (auto hitbox : m_hitboxes)
		{
			auto skeleton = player->get_skeleton();

			if (!skeleton)
				continue;

			auto model = skeleton->m_modelState().m_hModel();

			if (!model)
				continue;

			auto bone_data = skeleton->m_modelState().get_bone_data();

			if (!bone_data)
				continue;

			auto hitbox_data = model->get_hitbox(hitbox);

			if (!hitbox_data || !hitbox_data->m_name)
				continue;

			auto bone_index = player->get_bone_index(hitbox_data->m_name);
			auto bone_data_ = bone_data[bone_index];

			auto angle = math::calc_angle(g_cs2->eye_position, bone_data_.pos);
			auto field_of_view = math::get_fov(m_original_viewangles, angle);

			if (!can_see_player_position(player, bone_data_.pos))
				continue;

			if (m_final_target.field_of_view < field_of_view)
				continue;

			m_final_target.field_of_view = field_of_view;
			m_final_target.hitbox = hitbox;
			m_final_target.visible = true;
			m_final_target.player = player;		
			m_final_target.point = bone_data_.pos;
		}
	}
	if (m_final_target.player) {
		if (!math::world_to_screen(m_final_target.point, m_last_point_render))
			m_last_point_render.invalidate();
	}else
		m_last_point_render.invalidate();

	return m_final_target;
}
void c_legit_bot::recoil_control_system(c_user_cmd* cmd)
{
	if (!g_user->IsActive(xorstr_("legitbot_standalone_rcs"), xorstr_("legitbot_standalone_rcs"), 0))
		return;

	auto aim_punch = get_aim_punch();

	if (aim_punch.is_zero())
		return;

	auto prev_aim_punch = get_prev_aim_punch();

	if (g_cs2->local_player->shots_fired() > 1)
	{
		vector recoil_vector = vector(
			((m_old_aim_punch.x - aim_punch.x) * 2.0f * (g_user->IsActive(xorstr_("legitbot_rcs_coefficient"), xorstr_("legitbot_rcs_coefficient"), 0) / 100.0f)),
			((m_old_aim_punch.y - aim_punch.y) * 2.0f * (g_user->IsActive(xorstr_("legitbot_rcs_coefficient"), xorstr_("legitbot_rcs_coefficient"), 0) / 100.0f)),
			0.f
		);
		Interfaces::csgo_input->view_angle += recoil_vector;
	}
	m_old_aim_punch = aim_punch;
}
