#pragma once

#include "../sdk.hpp"

class c_body_component_base_anim_graph
{
public:
    c_base_anim_graph_controller* get_anim_controller()
    {
        return (c_base_anim_graph_controller*)(std::uintptr_t(this) + 0x460);
    }
};