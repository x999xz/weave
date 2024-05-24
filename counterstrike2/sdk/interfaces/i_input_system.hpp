#pragma once

#include <cstdint>

class c_input_sys {
public:
    bool is_relative_mouse_mode() {
        // Offset in 'CInputSystem::SetRelativeMouseMode'.
        // 'CInputSystem::SetRelativeMouseMode' index is 76.
        // xref: SDL is %s relative mouse\n
        return *reinterpret_cast<bool*>((uintptr_t)(this) + 0x4D);
    }

    void* get_sdl_window() {
        // Offset in 'CInputSystem::DebugSpew'.
        // xref: "Current coordinate bias %s: %g,%g scale %g,%g\n".
        // find Plat_WindowToOsSpecificHandle first param
        return *reinterpret_cast<void**>((uintptr_t)(this) + 0x2678);
    }
};