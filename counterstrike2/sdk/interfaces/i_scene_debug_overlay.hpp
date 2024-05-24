#pragma once

#include <cstdint>
#include "../math/vector.hpp"
#include "../../utilities/utilities.hpp"

class c_scene_debug_overlay {
public:
    void add_box(const vector& end, const vector& mins, const vector& maxs, const vector& a3, color_t clr)
    {
        using function_t = void(__thiscall*)(c_scene_debug_overlay*, const vector&, const vector&, const vector&, const vector&, int, int, int, int, double);
		(*reinterpret_cast<function_t**>(std::uintptr_t(this)))[47](this, end, mins, maxs, a3, clr.get_red(), clr.get_green(), clr.get_blue(), clr.get_alpha(), static_cast<double>(4.f));
    }
};