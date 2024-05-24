#pragma once

#include "../sdk.hpp"

class c_cs_player_pawn;

class c_game_scene_node
{
public:
	__forceinline vector vec_origin() {
		return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0x550 );
	};
	__forceinline vector abs_origin() {
		return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0xC8);
	};
	__forceinline bool dormant() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0xE7 );
	};
	__forceinline c_game_scene_node* parent() {
		return *reinterpret_cast<c_game_scene_node**>(reinterpret_cast<std::uint64_t>(this) + 0x38 );
	};
	__forceinline c_cs_player_pawn* owner() {
		return *reinterpret_cast<c_cs_player_pawn**>(reinterpret_cast<std::uint64_t>(this) + 0x30 );
	};
public:
	void set_mesh_group_mask(uint64_t meshGroupMask);
public:
	c_skeleton_instance* get_skeleton_instance();
};