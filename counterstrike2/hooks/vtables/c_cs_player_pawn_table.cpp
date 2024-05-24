// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

bool __fastcall hooks::show_legs::hook(c_cs_player_pawn* pawn)
{
	g_cs2->m_latest_hook = LoggerHack::ShowLegs;
	if (!Interfaces::csgo_input->can_thirdperson && pawn == g_cs2->local_player && g_user->IsActive(xorstr_("misc_remove_legs"), xorstr_("misc_disable_light"), 5))
		return false;

	return show_legs_original(pawn);
}