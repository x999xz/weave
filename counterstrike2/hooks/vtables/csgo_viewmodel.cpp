// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

//48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 48 8D 6C 24 B0
void __fastcall hooks::calc_viewmodel_view::hook(std::uintptr_t* a1, std::uintptr_t* a2, vector eye_position, vector eye_angle, char a5)
{
	g_cs2->m_latest_hook = LoggerHack::CalcViewmodelView;
	if (g_user->IsActive(xorstr_("misc_norecoil"), "misc_disable_light", 3))
	{
		auto angle_viewmodel = g_cs2->angle;
		math::normalize_angles(angle_viewmodel);
		eye_angle.x = angle_viewmodel.x;
		eye_angle.y = angle_viewmodel.y;
	}
	return calc_viewmodel_view_original(a1, a2, eye_position, eye_angle, a5);
}