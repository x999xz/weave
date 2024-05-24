// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

const char* c_econ_item_view::get_item_name(bool uncustomized)
{
	using function_t = const char* (__fastcall*)(void*, bool);

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "E8 ?? ?? ?? ?? 4C 8B C0 EB 17" ).get_absolute_address(1,0);
	return pattern.as<function_t>()(this, uncustomized);
}