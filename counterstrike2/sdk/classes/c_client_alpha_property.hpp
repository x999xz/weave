#pragma once

#include "../sdk.hpp"

class c_client_alpha_property
{
public:
    __forceinline int alpha() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + g_pSchemaOffset->m_nAlpha); //pl
    };
};