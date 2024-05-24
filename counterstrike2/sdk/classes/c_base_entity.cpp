// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"
#include "../../hooks/hooks.hpp"

void c_base_entity::set_model(const char* name) {

    using function_t = void* (__fastcall*)(c_base_entity*, const char*);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 48 89 7C 24 20 55 48 8B EC 48 83 EC 50" );
    pattern.as<function_t>()(this, name);
}

void c_base_entity::update_subclass() {
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 30 48 8B 41 10 48 8B D9 8B 50 30" );
    pattern.as<void(__fastcall*)(void*)>()(this);
}