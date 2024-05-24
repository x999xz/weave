// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

//40 53 48 81 EC 80 00 00 00 48 8B D9 E8 ?? ?? ?? ?? 48 85
float hooks::get_fov::hook(c_player_camera_services* camera)
{
	g_cs2->m_latest_hook = LoggerHack::GetFOV;
	if (g_user->IsActive(xorstr_("misc_fov"), xorstr_("misc_fov"), 0) == 90)
		return get_fov_original(camera);

	return g_user->IsActive(xorstr_("misc_fov"), xorstr_("misc_fov"),0);
}

float hooks::get_fov2::hook(c_player_camera_services* camera)
{
	g_cs2->m_latest_hook = LoggerHack::GETFOV2;
	if (g_user->IsActive(xorstr_("misc_fov"), xorstr_("misc_fov"), 0) == 90)
		return get_fov2_original(camera);

	return g_user->IsActive(xorstr_("misc_fov"), xorstr_("misc_fov"), 0);
}