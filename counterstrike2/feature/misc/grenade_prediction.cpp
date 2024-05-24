// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "misc.h"
#include "../../sdk/classes/c_grenade_trace.h"

void c_misc::grenade_prediction()
{
	if (!g_cs2->local_player || !g_cs2->local_player->is_alive())
		return;

	if (!g_cs2->local_player->get_weapon_active())
		return;

	if (!g_cs2->local_player->get_weapon_active()->is_grenade())
	{
		g_misc->grenade_prediction_m.lock();
		g_misc->lines.clear();
		g_misc->grenade_prediction_m.unlock();
		return;
	}

	//if (!(cmd->buttons.buttonstate[0] & 1) && !(cmd->buttons.buttonstate[0] & 2048))
	//	return;

	auto grenade_ = (c_base_cs_grenade*)g_cs2->local_player->get_weapon_active();

	vector angle{}, angle2{};

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 85 D2 0F 84 EB 03" );
	pattern.as<void(__fastcall*)(c_base_cs_grenade*, c_cs_player_pawn*, vector&, vector&)>()(grenade_, g_cs2->local_player, g_misc->direction_grenade[0], g_misc->direction_grenade[1]);
}