// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "animation.h"
#include "../../renderer/render_manager.h"
#include <iostream>

void c_animation::plus(const float freq)
{
    timer = std::clamp(timer + ((1.f / freq) * g_render->get_delta_render()), 0.f, 1.f);
    base = std::clamp(Easing::InOutQuad(timer), 0.0, 1.0);
}

void c_animation::minus(const float freq)
{
    timer = std::clamp(timer - ((1.f / freq) * g_render->get_delta_render()), 0.f, 1.f);
    base = std::clamp(Easing::InOutQuad(timer), 0.0, 1.0);
}

void c_animation::run(const bool value, const float freq)
{
    if (value)
        plus(freq);
    else
        minus(freq);
}