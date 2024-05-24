#pragma once

#include "../sdk.hpp"

class c_render_game_system
{
public:
	float* get_world_matrices()
	{
		using function_t = float*(__thiscall*)(c_render_game_system*, int);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[55](this, 0);
	}
};