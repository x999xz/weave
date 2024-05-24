// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../feature.hpp"
#include "../../utilities/hotkey_system/hotkey_system.h"
#include "../../utilities/input_system/input_system.h"

void c_movement::on_pre(c_user_cmd* cmd) {
	g_movement->auto_strafe();
	g_movement->bhop(cmd);
}

void c_movement::on_post() {
	g_movement->autopeek();
	g_movement->duck_assist();
}

void c_movement::clamp_movement(float speed)
{
	float final_speed = speed;

	if (!g_cs2->local_player && !g_cs2->local_player->is_alive())
		return;

	g_cs2->m_current_command->set_button_state(InputBitMask_t::IN_SPEED, EInButtonState::IN_BUTTON_DOWN_UP);

	auto f = g_cs2->m_current_command->base->forwardmove * 250.f;
	auto f2 = g_cs2->m_current_command->base->sidemove * 250.f;

	float squirt = std::sqrtf((f * f) + (f2 * f2));

	if (squirt > speed) {

		float aye = squirt / speed;

		g_cs2->m_current_command->base->forwardmove /= aye;
		g_cs2->m_current_command->base->sidemove /= aye;
	}
}

void c_movement::bhop(c_user_cmd* cmd)
{
	if (!Interfaces::engine->is_connected() || !Interfaces::engine->is_in_game()) return;
	if (!g_cs2->local_player || !g_cs2->local_player->is_alive()) return;
	if (g_cs2->local_player->move_type() == movetype_t::movetype_ladder || g_cs2->local_player->move_type() == movetype_t::movetype_noclip) return;
	if (g_cs2->sv_autobunnyhopping && g_cs2->sv_autobunnyhopping->GetValue<bool>()) return;
	//if (Interfaces::m_game_rules->freeze_pause) return;
	if (!g_user->IsActive(xorstr_("misc_bunnyhop"), xorstr_("misc_bunnyhop"), 0)) return;


	/*if (!should_fake)
	{
		if (g_cs2->m_current_command->buttons.buttonstate[0] & IN_JUMP)
		{
			is_subtick = Interfaces::csgo_input->subtick_count >= 1 || Interfaces::csgo_input->subtick_cache.size >= 1;
			should_fake = true;
		}
	}
	else if (!(g_cs2->m_current_command->buttons.buttonstate[0] & IN_JUMP))
	{
		should_fake = false;
	}

	m_jump[Interfaces::csgo_input->sequence % 150].on_ground = g_cs2->local_player->flags() & fl_onground;
	m_jump[Interfaces::csgo_input->sequence % 150].should_check = false;

	if (!m_jump[(Interfaces::csgo_input->sequence - 1) % 150].should_check)
	{
		bool jump_subtick = !m_jump[(Interfaces::csgo_input->sequence - 1) % 150].on_ground && m_jump[Interfaces::csgo_input->sequence % 150].on_ground && Interfaces::globals->interval_per_ticks < 0.013f;
		if (!m_jump[Interfaces::csgo_input->sequence % 150].on_ground || jump_subtick)
		{
			g_cs2->m_current_command->buttons.buttonstate[0] &= ~2;
			g_cs2->m_current_command->buttons.buttonstate[1] &= ~2;
			g_cs2->m_current_command->buttons.buttonstate[2] &= ~2;

			if (jump_subtick)
				m_jump[Interfaces::csgo_input->sequence % 150].should_check = true;

			return;
		}
	}*/

	auto set_jump = [&]() {
		g_cs2->m_current_command->buttons.buttonstate[0] |= IN_JUMP;
		g_cs2->m_current_command->buttons.buttonstate[1] |= IN_JUMP;

		cmd->add_subtick(true, IN_JUMP);
		cmd->add_subtick(false, IN_JUMP);
	};

	auto remove_jump = [&]() {
		g_cs2->m_current_command->buttons.buttonstate[0] &= ~IN_JUMP;
		g_cs2->m_current_command->buttons.buttonstate[1] &= ~IN_JUMP;
		g_cs2->m_current_command->buttons.buttonstate[2] &= ~IN_JUMP;
	};

	auto is_jumping = [&]() {
		return g_cs2->m_current_command->buttons.buttonstate[0] & IN_JUMP
			|| g_cs2->m_current_command->buttons.buttonstate[1] & IN_JUMP;
		};

	static bool last_jumped{}, should_fake{};
	if (!last_jumped && should_fake)
	{
		should_fake = false;
		set_jump();
	}
	else if (is_jumping())
	{
		if (g_cs2->local_player->flags() & fl_onground)
			should_fake = last_jumped = true;
		else
		{
			remove_jump();
			last_jumped = false;
		}
	}
	else
	{
		should_fake = last_jumped = false;
	}

	/*bool jumping = g_cs2->m_current_command->buttons.buttonstate[0] & IN_JUMP;

	if (!jumping)
		return;

	g_cs2->m_current_command->buttons.buttonstate[0] &= ~IN_JUMP;
	g_cs2->m_current_command->buttons.buttonstate[1] &= ~IN_JUMP;
	g_cs2->m_current_command->buttons.buttonstate[2] &= ~IN_JUMP;

	if (!(g_cs2->local_player->flags() & fl_onground))
		return;

	g_cs2->m_current_command->buttons.buttonstate[0] |= IN_JUMP;
	g_cs2->m_current_command->buttons.buttonstate[1] |= IN_JUMP;
	g_cs2->m_current_command->buttons.buttonstate[2] |= IN_JUMP;

	cmd->add_subtick(true, IN_JUMP);
	cmd->add_subtick(false, IN_JUMP);*/

}

