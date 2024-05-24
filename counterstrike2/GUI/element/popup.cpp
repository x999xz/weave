// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"

bool c_gui::begin_popup(const std::string name, const render_size region_size, const render_size popup_size, const int key)
{
	std::uint64_t hash = std::hash<std::string>()(name);
	if (m_popup.find(hash) == m_popup.end()) {
		m_popup.insert_or_assign(hash, gui_popup(name, m_cursor_pos_, popup_size, key));
	}

	auto& popup = m_popup.find(hash)->second;

	bool has_hovered = helper.is_hovered(m_pressed_mouse_pos_, rect_(get_position(), region_size));

	if (popup.is_open_)
		has_hovered = helper.is_hovered(m_pressed_mouse_pos_, rect_(m_window_pos_ / g_render->get_dpi() + popup.cursor_pos_, popup_size));

	current_popup = hash;

	g_render->push_override_buffer(3);

	g_render->set_limit(m_window_pos_ / g_render->get_dpi() + popup.cursor_pos_, popup_size);
	if (!(!popup.is_open_ && popup.animation_.base == 0.0f))
		g_render->rect_filled(m_window_pos_ / g_render->get_dpi() + popup.cursor_pos_, popup_size, render_color(17, 17, 17).override_alpha(popup.animation_.base), 0, 10.f);

	if (has_hovered && has_pressed(key) && !popup.is_open_)
	{
		for (auto& it : m_popup)
			it.second.is_open_ = false;

		popup.is_open_ = true;
		popup.m_backup_cursor_pos_ = m_cursor_pos_;
		popup.cursor_pos_ = (m_pressed_mouse_pos_ / g_render->get_dpi() - m_window_pos_ / g_render->get_dpi()) + render_position(5, 0);
	}
	else if (popup.is_open_ && !has_hovered && has_pressed(VK_LBUTTON) && !has_active())
	{
		popup.is_open_ = false;
		buttons[VK_LBUTTON] = c_buttons();
	}

	popup.animation_.run(popup.is_open_);

	bool has_close = !popup.is_open_ && popup.animation_.base == 0.0f;

	if (!has_close)
	{
		m_cursor_pos_ = popup.cursor_pos_;
	}

	m_window_pos_ /= g_render->get_dpi();

	g_render->push_override_alpha(popup.animation_.base);

	return !has_close;
}

void c_gui::end_popup()
{
	auto popup_info = m_popup.find(current_popup)->second;
	current_popup = -1;

	m_cursor_pos_ = popup_info.m_backup_cursor_pos_;
	m_window_pos_ *= g_render->get_dpi();

	g_render->pop_limit();
	g_render->pop_override_buffer();
	g_render->pop_override_alpha();
}