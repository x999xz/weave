// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void viewmodel_change(c_view_render* view_render) {
	if (!g_cs2->local_player->is_alive())
		return;

	auto viewmodel = g_cs2->local_player->viewmodel_services();

	if (!viewmodel)
		return;

	auto handle = viewmodel->view_model();

	if (!handle.is_valid())
		return;

	if (!g_user->IsActive(xorstr_("misc_viewmodel_changer"), xorstr_("misc_viewmodel_changer"), 0))
		return;

	c_csgo_viewmodel* vi = reinterpret_cast<c_csgo_viewmodel*>(Interfaces::entity_list->get_entity(handle.get_index()));

	if (!vi)
		return;

	vector vmorigin = view_render->view_setup.origin;
	vector vmangle = view_render->view_setup.angle;

	vector forward{}, right{}, up{};
	math::angle_vectors(vmangle, &forward, &right, &up);

	float z_ = g_user->IsActive(xorstr_("misc_viewmodel_z"), xorstr_("misc_viewmodel_z"), 0);
	float y_ = g_user->IsActive(xorstr_("misc_viewmodel_y"), xorstr_("misc_viewmodel_y"), 0);
	float x_ = g_user->IsActive(xorstr_("misc_viewmodel_x"), xorstr_("misc_viewmodel_x"), 0);

	vmorigin += (up * z_) + (forward * y_) + (right * -x_);

	vi->set_local_origin(vmorigin);
}

void __fastcall hooks::on_render_start::hook(c_view_render* view_render)
{
	g_cs2->m_latest_hook = LoggerHack::OnRenderStart;
	on_render_start_original(view_render);

	if (!Interfaces::engine->is_connected() || !Interfaces::engine->is_in_game())
		return;

	if (!g_cs2->local_player)
		return;

	viewmodel_change(view_render);

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8D 05 ?? ?? ?? ?? 48 8B D3 4C 8D 05" ).get_absolute_address( 3, 0 );

	memcpy(g_cs2->world_screen.data(), reinterpret_cast<float*>( pattern.get()), sizeof(float) * 16);
}

//89 54 24 10 4C 8B DC 53
void __fastcall hooks::setup_view::hook(c_view_render* view, int unk)
{
	g_cs2->m_latest_hook = LoggerHack::SetupView;
	setup_view_original(view, unk);

	if (g_cs2->local_player && g_cs2->local_player->is_alive() && g_user->IsActive(xorstr_("misc_norecoil"), xorstr_("misc_disable_light"), 3))
	{
		view->view_setup.angle.x = g_cs2->angle.x;
		view->view_setup.angle.y = g_cs2->angle.y;
	}
}