void c_movement::autopeek()
{
	if (!g_cs2->local_player || !g_cs2->local_player->is_alive())
		return;

	auto m_data = &m_autopeek;
	if (g_user->IsActive(xorstr_("misc_autopeek"), xorstr_("misc_autopeek"), 0)) {
		if (!m_data->m_autopeeking) {
			m_data->m_should_retrack = false;
			m_data->m_old_origin = g_cs2->local_player->game_scene_node()->abs_origin();


			c_game_trace trace;
			c_trace_filter filter(0x3001, nullptr, nullptr, 3);
			filter.collision2 = 0x10000;

			c_ray ray{};
			Interfaces::trace->trace_shape(&ray, g_cs2->eye_position, g_cs2->eye_position - vector(0, 0, 1000.f), &filter, &trace);

			if (trace.fraction < 1.0f)
				m_data->m_old_origin = trace.end_pos + vector(0.0f, 0.0f, 2.0f);

		}
		if (m_data->m_should_retrack) {
			auto distance = g_cs2->local_player->game_scene_node()->abs_origin().dist_to(m_data->m_old_origin);
			if (distance <= 16.0) {
				m_data->m_autopeeking = false;
				m_data->m_should_retrack = false;
			}
			else {
				vector ang_to_pos;
				vector local_angle = Interfaces::csgo_input->view_angle;
				auto difference = m_data->m_old_origin - g_cs2->local_player->game_scene_node()->abs_origin();
				math::vector_angles(difference, ang_to_pos);
				auto v45 = cos(ang_to_pos.x * 0.017453292);

				g_cs2->m_current_command->base->forwardmove = 0.0;
				g_cs2->m_current_command->base->sidemove = 0.0;

				auto v48 = math::deg2rad((local_angle.y - ang_to_pos.y));
				auto v66 = math::deg2rad((local_angle.y - ang_to_pos.y));
				auto cos_v48 = cos(v48);
				auto sin_v48 = sin(v66);

				auto v50 = cos_v48 * v45;

				g_cs2->m_current_command->base->forwardmove = fmaxf(fminf(1.0, v50), -1.0);
				g_cs2->m_current_command->base->sidemove = -fmaxf(fminf(1.0, (float)(sin_v48 * v45)), -1.0);
			}
		}
		if (g_cs2->did_shoot) {
			m_data->m_should_retrack = true;
		}
		m_data->m_autopeeking = true;
	}
	else {
		m_data->m_autopeeking = false;
		m_data->m_should_retrack = false;
	}

}

