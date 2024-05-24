#include "misc.h"
#include "../ragebot/ragebot.hpp"

void c_misc::penetration_crosshair() {
	if (!g_cs2->local_player->get_weapon_active() || !g_cs2->local_player->get_weapon_active()->get_weapon_data())
		return;

	vector fwd;
	math::angle_vectors(Interfaces::csgo_input->view_angle, fwd);
	auto point = g_cs2->eye_position + (fwd * g_cs2->local_player->get_weapon_active()->get_weapon_data()->range());
	auto direction = (point - g_cs2->eye_position).normalized();
	direction *= g_cs2->local_player->get_weapon_active()->get_weapon_data()->range();
	float damage = 0;
	int hitbox = -1;

	g_fx_firebullet->run(nullptr, g_cs2->eye_position, direction, damage, hitbox);
}