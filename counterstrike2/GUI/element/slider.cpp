// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"
#include "../../utilities/hotkey_system/hotkey_system.h"

bool is_active2(hotkey_impl hotkey) {
	return hotkey.enabled && g_gui->active_hotkey == -1;
}

void c_gui::slider(const std::string name, std::string var, const int min, const int max)
{
	int value = g_user->GetConfig()[var];
	slider(name, var, value, min, max);
	g_user->GetConfig()[var] = value;
}

void c_gui::slider(const std::string name, const std::string hash_name, int& value, const int min, const int max)
{
	auto pos = get_position() + padding_element;
	std::uint64_t hash = std::hash<std::string>()(hash_name);

	if (m_slider.find(hash) == m_slider.end())
	{
		m_slider.insert_or_assign(hash, gui_slider());
	}

	auto& slider_info = m_slider.find(hash)->second;

	render_position size{};

	bool has_popup = false;

	if (current_popup == -1) {
		has_popup = has_popup_open_;
		size = m_groups.top().size_;
	}
	else {
		size = m_popup.find(current_popup)->second.size_;
	}

	rect_ rect(pos, render_size(size.x - padding_element.x * 2, 20));

	if (name.find(xorstr_("_value_bind")) == std::string::npos)
		g_render->add_text(name, pos, render_color(221, 221, 221), g_render->get_font(0), 12);

	render_size square(80, 6);

	value = std::clamp(int(value), min, max);

	int max_amount = std::fabsf(min) + max;

	if (min >= 0.f)
		max_amount = max - min;

	int value_ = value;

	float amount = 0.f;
	if (min < 0.f)
		amount = ((value_ + max) / float(max_amount));
	else
		amount = (float(value_ - min) / float(max_amount));
	float delta = std::clamp((square.x * amount) / square.x, 0.00f, 1.f);
	float delta_previous = 0.01f;

	auto delta_avg = delta - slider_info.animation_;

	if (delta_avg < 0.0f)
		slider_info.animation_ -= std::clamp(std::fabsf(delta_avg) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
	else
		slider_info.animation_ += std::clamp(std::fabsf(delta_avg) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);

	slider_info.animation_ = std::clamp(slider_info.animation_, 0.f, 1.f);

	auto t = std::round(slider_info.animation_ * max_amount);
	int anim_value = min + t;

	bool is_hovered = helper.is_hovered(m_mouse_pos_, rect_(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), square));

	animation[hash].run(is_hovered || active_id == hash);

	if (is_hovered)
	{
		if (has_hold(VK_CONTROL) && g_input_system->get_scroll() != 0)
		{
			value += g_input_system->get_scroll();
			g_input_system->reset_scrolling();
		}

		if (has_pressed(VK_LEFT))
			value -= 1;
		else if (has_pressed(VK_RIGHT))
			value += 1;
	}

	if (is_hovered)
	{
		auto pos_ = (pos + render_position(size.x - 14 - padding_element.x - square.x, 5)) * g_render->get_dpi();
		delta_previous = std::clamp((m_mouse_pos_.x - pos_.x) / (square.x * g_render->get_dpi()), 0.01f, 1.f);

		auto delta_previous_avg = delta_previous - slider_info.animation_previous;

		if (delta_previous_avg < 0.0f)
			slider_info.animation_previous -= std::clamp(std::fabsf(delta_previous_avg) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
		else
			slider_info.animation_previous += std::clamp(delta_previous_avg * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
	}
	else
	{
		auto delta_unk =  slider_info.animation_ - slider_info.animation_previous;
		if (delta_unk < 0.0f)
			slider_info.animation_previous -= std::clamp(std::fabsf(delta_unk) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
		else
			slider_info.animation_previous += std::clamp(delta_unk * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
	}

	slider_info.animation_previous = std::clamp(slider_info.animation_previous, 0.f, 1.f);

	g_render->rect_filled(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), square, render_color(23, 23, 23), c_render_manager::render_flags_::clip, 2.f);
	g_render->rect_filled(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), render_size(square.x * slider_info.animation_previous, square.y), render_color(50, 50, 50), c_render_manager::render_flags_::clip, 2.f);
	g_render->rect_filled(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), render_size(square.x * slider_info.animation_, square.y), render_color(255, 139, 59), c_render_manager::render_flags_::clip, 2.f);
	g_render->arc_fill(pos + render_position(size.x - 18 - padding_element.x - square.x, 5) + render_size(square.x * slider_info.animation_, 3), 0, 360, 6, render_color(255, 139, 59, 50 * animation[hash].base));
	g_render->arc_fill(pos + render_position(size.x - 16 - padding_element.x - square.x, 5) + render_size(square.x * slider_info.animation_, 3), 0, 360, 4, render_color(255, 139, 59));
	g_render->add_text(std::to_string(anim_value), pos + render_position(size.x - 14 - padding_element.x - square.x, 0) - render_position(10 + g_render->get_font(0)->calc_text_size(12, FLT_MAX, FLT_MAX, std::to_string(anim_value).c_str()).x, -0.5f), render_color(86, 86, 87), g_render->get_font(0), 12);
	g_render->line(render_position(rect.min.x, rect.max.y), render_position(rect.max.x, rect.max.y), render_color(18, 18, 20));

	if (helper.is_hovered(m_mouse_pos_, rect_(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), square)) && has_hold(VK_LBUTTON) && !has_active() && !has_popup)
		active_id = hash;

	if (active_id == hash)
	{
		if (!has_hold(VK_LBUTTON))
			active_id = -1;

		auto pos_ = (pos + render_position(size.x - 14 - padding_element.x - square.x, 5)) * g_render->get_dpi();
		delta = std::clamp((m_mouse_pos_.x - pos_.x) / (square.x * g_render->get_dpi()), 0.f, 1.f);
		value = min + (delta * max_amount);
	}

	auto backup = get_cursor_pos();

	if (name.find(xorstr_("_value_bind")) == std::string::npos)
	{
		set_cursor_pos(get_cursor_pos() + padding_element + render_position(size.x - 14 - padding_element.x - square.x, 2));
		if (begin_popup(name + xorstr_("_popup"), square + render_position(0,3), render_size(180, 155), VK_RBUTTON) && g_hotkey->hotkeys_->find(hash) != g_hotkey->hotkeys_->end())
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
			g_render->push_override_buffer(5);
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
				std::vector<std::string> temp_name;
				std::vector<double> temp_value(1);
				temp_name.push_back(hash_name);
				add_bind(g_hotkey->hotkeys_->at(hash), 1, temp_name, temp_value);
				g_hotkey->hotkeys_->at(hash).current = backup_current;
			}

			std::vector<std::string> mode = {
				xorstr_("Hold"), xorstr_("Toggle")
			};

			g_render->push_override_buffer(4);
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
				slider(v, v2, value2, min, max);
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

void c_gui::slider_float(const std::string name, std::string var, const float min, const float max)
{
	float value = g_user->GetConfig()[var];
	slider_float(name, var, value, min, max);
	g_user->GetConfig()[var] = value;
}

void c_gui::slider_float(const std::string name, const std::string hash_name, float& value, const float min, const float max)
{
	auto pos = get_position() + padding_element;
	std::uint64_t hash = std::hash<std::string>()(hash_name);

	if (m_slider.find(hash) == m_slider.end())
	{
		m_slider.insert_or_assign(hash, gui_slider());
	}

	auto& slider_info = m_slider.find(hash)->second;

	render_position size{};

	bool has_popup = false;

	if (current_popup == -1) {
		has_popup = has_popup_open_;
		size = m_groups.top().size_;
	}
	else {
		size = m_popup.find(current_popup)->second.size_;
	}

	rect_ rect(pos, render_size(size.x - padding_element.x * 2, 20));

	if (name.find(xorstr_("_value_bind")) == std::string::npos)
		g_render->add_text(name, pos, render_color(221, 221, 221), g_render->get_font(0), 12);

	render_size square(80, 6);

	value = std::clamp(float(value), min, max);

	int max_amount = std::fabsf(min) + max;

	if (min >= 0.f)
		max_amount = max - min;

	int value_ = value;

	float amount = 0.f;
	if (min < 0.f)
		amount = ((value_ + max) / float(max_amount));
	else
		amount = (float(value_ - min) / float(max_amount));
	float delta = std::clamp((square.x * amount) / square.x, 0.00f, 1.f);
	float delta_previous = 0.01f;

	auto delta_avg = delta - slider_info.animation_;

	if (delta_avg < 0.0f)
		slider_info.animation_ -= std::clamp(std::fabsf(delta_avg) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
	else
		slider_info.animation_ += std::clamp(std::fabsf(delta_avg) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);

	slider_info.animation_ = std::clamp(slider_info.animation_, 0.f, 1.f);

	auto t = std::round(slider_info.animation_ * max_amount);
	float anim_value = min + t;

	bool is_hovered = helper.is_hovered(m_mouse_pos_, rect_(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), square));

	animation[hash].run(is_hovered || active_id == hash);

	if (is_hovered)
	{
		if (has_hold(VK_CONTROL) && g_input_system->get_scroll() != 0)
		{
			value += g_input_system->get_scroll();
			g_input_system->reset_scrolling();
		}

		if (has_pressed(VK_LEFT))
			value -= 0.1;
		else if (has_pressed(VK_RIGHT))
			value += 0.1;
	}

	if (is_hovered)
	{
		auto pos_ = (pos + render_position(size.x - 14 - padding_element.x - square.x, 5)) * g_render->get_dpi();
		delta_previous = std::clamp((m_mouse_pos_.x - pos_.x) / (square.x * g_render->get_dpi()), 0.01f, 1.f);

		auto delta_previous_avg = delta_previous - slider_info.animation_previous;

		if (delta_previous_avg < 0.0f)
			slider_info.animation_previous -= std::clamp(std::fabsf(delta_previous_avg) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
		else
			slider_info.animation_previous += std::clamp(delta_previous_avg * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
	}
	else
	{
		auto delta_unk = slider_info.animation_ - slider_info.animation_previous;
		if (delta_unk < 0.0f)
			slider_info.animation_previous -= std::clamp(std::fabsf(delta_unk) * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
		else
			slider_info.animation_previous += std::clamp(delta_unk * ((1.f / 0.1f) * g_render->get_delta_render()), 0.f, 1.f);
	}

	slider_info.animation_previous = std::clamp(slider_info.animation_previous, 0.f, 1.f);

	g_render->rect_filled(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), square, render_color(23, 23, 23), c_render_manager::render_flags_::clip, 2.f);
	g_render->rect_filled(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), render_size(square.x * slider_info.animation_previous, square.y), render_color(50, 50, 50), c_render_manager::render_flags_::clip, 2.f);
	g_render->rect_filled(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), render_size(square.x * slider_info.animation_, square.y), render_color(255, 139, 59), c_render_manager::render_flags_::clip, 2.f);
	g_render->arc_fill(pos + render_position(size.x - 18 - padding_element.x - square.x, 5) + render_size(square.x * slider_info.animation_, 3), 0, 360, 6, render_color(255, 139, 59, 50 * animation[hash].base));
	g_render->arc_fill(pos + render_position(size.x - 16 - padding_element.x - square.x, 5) + render_size(square.x * slider_info.animation_, 3), 0, 360, 4, render_color(255, 139, 59));
	g_render->add_text(std::to_string(anim_value), pos + render_position(size.x - 14 - padding_element.x - square.x, 0) - render_position(10 + g_render->get_font(0)->calc_text_size(12, FLT_MAX, FLT_MAX, std::to_string(anim_value).c_str()).x, -0.5f), render_color(86, 86, 87), g_render->get_font(0), 12);
	g_render->line(render_position(rect.min.x, rect.max.y), render_position(rect.max.x, rect.max.y), render_color(18, 18, 20));

	if (helper.is_hovered(m_mouse_pos_, rect_(pos + render_position(size.x - 14 - padding_element.x - square.x, 5), square)) && has_hold(VK_LBUTTON) && !has_active() && !has_popup)
		active_id = hash;

	if (active_id == hash)
	{
		if (!has_hold(VK_LBUTTON))
			active_id = -1;

		auto pos_ = (pos + render_position(size.x - 14 - padding_element.x - square.x, 5)) * g_render->get_dpi();
		delta = std::clamp((m_mouse_pos_.x - pos_.x) / (square.x * g_render->get_dpi()), 0.f, 1.f);
		value = min + (delta * max_amount);
	}

	auto backup = get_cursor_pos();

	if (name.find(xorstr_("_value_bind")) == std::string::npos)
	{
		set_cursor_pos(get_cursor_pos() + padding_element + render_position(size.x - 14 - padding_element.x - square.x, 2));
		if (begin_popup(name + xorstr_("_popup"), square + render_position(0, 3), render_size(180, 155), VK_RBUTTON) && g_hotkey->hotkeys_->find(hash) != g_hotkey->hotkeys_->end())
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
			g_render->push_override_buffer(5);
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
				std::vector<std::string> temp_name;
				std::vector<double> temp_value(1);
				temp_name.push_back(hash_name);
				add_bind(g_hotkey->hotkeys_->at(hash), 1, temp_name, temp_value);
				g_hotkey->hotkeys_->at(hash).current = backup_current;
			}

			std::vector<std::string> mode = {
				xorstr_("Hold"), xorstr_("Toggle")
			};

			g_render->push_override_buffer(4);
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
				float value2 = g_hotkey->hotkeys_->at(hash).binds[g_hotkey->hotkeys_->at(hash).current].value[0];
				slider_float(v, v2, value2, min, max);
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