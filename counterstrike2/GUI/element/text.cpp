// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"

void c_gui::text(const std::string name, const bool same_line)
{
	auto pos = get_position() + padding_element;
	std::uint64_t hash = std::hash<std::string>()(name);

	g_render->add_text(name, pos, render_color(221, 221, 221), g_render->get_font(0), 12);

	if (!same_line)
		m_cursor_pos_ += render_position(0, 12) + render_position(0, 17);
}