void c_movement::duck_assist()
{
	if (!g_cs2->local_player->get_weapon_active())
		return;

	if (!g_user->IsActive(xorstr_("misc_duck_assist"), xorstr_("misc_duck_assist"), 0))
	{
		m_duck_assist.m_peeking = false;
		return;
	}

	if (g_cs2->local_player->get_weapon_active()->is_knife())
	{
		m_duck_assist.m_peeking = false;
		return;
	}

	if (g_cs2->local_player->get_weapon_active()->is_grenade())
	{
		m_duck_assist.m_peeking = false;
		return;
	}

	if (m_duck_assist.m_peeking)
	{
		g_cs2->m_current_command->buttons.buttonstate[0] &= ~InputBitMask_t::IN_DUCK;
	}

	vector fwd;
	math::angle_vectors(Interfaces::csgo_input->view_angle, fwd);

	auto shoot_position_unduck = g_cs2->eye_position + Interfaces::m_game_rules->get_view_vectors()->vec_view;

	auto point = shoot_position_unduck + (fwd * g_cs2->local_player->get_weapon_active()->get_weapon_data()->range());
	auto direction = (point - shoot_position_unduck).normalized();
	direction *= g_cs2->local_player->get_weapon_active()->get_weapon_data()->range();
	float damage = 0;

	for (int i = 1; i < 32; i++)
	{
		auto controller = Interfaces::entity_list->get_controller(i);

		if (!controller)
			continue;

		auto pawn = controller->get_player_pawn();

		if (!pawn)
			continue;

		if (!pawn->is_enemy())
			continue;

		if (!pawn->is_alive())
			continue;

		int hitbox_ = -1;

		if (g_fx_firebullet->run(pawn, shoot_position_unduck, direction, damage, hitbox_))
		{
			if (g_cs2->local_player->movement_services()->m_flDuckAmount() > 0.95f)
				m_duck_assist.m_peeking = true;
		}
	}
}

