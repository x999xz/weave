// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

std::uint32_t c_model::num_bones()
{
	using function_t = std::uint32_t(__fastcall*)(c_model*);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 85 C9 75 04 83 C8 FF C3 8B" );
	return pattern.as<function_t>()(this);
}

std::uint32_t c_model::bone_flags(int index)
{
	using function_t = std::uint32_t(__fastcall*)(c_model*, int);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "85 D2 78 16 3B 91" );
	return pattern.as<function_t>()(this, index);
}

std::uint32_t c_model::bone_parent(int index)
{
	using function_t = std::uint32_t(__fastcall*)(c_model*, int);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "85 D2 78 17 3B 91 78" );
	return pattern.as<function_t>()(this, index);
}