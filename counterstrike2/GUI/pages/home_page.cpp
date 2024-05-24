// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../core.hpp"
#include "../gui.h"
#include "../../utilities/cloud/user.h"
#include "../utilities/hash.h"
#include <tinyformat/tinyformat.h>

void clip_board(std::string str)
{
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, str.size() + 1 * sizeof(CHAR));;
	LPVOID gl = GlobalLock(h);

	memcpy(gl, str.data(), str.size() * sizeof(CHAR));

	GlobalUnlock(gl);

	OpenClipboard(NULL); // hWnd is set to NULL
	EmptyClipboard(); // Sets clipboard ownership to someone don't know
	SetClipboardData(CF_TEXT, h);  // Successfully data to clipboard!
	CloseClipboard();
}

std::string get_time() {
	return xorstr_( "Lifetime" );
}

void c_gui::home_page()
{
	const render_position position = m_window_pos_;
	const render_color_multi gradient(render_color(255, 139, 59, 50), render_color(255, 139, 59, 50), render_color(14, 14, 16, 50), render_color(14, 14, 16, 50));
	const render_color_multi shadow(render_color(13, 13, 14, 0).override_alpha(g_render->get_override_alpha()), render_color(13, 13, 14, 0).override_alpha(g_render->get_override_alpha()), render_color(13, 13, 14, 255).override_alpha(g_render->get_override_alpha()), render_color(13, 13, 14, 255).override_alpha(g_render->get_override_alpha()));
	const render_position calc_text = g_render->get_font(2)->calc_text_size(13, FLT_MAX, FLT_MAX, g_user->GetUsername().c_str());

	std::uint64_t hash_search = std::hash<std::string>()(xorstr_("search"));
	std::uint64_t hash_configs = std::hash<std::string>()(xorstr_("configs"));

	begin_group(xorstr_("User Profile"), render_size(365, 102), false);
	{
		auto group_position = get_position();

		g_render->add_text(g_user->GetUsername(), group_position + render_position(60, 18), render_color(221, 221, 221), g_render->get_font(2), 13);
#ifdef _ALPHAD
		g_render->add_text(xorstr_("ALPHA"), group_position + render_position(60, 18) + render_position(calc_text.x + 5, 0), render_color(255, 139, 59), g_render->get_font(3), 13);
#elif _DEV
		g_render->add_text(xorstr_("DEV"), group_position + render_position(60, 18) + render_position(calc_text.x + 5, 0), render_color(255, 139, 59), g_render->get_font(3), 13);
#endif
		g_render->add_text(xorstr_("days left: ") + get_time(), group_position + render_position(60, 21 + g_render->get_font(2)->calc_text_size(13, FLT_MAX, FLT_MAX, "nicesrc" ).y ), render_color( 86, 86, 87 ), g_render->get_font( 3 ), 11 );
		//g_render->add_texture_circle(group_position + render_position(14, 14), 17, g_user->GetAvatar(g_user->GetUsername()) == -1 ? 11 : g_user->GetAvatar(g_user->GetUsername()), true, render_color(255, 139, 59));
	}
	end_group();

	begin_group(xorstr_("Search"), render_size(365, 102), false);
	{

	}
	end_group();

	// scripts soon...
	{
		//render_position start = position + render_position(10, 177) + render_size(134, 0) + render_position(10, 0);
		//render_size size = render_size(90, 23);

		//bool is_hovered = helper.is_hovered(m_mouse_pos_, rect_(*reinterpret_cast<vec2_t*>(&start), *reinterpret_cast<vec2_t*>(&size)));

		//animation["button_scripts"].run(is_hovered);

		//g_render->rect_filled(position + render_position(10, 177) + render_size(134, 0) + render_position(10, 0), render_size(90, 23), render_color(255, 139, 59, 255 * animation["button_scripts"].base), 0, 10.f);
		//g_render->add_text("Scripts", position + render_position(10, 181) + render_size(134, 0) + render_position(10, 0) + render_position(30, 0), render_color(11, 11, 12), g_render->get_font(0), 12);
		//g_render->add_texture(position + render_position(10, 183) + render_size(134, 0) + render_position(10, 0) + render_position(14, 0), render_size(11, 11), 8);
	}

	
}