void c_movement::auto_strafe()
{
	if (g_cs2->local_player->move_type() == movetype_ladder || g_cs2->local_player->move_type() == movetype_noclip || g_cs2->local_player->flags() & fl_onground)
		return;

	if (g_cs2->local_player->actual_move_type() == movetype_ladder || g_cs2->local_player->actual_move_type() == movetype_noclip)
		return;

	if (g_input_system->get_hold_key(VK_LSHIFT) || g_user->IsActive(xorstr_("ragebot_slowwalk"), xorstr_("ragebot_slowwalk"), 0))
		return;

	if (!g_user->IsActive(xorstr_("misc_autostrafe"), xorstr_("misc_autostrafe"), 0))
		return;

	const auto current_buttons = g_cs2->m_current_command->buttons.buttonstate[0];
	auto yaw = math::normalize_yaw(g_cs2->m_current_command->base->view->angles.y);

	const auto check_button = [&](const uint64_t button)
		{
			if (current_buttons & button && (!(last_buttons & button) || button & InputBitMask_t::IN_MOVELEFT && !(last_pressed & InputBitMask_t::IN_MOVERIGHT) || button &
				InputBitMask_t::IN_MOVERIGHT && !(last_pressed & InputBitMask_t::IN_MOVELEFT) || button & InputBitMask_t::IN_FORWARD && !(last_pressed & InputBitMask_t::IN_BACK) ||
				button & InputBitMask_t::IN_BACK && !(last_pressed & InputBitMask_t::IN_FORWARD)))
			{
				if (button & InputBitMask_t::IN_MOVELEFT)
					last_pressed &= ~InputBitMask_t::IN_MOVERIGHT;
				else if (button & InputBitMask_t::IN_MOVERIGHT)
					last_pressed &= ~InputBitMask_t::IN_MOVELEFT;
				else if (button & InputBitMask_t::IN_FORWARD)
					last_pressed &= ~InputBitMask_t::IN_BACK;
				else if (button & InputBitMask_t::IN_BACK)
					last_pressed &= ~InputBitMask_t::IN_FORWARD;

				last_pressed |= button;

			}
			else if (!(current_buttons & button))
				last_pressed &= ~button;
		};

	check_button(InputBitMask_t::IN_MOVELEFT);
	check_button(InputBitMask_t::IN_MOVERIGHT);
	check_button(InputBitMask_t::IN_FORWARD);
	check_button(InputBitMask_t::IN_BACK);

	last_buttons = current_buttons;

	const auto velocity = g_cs2->local_player->abs_velocity();

	if (g_cs2->local_player->flags() & fl_onground)
		return;

	auto offset = 0.f;
	if (last_pressed & InputBitMask_t::IN_MOVELEFT)
		offset += 90.f;
	if (last_pressed & InputBitMask_t::IN_MOVERIGHT)
		offset -= 90.f;
	if (last_pressed & InputBitMask_t::IN_FORWARD)
		offset *= 0.5f;
	else if (last_pressed & InputBitMask_t::IN_BACK)
		offset = -offset * 0.5f + 180.f;

	yaw += offset;

	auto velocity_angle = math::rad2deg(std::atan2f(velocity.y, velocity.x));
	if (velocity_angle < 0.0f)
		velocity_angle += 360.0f;

	if (velocity_angle < 0.0f)
		velocity_angle += 360.0f;

	velocity_angle -= floorf(velocity_angle / 360.0f + 0.5f) * 360.0f;

	const auto speed = velocity.length_2d();
	auto ideal = 0.f;

	if (speed > 0.f)
		ideal = std::clamp(math::rad2deg(std::atan2(15.f, speed)), 0.f, 90.f);

	auto correct = ideal;

	g_cs2->m_current_command->base->forwardmove = 0.f;
	const auto velocity_delta = math::normalize_yaw(yaw - velocity_angle);

	// get our viewangle change.
	auto delta = math::normalize_yaw(yaw - m_old_yaw);

	// convert to absolute change.
	auto abs_delta = std::abs(delta);

	// save old yaw for next call.
	m_old_yaw = yaw;

	auto rotate_movement = [](c_user_cmd* cmd, float target_yaw)
		{
			const float rot = math::deg2rad(cmd->base->view->angles.y - target_yaw);

			const float new_forward = std::cos(rot) * cmd->base->forwardmove - std::sin(rot) * cmd->base->sidemove;
			const float new_side = std::sin(rot) * cmd->base->forwardmove + std::cos(rot) * cmd->base->sidemove;

			cmd->buttons.buttonstate[0] &= ~(InputBitMask_t::IN_BACK | InputBitMask_t::IN_FORWARD | InputBitMask_t::IN_MOVELEFT | InputBitMask_t::IN_MOVERIGHT);
			cmd->buttons.buttonstate[1] &= ~(InputBitMask_t::IN_BACK | InputBitMask_t::IN_FORWARD | InputBitMask_t::IN_MOVELEFT | InputBitMask_t::IN_MOVERIGHT);

			cmd->base->forwardmove = std::clamp(new_forward, -1.f, 1.f);
			cmd->base->sidemove = std::clamp(new_side * -1.f, -1.f, 1.f);

			if (cmd->base->forwardmove > 0.f)
				cmd->buttons.buttonstate[0] |= InputBitMask_t::IN_FORWARD;
			else if (cmd->base->forwardmove < 0.f)
				cmd->buttons.buttonstate[0] |= InputBitMask_t::IN_BACK;

			if (cmd->base->sidemove > 0.f)
				cmd->buttons.buttonstate[0] |= InputBitMask_t::IN_MOVELEFT;
			else if (cmd->base->sidemove < 0.f)
				cmd->buttons.buttonstate[0] |= InputBitMask_t::IN_MOVERIGHT;
		};

	if (fabsf(velocity_delta) > 170.f && speed > 80.f || velocity_delta > correct && speed > 80.f)
	{
		yaw = correct + velocity_angle;
		g_cs2->m_current_command->base->sidemove = -1.f;
		rotate_movement(g_cs2->m_current_command, math::normalize_yaw(yaw));
		return;
	}

	m_switch_value = !m_switch_value;

	if (-correct <= velocity_delta || speed <= 80.f)
	{
		if (m_switch_value)
		{
			yaw = yaw - ideal;
			g_cs2->m_current_command->base->sidemove = -1.f;

		}
		else
		{
			yaw = ideal + yaw;
			g_cs2->m_current_command->base->sidemove = 1.f;

		}
	}
	else
	{
		yaw = velocity_angle - correct;
		g_cs2->m_current_command->base->sidemove = 1.f;
	}

	rotate_movement(g_cs2->m_current_command, math::normalize_yaw(yaw));
}