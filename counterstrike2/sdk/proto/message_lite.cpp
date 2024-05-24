// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

bool message_lite::serialize_partial_to_array(std::uintptr_t* data, int size)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 18 55 56 57 48 81 EC 90 00 00 00 48" );
	return pattern.as<bool(__fastcall*)(message_lite*, std::uintptr_t*, int)>()(this, data, size);
}

void message_lite::parse_partial_to_array(const void* data, int size)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 48 89 6C 24 18 48 89 7C 24 20 41 56 48 83 EC 20 48 BF" );
	return pattern.as<void(__fastcall*)(intptr_t*, const void*, int)>()(&_internal_metadata_.kUnknownFieldsTagMask, data, size);
}

std::uintptr_t* message_lite::merge(void* to, std::uintptr_t* hyeta)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 20 55 56 57 48 83 EC 30 49" );
	return pattern.as<std::uintptr_t * (__fastcall*)(void*, intptr_t*, void*)>()(to, &_internal_metadata_.kUnknownFieldsTagMask, nullptr);
}