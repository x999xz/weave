// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"
#include <bitset>
#include <chrono>
#include <ios>
#include <sstream>

typedef struct {
	double h;       // angle in degrees
	double s;       // a fraction between 0 and 1
	double v;       // a fraction between 0 and 1
} hsv;

hsv rgb2hsv(util::draw::color in)
{
	hsv         out;
	double      min, max, delta;

	float r = in.r() / 255.f;
	float g = in.g() / 255.f;
	float b = in.b() / 255.f;

	min = r < g ? r : g;
	min = min < b ? min : b;

	max = r > g ? r : g;
	max = max > b ? max : b;

	out.v = max;                                // v
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; // undefined, maybe nan?
		return out;
	}
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0              
		// s = 0, h is undefined
		out.s = 0.0;
		out.h = NAN;                            // its now undefined
		return out;
	}
	if (r >= max)                           // > is bogus, just keeps compilor happy
		out.h = (g - b) / delta;        // between yellow & magenta
	else
		if (g >= max)
			out.h = 2.0 + (b - r) / delta;  // between cyan & yellow
		else
			out.h = 4.0 + (r - g) / delta;  // between magenta & cyan

	out.h *= 60.0;                              // degrees

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}


util::draw::color hsv2rgb(hsv in)
{
	double      hh, p, q, t, ff;
	long        i;
	util::draw::color         out = util::draw::color::white();

	if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out._r = in.v;
		out._g = in.v;
		out._b = in.v;
		return out;
	}
	hh = in.h;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0 - in.s);
	q = in.v * (1.0 - (in.s * ff));
	t = in.v * (1.0 - (in.s * (1.0 - ff)));

	switch (i) {
	case 0:
		out._r = in.v * 255;
		out._g = t * 255;
		out._b = p * 255;
		break;
	case 1:
		out._r = q * 255;
		out._g = in.v * 255;
		out._b = p * 255;
		break;
	case 2:
		out._r = p * 255;
		out._g = in.v * 255;
		out._b = t * 255;
		break;

	case 3:
		out._r = p * 255;
		out._g = q * 255;
		out._b = in.v * 255;
		break;
	case 4:
		out._r = t * 255;
		out._g = p * 255;
		out._b = in.v * 255;
		break;
	case 5:
	default:
		out._r = in.v * 255;
		out._g = p * 255;
		out._b = q * 255;
		break;
	}


	return out;
}

typedef unsigned int        ImU32;
#define IM_COL32_R_SHIFT    24
#define IM_COL32_G_SHIFT    16
#define IM_COL32_B_SHIFT    8
#define IM_COL32_A_SHIFT    0
#define IM_COL32_A_MASK     0xFF000000
#define IM_COL32(R,G,B,A)    (((ImU32)(A)<<IM_COL32_A_SHIFT) | ((ImU32)(B)<<IM_COL32_B_SHIFT) | ((ImU32)(G)<<IM_COL32_G_SHIFT) | ((ImU32)(R)<<IM_COL32_R_SHIFT))

