// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"
#include <ranges>
#include "../../utilities/hotkey_system/hotkey_system.h"

bool is_active(hotkey_impl hotkey) {
	return hotkey.enabled && g_gui->active_hotkey == -1;
}

void c_gui::checkbox(const std::string name, std::string var)
{
	bool value = g_user->GetConfig()[var];
	checkbox(name, var, value);
	g_user->GetConfig()[var] = value;
}

void c_gui::checkbox(const std::string name, const std::string hash_name, bool& value)
{
	auto pos = get_position() + padding_element;
	std::uint64_t hash = std::hash<std::string>()(hash_name);

	render_position size = get_group_size();
	rect_ rect(pos, render_size(size.x - padding_element.x * 2, 20));
	bool has_popup = current_popup == -1 && has_popup_open_;
	render_size square(23, 12);

	animation[hash].run(value, 0.3f);

	bool has_hovered = is_hovered(rect_(pos + render_position(size.x - 14 - padding_element.x - square.x, 0), square));

	if (name.find(xorstr_("_value_bind")) == std::string::npos && name.find(xorstr_("_visible_bind")) == std::string::npos)
		g_render->add_text(name, pos, render_color(221, 221, 221), g_render->get_font(0), 12);

	auto calc_text = g_render->get_font(0)->calc_text_size(12, FLT_MAX, FLT_MAX, name.c_str());

	bool has_hovered_text = is_hovered(rect_(pos, calc_text));

	g_render->rect_filled(pos + render_position(size.x - 14 - padding_element.x - square.x, 0), square, helper.animation_color(render_color(32,32,33), render_color(255,139,59), animation[hash].base), 0, 5.f);
	g_render->arc_fill(pos + render_position(size.x - 14 - padding_element.x - square.x, 0) + render_position(3, 6) + render_position(10 * animation[hash].base, 0), 0, 360, 3, helper.animation_color(render_color(86, 86, 86), render_color(13, 13, 14), animation[hash].base));
	g_render->line(render_position(rect.min.x, rect.max.y), render_position(rect.max.x, rect.max.y), render_color(18, 18, 20));

	if ((has_hovered || has_hovered_text) && has_pressed(VK_LBUTTON) && !has_popup && !has_active())
		value = !value;

	render_position hotkey_position = padding_element + render_position(size.x - 14 - padding_element.x - square.x, 0);
	hotkey(name, hash_name, hotkey_position);

	m_cursor_pos_.y += (rect.max.y - rect.min.y) + 6;
}