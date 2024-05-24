// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk/sdk.hpp"

c_gc_client_shared_object_cache* c_gc_client::find_so_cache(soid_t ID, bool bCreateIfMissing)
{
    using function_t = c_gc_client_shared_object_cache * (__fastcall*)(c_gc_client*, soid_t, bool);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "E8 ? ? ? ? 48 8B F0 48 85 C0 74 0E 4C 8B C3" ).get_absolute_address(1,0);
    return pattern.as<function_t>()(this, ID, bCreateIfMissing);
}