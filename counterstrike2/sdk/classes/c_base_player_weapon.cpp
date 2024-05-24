// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

float c_base_player_weapon::get_spread()
{
	using function_t = float(__fastcall*)(c_base_player_weapon*);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 83 EC 38 48 63 91" );
	return pattern.as<function_t>()(this);
}

float c_base_player_weapon::get_accuracy()
{
	using function_t = float(__fastcall*)(c_base_player_weapon*);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 57 48 81 EC D0 00 00 00 0F" );
	return pattern.as<function_t>()(this);
}

void c_base_player_weapon::update_accuracy()
{
	using function_t = void(__fastcall*)(c_base_player_weapon*);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 18 57 48 83 EC 50 48 8B F9" );
	pattern.as<function_t>()(this);
}