void c_gui::colorpicker(std::string name, std::string var)
{
	util::draw::color hueColors[7] =
	{
		{ 255, 0, 0   },
		{ 255, 255, 0 },
		{ 0, 255, 0   },
		{ 0, 255, 255 },
		{ 0, 0, 255   },
		{ 255, 0, 255 },
		{ 255, 0, 0   }
	};

	std::uint64_t hash = std::hash<std::string>()(name);

	if (m_color_picker.find(hash) == m_color_picker.end())
	{
		auto picker = gui_color_picker();

		std::uint32_t hex = g_user->GetConfig()[var];

		auto r = hex >> 24 & 0xFF;
		auto g = hex >> 16 & 0xFF;
		auto b = hex >> 8 & 0xFF;
		auto a = hex >> 0 & 0xFF;

		picker.alpha = a / 255.0;
		hsv hsv_ = rgb2hsv(render_color(r, g, b, a));
		picker.hue_bar = hsv_.h / 360.f;
		picker.picker.x = std::clamp(hsv_.s, 0.01, 1.0);
		picker.picker.y = hsv_.v;
		m_color_picker.emplace(hash, picker);
	}

	auto& color_info = m_color_picker.find(hash)->second;

	auto pos = get_position();

	render_size size_picker = { 150.f,119.f };

	{
		util::draw::position start = pos;
		util::draw::position end = { size_picker.x, size_picker.y };
		auto black = util::draw::color::black();
		util::draw::color black_trans = { black.r(), black.g(), black.b(), 0 };

		auto aye = hsv{ color_info.hue_bar * 360.f, 1,1 };

		auto clr_ = hsv2rgb(aye);

		if (helper.is_hovered(m_mouse_pos_, rect_(start, end)) && g_input_system->get_hold_key(VK_LBUTTON) && color_info.active_element == -1)
			color_info.active_element = 3;

		g_render->rect_filled_multi(start, end, render_color_multi(util::draw::color::white(), util::draw::color::white(), clr_, clr_), 10.f, ROUND_RECT_TOP);
		g_render->rect_filled_multi(start, end, render_color_multi(black_trans, black, black_trans, black), 10.f, ROUND_RECT_TOP);
		g_render->get_buffer()->circle((pos + (render_position(color_info.picker.x, 1.f - color_info.picker.y) * size_picker) + render_position(2.5, 2.5)) * g_render->get_dpi(), 5 * g_render->get_dpi(), render_color::white().override_alpha(g_render->get_override_alpha()), 1);
	}

	/* Render hue bar */
	for (auto i = 0; i < 6; ++i)
	{
		float size = size_picker.x - 12.f;
		util::draw::position start = { (pos.x + float(i * size / 6.f)) + 6.f, pos.y + 125.f };
		util::draw::position end = { size / 6, 8.f };

		g_render->rect_filled_multi(start, end, render_color_multi(hueColors[i], hueColors[i], hueColors[i + 1], hueColors[i + 1]));
	}

	g_render->get_buffer()->circle((pos + render_size((size_picker.x - 12) * color_info.hue_bar, 125.f) + render_position(5, 4)) * g_render->get_dpi(), 5 * g_render->get_dpi(), render_color::white().override_alpha(g_render->get_override_alpha()), 1);

	if (helper.is_hovered(m_mouse_pos_, rect_(render_position(pos.x + 6.f, pos.y + 125.f), render_size(size_picker.x - 12.f, 8.f))) && g_input_system->get_hold_key(VK_LBUTTON) && color_info.active_element == -1)
	{
		color_info.active_element = 1;
	}

	{
		util::draw::position start = pos + render_position(6.f, 125) + render_position(0, 14);
		util::draw::position end = { size_picker.x - 12.f, 8.f };

		g_render->rect_filled_multi(start, end, render_color_multi(util::draw::color::black(), util::draw::color::black(), util::draw::color::white(), util::draw::color::white()));
	}

	g_render->get_buffer()->circle((pos + render_size((size_picker.x - 12) * color_info.alpha, 139.f) + render_position(5, 4)) * g_render->get_dpi(), 5 * g_render->get_dpi(), render_color::white().override_alpha(g_render->get_override_alpha()), 1);

	if (helper.is_hovered(m_mouse_pos_, rect_(pos + render_position(6.f, 125) + render_position(0, 14), render_size(size_picker.x - 12.f, 8.f))) && g_input_system->get_hold_key(VK_LBUTTON) && color_info.active_element == -1)
	{
		color_info.active_element = 2;
	}

	{
		std::uint32_t hex = g_user->GetConfig()[var];

		auto r = hex >> 24;
		auto g = hex >> 16;
		auto b = hex >> 8;
		auto a = hex >> 0;

		std::uint32_t value = IM_COL32(r, g, b, a);
		std::ostringstream oss;
		oss << std::hex << std::uppercase << value;
		std::string hexStr = oss.str();
		g_render->add_text(xorstr_("Hex"), pos + render_position(5, 154), render_color(86, 86, 87), g_render->get_font(0), 11);
		g_render->add_text(hexStr, pos + render_position(85, 154), render_color(86, 86, 87), g_render->get_font(0), 11);
	}

	g_render->rect_filled(pos + render_position(5, 175), render_size(65, 15), render_color(10, 10, 10), 0, 2.f);
	g_render->rect_filled(pos + render_position(80, 175), render_size(65, 15), render_color(10, 10, 10), 0, 2.f);

	static std::uint32_t penis{};

	if (g_gui->is_hovered({ pos + render_position(5, 175), render_size(65,15) }) && g_gui->has_pressed(VK_LBUTTON))
	{
		std::uint32_t hex = g_user->GetConfig()[var];
		auto r = hex >> 24;
		auto g = hex >> 16;
		auto b = hex >> 8;
		auto a = hex >> 0;
		std::uint32_t value = IM_COL32(r, g, b, a);
		penis = value;
	}

	if (g_gui->is_hovered({ pos + render_position(80, 175), render_size(65,15) }) && g_gui->has_pressed(VK_LBUTTON))
	{
		g_user->GetConfig()[var] = penis;
		m_color_picker.erase(hash);
		return;
	}

	g_render->add_text(xorstr_("Copy"), pos + render_position(5 + 32.5 - g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, "Copy").x / 2, 175), render_color::white(), g_render->get_font(0), 11);
	g_render->add_text(xorstr_("Paste"), pos + render_position(80 + 32.5 - g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, "Paste").x / 2, 175), render_color::white(), g_render->get_font(0), 11);

	size_picker *= g_render->get_dpi();
	pos *= g_render->get_dpi();

	// manipulation active
	switch (color_info.active_element)
	{
	case 1:
	{
		auto p = render_size(size_picker.x - 12.f, 8.f);
		color_info.hue_bar = std::clamp((g_gui->m_mouse_pos_.x - pos.x) / p.x, 0.f, 1.f);
	}
	break;
	case 2:
	{
		color_info.alpha = std::clamp((g_gui->m_mouse_pos_.x - pos.x) / render_size(size_picker.x - 12.f, 8.f).x, 0.f, 1.f);
	}
	break;
	case 3:
	{
		color_info.picker.x = std::clamp((g_gui->m_mouse_pos_.x - pos.x) / size_picker.x, 0.01f, 1.f);
		color_info.picker.y = 1.f - std::clamp((g_gui->m_mouse_pos_.y - pos.y) / size_picker.y, 0.f, 1.f);
	}
	break;
	}

	hsv hsv;
	hsv.h = color_info.hue_bar * 360.f;
	hsv.s = color_info.picker.x;
	hsv.v = color_info.picker.y;

	auto clr = hsv2rgb(hsv);
	g_user->GetConfig()[var] = IM_COL32(clr.r(), clr.g(), clr.b(), clr.a() * color_info.alpha);

	if (color_info.active_element != -1 && !has_hold(VK_LBUTTON))
		color_info.active_element = -1;
}