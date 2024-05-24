// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void hooks::send_move_internal::hook(std::uintptr_t* a1, std::uintptr_t* a2)
{
	g_cs2->m_latest_hook = LoggerHack::SendMoveInternal;
	g_cs2->angle = Interfaces::csgo_input->view_angle;
	send_move_internal_original(a1, a2);
}