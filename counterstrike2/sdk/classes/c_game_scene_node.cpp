// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "c_game_scene_node.hpp"

void c_game_scene_node::set_mesh_group_mask(uint64_t meshGroupMask) {
	
	using function_t = void(__fastcall*)(c_game_scene_node*, uint64_t);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8D 99 60" );
	pattern.as<function_t>()(this, meshGroupMask);
}

c_skeleton_instance* c_game_scene_node::get_skeleton_instance()
{
	return reinterpret_cast<c_skeleton_instance*(__thiscall*)(c_game_scene_node*)>(g_utils->get_virtual(this, 8))(this);
}