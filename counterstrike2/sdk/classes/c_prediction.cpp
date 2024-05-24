// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

void c_prediction::update(int reason, int delta_tick)
{
    using function_t = void(__fastcall*)(c_prediction*, int, int);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 55 56 41 56 48 81 EC 80" );
    pattern.as<function_t>()(this, reason, delta_tick);
}