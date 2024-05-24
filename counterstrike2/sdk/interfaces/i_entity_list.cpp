// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

c_cs_player_pawn* i_entity_list::get_local_player()
{
	add_trace(__PRETTY_FUNCTION__);
	return get_split_screen_view_player(0);
}

c_cs_player_pawn* i_entity_list::get_split_screen_view_player(int index)
{
	add_trace(__PRETTY_FUNCTION__);
	using function_t = c_cs_player_pawn * (__fastcall*)(int index);

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 83 EC 28 83 F9 FF 75 17 48 8B 0D ?? ?? ?? ?? 48 8D 54 24 30 48 8B 01 FF 90 ?? ?? ?? ?? 8B 08 48 63 C1 48 8D 0D ?? ?? ?? ?? 48 8B 0C" );

	return pattern.as<function_t>()(index);
}