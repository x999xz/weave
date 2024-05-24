#pragma once
#include <algorithm>
#include "easing.hpp"

class c_animation
{
public:
    float timer;
    float base;

    void plus(const float freq = 0.2f);

    void minus(const float freq = 0.2f);

    void run(const bool value, const float freq = 0.2f);
};