// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "channel_system.h"
#include "../core.hpp"

void c_channel_system::init()
{
	weave_channel = create_channel("Weave", color_channel(0, 255, 0));

	//add_log(weave_channel, "weave inject!");
}

std::uintptr_t* c_channel_system::create_channel(const char* str, color_channel clr)
{
	using function_t = std::uintptr_t* (__fastcall*)(const char*, std::uintptr_t, int, int, std::uint32_t);
	//static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 44 0F" );
	return g_cs2->m_patterns[FNV32("register_channel")].as<function_t>()(str, 0 /*add tag*/, 0, 2, clr.get_hex());
}

bool c_channel_system::is_enable(std::uintptr_t* channel)
{
	using function_t = bool(__fastcall*)(std::uintptr_t*, int);
	//static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 44 0F" );
	return g_cs2->m_patterns[FNV32("is_channel_enable")].as<function_t>()(channel, 2);
}

void c_channel_system::add_log(std::uintptr_t* channel, const char* txt)
{
	if (!is_enable(channel))
		return;

	using function_t = void(__fastcall*)(std::uintptr_t*, int, const char*);
	//static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 44 0F" );
	g_cs2->m_patterns[FNV32("add_log_channel")].as<function_t>()(channel, 2, txt);
}