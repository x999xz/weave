// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

uintptr_t C_KeyString::FindKey(const char* name) {
    using type = uintptr_t(__fastcall*)(const char*, int, int);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_particles( ), "48 89 5C 24 08 57 48 81 EC C0 00 00 00 33 C0 8B" );
    type fn = pattern.as<type>(); // particles.dll E8 ? ? ? ? 80 7F 1A 00 + 1
    return fn(name, 0x12, 0x31415926);
}

void c_resource_system::enumerate_material(std::uint64_t hash, resource_array_t* array, std::uint8_t flags)
{
    using function_t = void(__fastcall*)(c_resource_system*, std::uint64_t, resource_array_t*, std::uint8_t);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_resourcesystem( ), "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 30 41 8B" );
    pattern.as<function_t>()(this, hash, array, flags);
}

void i_material_system::SetMaterialShaderType(void* data, const char* shader_name)
{
    using type = void(__fastcall*)(void*, C_KeyString, const char*, int);

    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_particles( ), "48 89 5C 24 10 48 89 6C 24 18 56 57 41 54 41 56 41 57 48 83 EC 30 0F B6 01 45 0F B6 F9 8B 2A 4D 8B E0 4C 8B 72 08 48 8B F9 C0 E8 02 24 0F 3C 09 74 0A 41 B0 0B B2 09 E8 ?? ?? ?? ?? 0F B6 07 33 DB C0 E8 02 24 0F 3C 09 75 06 48 8B 77 08 EB 03 48 8B F3 4C 8D 44 24 60 C7 44 24 60 FF FF FF FF 48 8D 54 24 20 89 6C 24 20 48 8B CE 4C 89 74 24 28 E8 ?? ?? ?? ?? 8B D0 83 F8 FF 75 1E 45 33 C9 89 6C 24 20 4C 8D 44 24 20 4C 89 74 24 28 48 8B D7 48 8B CE E8 ?? ?? ?? ?? 8B D0 0F B6 0F C0 E9 02 80 E1 0F 80 F9 09 75 06 48 8B 4F 08 EB 03 48 8B CB 8B 41 3C 85 C0 74 0C 48 8D 59 40 83 F8 08 76 03 48 8B 1B 48 63 C2 4D" );
    type fn = pattern.as<type>(); // particles.dll  E8 ? ? ? ? 48 8D B7 ? ? ? ? + 1

    C_KeyString shader((const char*)xorstr_("shader"), 0x162C1777);
    fn(data, shader, shader_name, 0x18);
}

void i_material_system::SetMaterialFunctions(void* data, const char* functions_name, int value)
{
    using type = void(__fastcall*)(void*, C_KeyString, int, int);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_particles( ), "48 89 5C 24 08 48 89 6C 24 10 56 57 41 54" );
    type set_other = pattern.as<type>(); //particles.dll  E8 ? ? ? ? 49 C1 E5 21 + 1

    C_KeyString functions(functions_name, true);

    set_other(data, functions, value, 0x13);
}