#pragma once

#include "../sdk.hpp"

class c_game_scene_node;

class c_csgo_viewmodel : public c_base_model_entity {
public:
	void set_local_origin(vector origin);
public:
	__forceinline c_handle handle_weapon() {
		return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0xEF8 );
	};
};