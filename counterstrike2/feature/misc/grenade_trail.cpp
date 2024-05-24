// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "misc.h"
#include "../utilities/cloud/user.h"

void c_misc::add_grenade_trail(vector* points, int size, float time)
{
	auto& bullet = g_cs2->bullets.emplace_back();

	particle_effect particle_effect_{};
	particle_effect_.name = "particles/entity/spectator_utility_trail.vpcf";
	particle_effect_.pad[0] = 8;
	Interfaces::m_game_particle_manager_system->create_effect_index(&bullet.effect_index, &particle_effect_);
	auto clr_ = color_t(g_user->GetConfig()[xorstr_("misc_grenade_trail_color")]);
	particle_color clr = { (float)clr_.get_red(), (float)clr_.get_green(), (float)clr_.get_blue() };
	Interfaces::m_game_particle_manager_system->create_effect(bullet.effect_index, 16, &clr, 0);

	bullet.particle_data_ = {};
	bullet.positions = new vector[size];
	bullet.times = new float[size];

	int current_size = 0;

	for (int i{}; i < size; i++)
	{

		particle_information particle_info{};
		particle_info.time = time;
		particle_info.width = 1.f;
		particle_info.unk2 = 0x3F800000;
		Interfaces::m_game_particle_manager_system->create_effect(bullet.effect_index, 1, &particle_info, 0);

		bullet.positions[i] = points[i];
		bullet.times[i] = 0.00f + (Interfaces::globals->interval_per_ticks * float(i));
		current_size++;

		bullet.particle_data_.positions = bullet.positions;
		bullet.particle_data_.times = bullet.times;

		Interfaces::m_particle_manager->create_snapshot(&bullet.handle_snapshot_particle);

		Interfaces::m_game_particle_manager_system->unk_function(bullet.effect_index, 0, &bullet.handle_snapshot_particle);
		Interfaces::m_particle_manager->draw(&bullet.handle_snapshot_particle, current_size, &bullet.particle_data_);

	}

	delete[] bullet.positions;
	delete[] bullet.times;
}