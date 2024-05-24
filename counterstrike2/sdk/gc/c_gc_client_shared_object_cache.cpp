// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk/sdk.hpp"

c_gc_client_shared_object_type_cache* c_gc_client_shared_object_cache::create_base_type_cache(int nClassID)
{
    using function_t = c_gc_client_shared_object_type_cache * (__fastcall*)(c_gc_client_shared_object_cache*, int);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 20 4C 8B 49 18" );
    return pattern.as<function_t>()(this, nClassID);
}