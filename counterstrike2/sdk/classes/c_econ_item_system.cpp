// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

bool c_paint_kit::uses_legacy_model()
{
	return *(bool*)(std::uintptr_t(this) + 0xB2);
}

CEconItemAttributeDefinition* c_econ_item_system::get_attribute_definition_by_name(const char* name)
{
	using function_t = CEconItemAttributeDefinition*(__fastcall*)(const char**);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 56 48 83 EC 20 48 8B D9 E8" );
	return pattern.as<function_t>()(&name);
}