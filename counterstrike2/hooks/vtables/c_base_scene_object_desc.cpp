// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void __fastcall hooks::base_draw::hook(std::uintptr_t* a1, std::uintptr_t* a2, c_scene_data* a3, int a4, int a5, std::uint32_t* a6, std::uintptr_t* a7, std::uintptr_t* a8)
{
	Interfaces::material_system->SetColor(a3, color_t(0, 0, 0, 255));
	return base_draw_original(a1, a2, a3, a4, a5, a6,a7,a8);
}