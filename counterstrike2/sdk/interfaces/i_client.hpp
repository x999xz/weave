#pragma once

#include <cstdint>
#include "../math/vector.hpp"
#include "../../utilities/utilities.hpp"

class i_client
{
public:
	float get_lerp_time() {
		return CALL_VIRTUAL(float, 166, this);
	}

    c_scene_debug_overlay* get_scene_debug_overlay()
	{
		//xref: CDebugOverlayGameSystem lea rdx
		// https://imgur.com/864KioY
		// https://imgur.com/MYz5ScT
		using function_t = c_scene_debug_overlay*(__thiscall*)(i_client*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[155](this);
	}
};