// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

void c_skeleton_instance::calc_world_space_bones(int bone_mask)
{
	using function_t = void(__fastcall*)(c_skeleton_instance*, int);
	static auto pattern1 = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC D0" );
	auto pattern = pattern1;
	pattern.as<function_t>()(this, bone_mask);
}