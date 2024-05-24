// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void __fastcall hooks::world_render::hook(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, std::uintptr_t* a4, int a5, int a6)
{
	return world_render_original(a1, a2, a3, a4, a5, a6);
}