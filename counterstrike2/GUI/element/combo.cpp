// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"
#include "../../utilities/hotkey_system/hotkey_system.h"

bool is_active3(hotkey_impl hotkey) {
	return hotkey.enabled && g_gui->active_hotkey == -1;
}

void c_gui::combo(const std::string name, std::string var, std::vector<std::string >& list)
{
	int value = g_user->GetConfig()[var];
	combo(name, var, value, list);
	g_user->GetConfig()[var] = value;
}

void c_gui::combo(const std::string name, const std::string hash_name, int& select, std::vector<std::string >& list)
{
	auto pos = get_position() + padding_element;
	render_position size{};

	bool has_popup = false;

	if (current_popup == -1) {
		has_popup = has_popup_open();
		size = m_groups.top().size_;
	}
	else {
		size = m_popup.find(current_popup)->second.size_;
	}

	std::uint64_t hash = std::hash<std::string>()(hash_name);

	rect_ rect(pos, render_size(size.x - padding_element.x * 2, 25));

	bool is_hovered = helper.is_hovered(m_pressed_mouse_pos_, rect_(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17)));

	if (active_id == hash && is_hovered && has_pressed(VK_LBUTTON))
		reset_active_id();
	else
	{
		if (active_id == hash)
			is_hovered = helper.is_hovered(m_pressed_mouse_pos_, rect_(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17 + (23 * list.size()))));

		if (is_hovered && has_pressed(VK_LBUTTON) && !has_active() && !has_popup)
			active_id = hash;

		if (!is_hovered && has_pressed(VK_LBUTTON) && active_id == hash)
			reset_active_id();
	}

	int value_ = select;

	animation[hash].run(active_id == hash);

	g_render->line(render_position(rect.min.x, rect.max.y), render_position(rect.max.x, rect.max.y), render_color(18, 18, 20));

	bool has_foreground = g_render->has_override_buffer();

	if (!has_foreground)
		g_render->push_override_buffer(2);

	if (active_id == hash && m_moved_window != -1 && m_moved_window != m_current_window) {
		reset_active_id();
	}

	g_render->set_limit(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17 + (20.5f * float(list.size())) * animation[hash].base));

	g_render->rect_filled(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17 + (20.5f * float(list.size())) * animation[hash].base), render_color(19, 19, 19, 255 * animation[hash].base), 0, 6.f);

	int text_index = 0;
	int padding_x = 0;
	for (auto it = list.begin(); it != list.end();)
	{
		g_render->add_text(it->c_str(), pos + render_position(size.x - 14 - 100 - padding_element.x, -1) + render_position(0, 17) + render_position(0, 6) + render_position(5, padding_x), helper.animation_color(render_color(86, 86, 87, 255 * animation[hash].base), render_color(221, 221, 221, 255 * animation[hash].base), select == text_index), g_render->get_font(1), 11);

		bool is_hover = helper.is_hovered(m_pressed_mouse_pos_, rect_(pos + render_position(size.x - 14 - 100 - padding_element.x, -1) + render_position(0, 17) + render_position(0, 6) + render_position(5, padding_x), render_size(100, 14)));

		if (name.find(xorstr_("Binds")) != std::string::npos && text_index != 0 && text_index != (list.size() - 1))
		{
			std::uint64_t hash_bind = std::hash<std::string>()(std::format("Binds_{}", text_index));
			auto pos_text = pos + render_position(size.x - 14 - 100 - padding_element.x, -1) + render_position(0, 17) + render_position(0, 6) + render_position(5, padding_x) + render_size(100 - 18, 7);
			g_render->line(pos_text, pos_text + render_position(8, 0), helper.animation_color(render_color(86, 86, 87), render_color::white(), animation[hash_bind].base));

			animation[hash_bind].run(helper.is_hovered(m_mouse_pos_, rect_(pos_text - render_position(0, 7), render_size(10, 14))));

			if (helper.is_hovered(m_pressed_mouse_pos_, rect_(pos_text - render_position(0,7), render_size(10, 14))) && has_pressed(VK_LBUTTON) && active_id == hash)
			{
				removed_bind = text_index;
				buttons[VK_LBUTTON] = c_buttons();
			}
		}

		if (is_hover && has_pressed(VK_LBUTTON) && active_id == hash && select != text_index)
		{
			select = text_index;
			buttons[VK_LBUTTON] = c_buttons();
			if (name.find(xorstr_("Binds")) != std::string::npos)
			{
				if (text_index != (list.size() - 1))
				{
					reset_active_id();
					break;
				}
			}
			else
			{
				reset_active_id();
				break;
			}
		}

		padding_x += 9 + g_render->get_font(1)->calc_text_size(11, FLT_MAX, FLT_MAX, it->c_str()).y;
		text_index++;

		it++;
	}

	g_render->get_buffer()->pop_clip_rect();

	if (animation[hash].base > 0.0f) {
		g_render->rect_filled(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17), render_color(23, 23, 23), 0, 3.f);
		g_render->set_limit(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17));
		g_render->add_text(list[value_], pos + render_position(size.x - 14 - 100 - padding_element.x, -1) + render_position(5, 1), render_color(86, 86, 87), g_render->get_font(0), 11);
		g_render->get_buffer()->pop_clip_rect();
	}

	if (!has_foreground)
		g_render->pop_override_buffer();

	if (name.find(xorstr_("_value_bind")) == std::string::npos)
		g_render->add_text(name, pos, render_color(221, 221, 221), g_render->get_font(0), 12);

	g_render->rect_filled(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17), render_color(23, 23, 23), 0, 3.f);

	g_render->set_limit(pos + render_position(size.x - 14 - 100 - padding_element.x, -1), render_size(100, 17));
	g_render->add_text(list[value_], pos + render_position(size.x - 14 - 100 - padding_element.x, -1) + render_position(5, 1), render_color(86, 86, 87), g_render->get_font(0), 11);
	g_render->get_buffer()->pop_clip_rect();

	auto backup = get_cursor_pos();

	if (name.find(xorstr_("_value_bind")) == std::string::npos && (name.find(xorstr_("Mode")) == std::string::npos && name.find(xorstr_("Binds")) == std::string::npos))
	{
		set_cursor_pos(get_cursor_pos() + padding_element + render_position(size.x - 14 - padding_element.x - 100, 3));
		if (begin_popup(name + xorstr_("_popup"), render_size(100,17), render_size(180, 155), VK_RBUTTON))
		{
			int backup_current = g_hotkey->hotkeys_->at(hash).current;
			std::vector<std::string> binds;
			for (auto bind : g_hotkey->hotkeys_->at(hash).binds)
			{
				std::string b = xorstr_("Bind");

				if (bind.key != -1)
					b += " [" + get_name_key(bind.key) + "]";

				binds.push_back(b);
			}
			binds.push_back(xorstr_("Add Bind"));
			g_render->push_override_buffer(6);
			combo(xorstr_("Binds"), xorstr_("Binds"), g_hotkey->hotkeys_->at(hash).current, binds);
			g_render->pop_override_buffer(3);

			if (removed_bind != -1)
			{
				if (g_hotkey->hotkeys_->at(hash).binds.size() > removed_bind)
					g_hotkey->hotkeys_->at(hash).binds.erase(g_hotkey->hotkeys_->at(hash).binds.begin() + removed_bind);

				removed_bind = -1;

				if (g_hotkey->hotkeys_->at(hash).binds.size() == g_hotkey->hotkeys_->at(hash).current)
					g_hotkey->hotkeys_->at(hash).current--;
			}

			if (g_hotkey->hotkeys_->at(hash).current == g_hotkey->hotkeys_->at(hash).binds.size())
			{
				std::vector<std::string> temp_name = { hash_name };
				std::vector<double> temp_value;
				temp_value.push_back(false);
				add_bind(g_hotkey->hotkeys_->at(hash), 2, list, temp_value);
				g_hotkey->hotkeys_->at(hash).current = backup_current;
			}

			std::vector<std::string> mode = {
				xorstr_("Hold"), xorstr_("Toggle")
			};

			g_render->push_override_buffer(5);
			combo(xorstr_("Mode"), xorstr_("Mode"), g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].mode, mode);
			g_render->pop_override_buffer(3);
			text(xorstr_("Key"), true);

			std::string key = xorstr_("[ ]");

			if (g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].key != -1)
			{
				key.clear();
				key += get_name_key(g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].key);
			}

			set_cursor_pos(get_cursor_pos() + render_position(180 - 50, 0));

			if (helper.is_hovered(get_mouse_pos(), rect_(get_position(), render_size(30, 30))) && has_pressed(VK_LBUTTON))
			{
				active_hotkey = hash;
				buttons[VK_LBUTTON] = {};
			}

			if (active_hotkey == hash) {
				key = xorstr_("[ - ]");

				for (int i{}; i < 256; i++)
				{
					if (!has_pressed(i))
						continue;

					if (i == VK_ESCAPE)
					{
						g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].key = -1;
						active_hotkey = -1;
						buttons[VK_LBUTTON] = c_buttons();
						break;
					}

					auto k = i;

					if (isupper(k) && i < 0x70 && i > 0x87)
						k = std::tolower(k);

					g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].key = i;
					active_hotkey = -1;
				}
			}

			{
				text(key, false);
				set_cursor_pos(get_cursor_pos() - render_position(180 - 50, 0));
				text(xorstr_("Value"), true);
				std::string v = name + xorstr_("_value_bind");
				std::string v2 = hash_name + xorstr_("_value_bind");
				int value2 = g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].value[0];
				g_render->push_override_buffer(4);
				combo(v, v2, value2, list);
				g_render->pop_override_buffer(3);
				g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].value[0] = value2;
			}

			{
				text(xorstr_("Visible"), true);
				std::string v = name + xorstr_("_visible_bind");
				std::string v2 = hash_name + xorstr_("_visible_bind");
				checkbox(v, v2, g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].visible);
			}

		}
		end_popup();
		set_cursor_pos(backup);
	}

	//g_render->rect(rect.min, rect.max - rect.min, render_color::white().override_alpha(200));

	m_cursor_pos_.y += (rect.max.y - rect.min.y) + 6;
}