// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"

void c_gui::begin_group(const std::string name, const render_size size, bool same_line)
{
	m_groups.emplace(name, same_line, m_cursor_pos_, size);

	g_render->set_limit(get_position(), size);

	const render_color_multi gradient(render_color(255, 139, 59, 50), render_color(255, 139, 59, 50), render_color(14, 14, 16, 50), render_color(14, 14, 16, 50));

	g_render->rect_filled_multi(get_position(), render_size(size.x, 35), gradient, 10.f, render_rounding_flags_::ROUND_RECT_TOP);
	g_render->rect_filled(get_position() + render_position(0, 35), render_size(size.x, size.y - 35.f), render_color(13, 13, 14), 0, 10.f, render_rounding_flags_::ROUND_RECT_BOT);
	g_render->add_text(name, get_position() + render_position(30, 10), render_color(221, 221, 221), g_render->get_font(0), 12);

	m_cursor_pos_ += render_position(0, 35);
}

void c_gui::end_group()
{
	auto group_info = m_groups.top();

	if (!group_info.same_line_)
	{
		m_cursor_pos_ = render_position(group_info.cursor_pos_.x + group_info.size_.x + 10, 65);
	}
	else
	{
		m_cursor_pos_ = render_position(group_info.cursor_pos_.x, group_info.cursor_pos_.y + group_info.size_.y + 10);
	}

	g_render->pop_limit();
	m_groups.pop();
	current_group++;
}