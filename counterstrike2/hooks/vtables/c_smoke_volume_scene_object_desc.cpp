// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void __fastcall hooks::smoke_voxel_draw::hook(__int64 a1, __int64* a2, int a3, int a4, __int64 a5, __int64 a6)
{
	g_cs2->m_latest_hook = LoggerHack::SmokeVortexDraw;
	if (g_user->IsActive(xorstr_("misc_smoke_remove"), xorstr_("misc_disable_light"), 1))
		return;

	return smoke_voxel_draw_original(a1, a2, a3, a4, a5, a6);
}