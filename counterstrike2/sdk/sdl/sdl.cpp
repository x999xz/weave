// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "sdl.hpp"

#include <Windows.h>
#include "../../core.hpp"

void sdl::set_relative_mouse_mode(bool mode)
{
	using function_t = std::uint64_t(__stdcall*)(bool);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_input_system( ), "48 89 5C 24 ? 57 48 83 EC 20 0F B6 FA 48 8B D9 FF 15" );
	function_t fn = pattern.as<function_t>();

	if (!fn)
		return;

	fn(mode);
}

void sdl::set_window_polling_mode(void* window, bool mode)
{
	using function_t = void(__stdcall*)(void*, bool);

	function_t fn = g_cs2->m_patterns[FNV32("set_window_grab")].as<function_t>();

	if (!fn)
		return;

	fn(window, mode);
}

void sdl::set_mouse_warp_position(void* window, std::int32_t x, std::int32_t y)
{
	using function_t = void(__stdcall*)(void*, std::int32_t, std::int32_t);
	function_t fn = g_cs2->m_patterns[FNV32("warp_mouse_in_window")].as<function_t>();

	if (!fn)
		return;

	fn(window, x, y);
}
