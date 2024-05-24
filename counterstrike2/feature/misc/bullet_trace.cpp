// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "misc.h"

void c_misc::add_bullet_trace(vector start, vector end, color_t clr_)
{
	auto& bullet = g_cs2->bullets.emplace_back();

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "E8 ? ? ? ? 40 80 FF 03" ).get_absolute_address(1, 0);


	if (!Interfaces::m_game_particle_manager_system)
		Interfaces::m_game_particle_manager_system = pattern.as<c_game_particle_manager_system * (__fastcall*)()>()();

	particle_effect particle_effect_{};
	particle_effect_.name = "particles/entity/spectator_utility_trail.vpcf";
	particle_effect_.pad[0] = 8;
	Interfaces::m_game_particle_manager_system->create_effect_index(&bullet.effect_index, &particle_effect_);
	particle_color clr = { float(clr_.get_red()), float(clr_.get_green()), float(clr_.get_blue()) };
	Interfaces::m_game_particle_manager_system->create_effect(bullet.effect_index, 16, &clr, 0);

	bullet.particle_data_ = {};

	auto dir = (end - start);
	auto stage_2 = start + (dir * 0.3f);
	auto stage_3 = start + (dir * 0.5f);

	vector positions_[] = { start,stage_2, stage_3,end };

	for (int i{}; i < sizeof(positions_) / sizeof(vector); i++) {

		particle_information particle_info{};
		particle_info.time = 4.f;
		particle_info.width = 1.5f;
		particle_info.unk2 = 1.f;
		Interfaces::m_game_particle_manager_system->create_effect(bullet.effect_index, 3, &particle_info, 0);

		bullet.positions = new vector[i + 1];
		bullet.times = new float[i + 1];

		for (int j{}; j < i + 1; j++) {
			bullet.positions[j] = positions_[j];
			bullet.times[j] = Interfaces::globals->interval_per_ticks * float(j);
		}

		bullet.particle_data_.positions = bullet.positions;
		bullet.particle_data_.times2 = bullet.times;

		Interfaces::m_particle_manager->create_snapshot(&bullet.handle_snapshot_particle);

		Interfaces::m_game_particle_manager_system->unk_function(bullet.effect_index, 0, &bullet.handle_snapshot_particle);
		Interfaces::m_particle_manager->draw(&bullet.handle_snapshot_particle, i + 1, &bullet.particle_data_);

		delete[] bullet.positions;
		delete[] bullet.times;
	}
}