// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../ragebot/ragebot.hpp"

bool c_fx_firebullet::run(c_cs_player_pawn* entity, vector& start, vector& end, float& damage, int& hitbox)
{
	if (!g_cs2->sv_penetration_type)
		return g_firebullet_cs2->run(entity, start, end, damage, hitbox);

	if (g_cs2->sv_penetration_type->GetValue<int>() == 2)
	{
		return g_firebullet_cs2->run(entity, start, end, damage, hitbox);
	}
	else
	{
		return false;
	}

	return false;
}