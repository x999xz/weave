// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "core.hpp"

std::uintptr_t c_module_system::get_client()
{
	return g_cs2->m_modules[FNV32("client")];
}

std::uintptr_t c_module_system::get_server()
{
	return g_cs2->m_modules[FNV32("server")];
}

std::uintptr_t c_module_system::get_panorama()
{
	return g_cs2->m_modules[FNV32("panorama")];
}

std::uintptr_t c_module_system::get_engine2()
{
	return g_cs2->m_modules[FNV32("engine2")];
}

std::uintptr_t c_module_system::get_tier0()
{
	return g_cs2->m_modules[FNV32("tier0")];
}

std::uintptr_t c_module_system::get_animationsystem()
{
	return g_cs2->m_modules[FNV32("animationsystem")];
}

std::uintptr_t c_module_system::get_gameoverlayrenderer64()
{
	return g_cs2->m_modules[FNV32("gameoverlayrenderer64")];
}

std::uintptr_t c_module_system::get_materialsystem2()
{
	return g_cs2->m_modules[FNV32("materialsystem2")];
}

std::uintptr_t c_module_system::get_resourcesystem()
{
	return g_cs2->m_modules[FNV32("resourcesystem")];
}

std::uintptr_t c_module_system::get_scenesystem()
{
	return g_cs2->m_modules[FNV32("scenesystem")];
}

std::uintptr_t c_module_system::get_render_system()
{
	return g_cs2->m_modules[FNV32("render_system")];
}

std::uintptr_t c_module_system::get_world_render()
{
	return g_cs2->m_modules[FNV32("world_render")];
}

std::uintptr_t c_module_system::get_schemasystem()
{
	return g_cs2->m_modules[FNV32("schemasystem")];
}

std::uintptr_t c_module_system::get_sdl3()
{
	return g_cs2->m_modules[FNV32("sdl3")];
}

std::uintptr_t c_module_system::get_steam_api64()
{
	return g_cs2->m_modules[FNV32("steam_api64")];
}

std::uintptr_t c_module_system::get_input_system()
{
	return g_cs2->m_modules[FNV32("inputsystem")];
}

std::uintptr_t c_module_system::get_file_system()
{
	return g_cs2->m_modules[FNV32("filesystem_stdio")];
}

std::uintptr_t c_module_system::get_network_system()
{
	return g_cs2->m_modules[FNV32("network_system")];
}


std::uintptr_t c_module_system::get_particles()
{
	return g_cs2->m_modules[FNV32("particles")];
}

std::uintptr_t c_module_system::get_localize()
{
	return g_cs2->m_modules[FNV32("localize")];
}