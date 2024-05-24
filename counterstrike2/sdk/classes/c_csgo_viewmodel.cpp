// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"
#include "../../hooks/hooks.hpp"

void c_csgo_viewmodel::set_local_origin(vector origin)
{
	using function_t = void(__fastcall*)(c_csgo_viewmodel*, vector);

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 57 48 83 EC 40 48 8B 01 48 8B FA 48" );
	pattern.as<function_t>()(this, origin);
}