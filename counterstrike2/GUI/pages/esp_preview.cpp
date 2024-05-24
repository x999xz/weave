// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"

void c_gui::esp_preview()
{
	const render_color_multi gradient(render_color(255, 139, 59, 50), render_color(255, 139, 59, 50), render_color(14, 14, 16, 50), render_color(14, 14, 16, 50));

	auto pos = m_window_pos_ + render_position(window_size.x + 20, 65);

	g_render->rect_filled(pos, render_size(240, 35), render_color(11, 11, 12), 0, 10.f, render_rounding_flags_::ROUND_RECT_TOP);
	g_render->rect_filled_multi(pos, render_size(240, 35), gradient, 10.f, render_rounding_flags_::ROUND_RECT_TOP);
	g_render->rect_filled(pos + render_position(0, 34), render_size(240, 396 - 35.f), render_color(13, 13, 14), 0, 10.f, render_rounding_flags_::ROUND_RECT_BOT);
	g_render->add_text(xorstr_("Preview"), pos + render_position(30, 10), render_color(221, 221, 221), g_render->get_font(0), 12);

	auto calc_name = g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, g_user->GetUsername().c_str());

	if (g_user->IsActive(xorstr_("esp_name"), xorstr_("esp_name"), 0)) {
		g_render->add_text(g_user->GetUsername(), pos + render_position(120, 65) - render_position(calc_name.x / 2, 0), render_color::white(), g_render->get_font(8), 8);
	}

	if (g_user->IsActive(xorstr_("esp_avatar"), xorstr_("esp_avatar"), 0)) {
		g_render->add_texture(pos + render_position(120, 65) - render_position(calc_name.x / 2, 0) - render_position(12, -1), render_size(10, 8), g_user->GetAvatar(g_user->GetUsername()));
	}

	auto box_size = render_size(140, 260);

	if (g_user->IsActive(xorstr_("esp_box"), xorstr_("esp_box"), 0))
		g_render->rect(pos + render_position(120, 80) - render_position(box_size.x / 2, 0), box_size, render_color::white());

	if (g_user->IsActive(xorstr_("esp_health"), xorstr_("esp_health"), 0)) {
		g_render->rect_filled(pos + render_position(120, 80) - render_position(box_size.x / 2, 0) - render_position(5, 0) - render_position(4.f, 0.f) + render_position(0, 30.f), render_size(4.f, box_size.y - 30.f), render_color::green());
		g_render->rect(pos + render_position(120, 80) - render_position(box_size.x / 2, 0) - render_position(5, 0) - render_position(4.f, 0.f), render_size(4.f, box_size.y), render_color::black());

		auto calc_hp = g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("63"));

		g_render->add_text(xorstr_("63"), pos + render_position(120, 80) - render_position(box_size.x / 2, 0) - render_position(7, 0) - render_position(4.f, 0.f) + render_position(0, 25.f) - render_position(5 + (calc_hp.x / 2), 0), render_color::white(), g_render->get_font(6), 10);
	}

	int padding = 0;

	if (g_user->IsActive(xorstr_("esp_flags_bomb"), xorstr_("esp_flags_bomb"), 0))
	{
		g_render->add_text("c4", pos + render_position(120, 80) + render_position(5 + (box_size.x / 2), padding), render_color(255, 255, 255, 255), g_render->get_font(6), 10);
		padding += g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("c4")).y + 2;
	}

	if (g_user->IsActive(xorstr_("esp_flags_kits"), xorstr_("esp_flags_bomb"), 1))
	{
		g_render->add_text("kits", pos + render_position(120, 80) + render_position(5 + (box_size.x / 2), padding), render_color(255, 255, 255, 255), g_render->get_font(6), 10);
		padding += g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("kits")).y + 2;
	}

	if (g_user->IsActive(xorstr_("esp_flags_armor"), xorstr_("esp_flags_bomb"), 2))
	{
			g_render->add_text(xorstr_("HK"), pos + render_position(120, 80) + render_position(5 + (box_size.x / 2), padding), render_color(255, 255, 255, 255), g_render->get_font(6), 10);
			padding += g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("HK")).y + 2;
	}

	if (g_user->IsActive(xorstr_("esp_flags_flashed"), xorstr_("esp_flags_bomb"), 3))
	{
		g_render->add_text(xorstr_("flashed"), pos + render_position(120, 80) + render_position(5 + (box_size.x / 2), padding), render_color(255, 255, 255, 255), g_render->get_font(6), 10);
		padding += g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("flashed")).y + 2;
	}

	if (g_user->IsActive(xorstr_("esp_flags_zeus"), xorstr_("esp_flags_bomb"), 4))
	{
		g_render->add_text("zeus", pos + render_position(120, 80) + render_position(5 + (box_size.x / 2), padding), render_color(255, 255, 255, 255), g_render->get_font(6), 10);
		padding += g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("zeus")).y + 2;
	}

	if (g_user->IsActive(xorstr_("esp_flags_defuser"), xorstr_("esp_flags_bomb"), 5))
	{
		g_render->add_text(xorstr_("defuser"), pos + render_position(120, 80) + render_position(5 + (box_size.x / 2), padding), render_color(255, 255, 255, 255), g_render->get_font(6), 10);
		padding += g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("defuser")).y + 2;
	}

	padding = 0;

	auto calc_awp = g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, xorstr_("AWP"));

	if (g_user->IsActive(xorstr_("esp_weapons_name"), xorstr_("esp_weapons_name"), 0))
	{
		g_render->add_text(xorstr_("AWP"), pos + render_position(120, 80 + (box_size.y + 5) + padding) - render_position(calc_awp.x / 2, 0), render_color(255, 255, 255, 255), g_render->get_font(6), 10);
		padding += calc_awp.y + 2;
	}

	if (g_user->IsActive(xorstr_("esp_weapons_icon"), xorstr_("esp_weapons_name"), 1))
	{
		auto calc_icon = g_render->get_font(5)->calc_text_size(12, FLT_MAX, FLT_MAX, xorstr_("Z"));
		g_render->add_text(xorstr_("Z"), pos + render_position(120, 80 + (box_size.y + 5) + padding) - render_position(calc_icon.x / 2, 0), render_color(255, 255, 255, 255), g_render->get_font(5), 12);
	}
}