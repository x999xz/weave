#pragma once

#include "../sdk.hpp"

class c_utl_string {
public:
    const char* get() {
        return data;
    }

    const char* data;
};