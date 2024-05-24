// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "c_game_particle_manager_system.hpp"
#include "../../hooks/hooks.hpp"

void c_game_particle_manager_system::create_effect_index(unsigned int* effect_index, particle_effect* effect_data)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 57 48 83 EC 20 49 8B 00" );
	pattern.as<void(__fastcall*)(c_game_particle_manager_system*, unsigned int*, particle_effect*)>()(this, effect_index, effect_data);
}

void c_game_particle_manager_system::create_effect(unsigned int effect_index, int unk, void* clr, int unk2)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 83 EC 58 F3 41 0F 10 51" );
	pattern.as<void(__fastcall*)(c_game_particle_manager_system*, unsigned int, int, void*, int)>()(this, effect_index, unk, clr, unk2);
}

void c_game_particle_manager_system::unk_function(int effect_index, unsigned int unk, const strong_handle<c_particle_snapshot>* particle_snapshot)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 74 24 10 57 48 83 EC 30 4C 8B D9 49 8B F9 33 C9 41 8B F0 83 FA FF 0F" );
	pattern.as<bool(__fastcall*)(c_game_particle_manager_system*, int, unsigned int, const strong_handle<c_particle_snapshot>*)>()(this, effect_index, unk, particle_snapshot);
}