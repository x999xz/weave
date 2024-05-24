// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

bool i_trace::trace_shape(c_ray* ray, const vector& start, const vector& end, c_trace_filter* filter, c_game_trace* trace)
{
	using function_t = bool(__fastcall*)(i_trace*, c_ray*, const vector&, const vector&, c_trace_filter*, c_game_trace*);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 48 89 4C 24 08 55 41 54 41 55 41 56 41 57 48 8D" );
	bool ret = pattern.as<function_t>()(this, ray, start, end, filter, trace);;
	return ret;
}

int i_trace::point_contents(const vector& end, int mask, __int16 mask2)
{
	using function_t = int(__fastcall*)(i_trace*, const vector&, __int64, __int16);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 83 EC 38 F3 0F 10 15 ?? ?? ?? ?? 66" );
	return pattern.as<function_t>()(this, end, mask, mask2);
}

bool i_trace::clip_ray_to_entity(c_ray* ray, const vector& start, const vector& end, c_cs_player_pawn* player, c_trace_filter* filter, c_game_trace* trace)
{
	using function_t = bool(__fastcall*)(i_trace*, c_ray*, const vector&, const vector&, c_cs_player_pawn*, c_trace_filter*, c_game_trace*);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 54 41 56 41 57 48 81 EC C0 00 00 00 48 8B 9C" );
	return pattern.as<function_t>()(this, ray, start, end, player, filter, trace);
}