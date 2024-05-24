// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../utilities/tls/tls.h"
#include "gui.h"
#include "../renderer/render_manager.h"
#include "menu_js.h"
#include "../utilities/cloud/user.h"
#include "../hooks/hooks.hpp"
#include <format>
#include <codecvt>
#include "../sdk/vtex/VTexParser.h"
#include "../utilities/service/flatbuffers.hpp"
#include "../utilities/hash.h"

bool c_gui_helper::is_hovered(render_position cursor_pos, rect_ dst)
{
	if (g_gui->m_moved_window != -1 && g_gui->m_moved_window != g_gui->m_current_window)
		return false;

	if (g_gui->m_hovered_window != -1 && g_gui->m_hovered_window != g_gui->m_current_window)
		return false;

	dst.min *= g_render->get_dpi();
	dst.max *= g_render->get_dpi();
	return (cursor_pos.x >= dst.min.x && cursor_pos.y >= dst.min.y) && (cursor_pos.x <= dst.max.x && cursor_pos.y <= dst.max.y);
}

bool c_gui::is_hovered(rect_ dst)
{
	if (g_gui->m_moved_window != -1 && g_gui->m_moved_window != g_gui->m_current_window)
		return false;

	if (g_gui->m_hovered_window != -1 && g_gui->m_hovered_window != g_gui->m_current_window)
		return false;

	dst.min *= g_render->get_dpi();
	dst.max *= g_render->get_dpi();
	return (m_mouse_pos_.x >= dst.min.x && m_mouse_pos_.y >= dst.min.y) && (m_mouse_pos_.x <= dst.max.x && m_mouse_pos_.y <= dst.max.y);
}

bool c_gui::is_hovered_pressed(rect_ dst)
{
	if (g_gui->m_moved_window != -1 && g_gui->m_moved_window != g_gui->m_current_window)
		return false;

	if (m_hovered_window != -1 && m_hovered_window != m_current_window)
		return false;

	dst.min *= g_render->get_dpi();
	dst.max *= g_render->get_dpi();
	return (m_pressed_mouse_pos_.x >= dst.min.x && m_pressed_mouse_pos_.y >= dst.min.y) && (m_pressed_mouse_pos_.x <= dst.max.x && m_pressed_mouse_pos_.y <= dst.max.y);
}

void c_gui::create_window(std::string name, render_size window_size, render_size fully_window_size)
{
	auto& window = m_windows.emplace_back();
	window.m_window_name = name;
	window.m_window_hash = fnv32::hash_runtime(name.c_str());
	window.m_window_size = window_size;
	window.m_fully_window_size = fully_window_size;
	window.m_direction = false;
	window.m_cursor_position = render_position();
	window.m_window_position = render_position();
	window.m_open = false;
}

void c_gui::update_windows()
{
	if (m_windows.empty())
		return;

	for (auto& window : m_windows)
	{
		if (window.m_window_hash == FNV32("Chat")) {
			window.m_open = g_cs2->m_open_chat && is_open_menu();
		}
		else if (window.m_window_hash == FNV32("Keybind")) {
			window.m_open = g_user->IsActive(xorstr_("misc_keybind"), xorstr_("misc_keybind"), 0) && is_open_menu();
		}
		else if (window.m_window_hash == FNV32("Spectators")) {
			window.m_open = g_user->IsActive(xorstr_("misc_spectators"), xorstr_("misc_keybind"), 1) && is_open_menu();
		}
		else if (window.m_window_hash == FNV32("Menu")) {
			window.m_open = is_open_menu();
		}
		else if (window.m_window_hash == FNV32("Rapid")) {
			window.m_open = is_open_menu();
		}
	}

	for (auto it = m_windows.rbegin(); it != m_windows.rend(); it++)
	{
		g_gui->m_current_window = it->m_window_hash;

		if (!it->m_open)
		{
			if (it->m_window_hash == m_moved_window)
				m_moved_window = -1;

			if (it->m_window_hash == m_hovered_window)
				m_hovered_window = -1;

			g_gui->m_current_window = -1;
			continue;
		}

		if (GetForegroundWindow() != g_d3d11_helper->get_window())
		{
			g_gui->m_current_window = -1;
			continue;
		}

		bool has_hovered = is_hovered_pressed(rect_(it->m_window_position, render_size(it->m_window_size.x, 35)));
		bool has_lbutton = has_hold(VK_LBUTTON);
		bool has_moving = std::find_if(m_windows.begin(), m_windows.end(), [&](const auto x) {
			return x.m_window_hash == m_moved_window;
			}) != m_windows.end();

		if (!it->m_direction && has_lbutton && has_hovered && !has_moving && is_open_menu())
		{
			it->m_direction = true;
			m_moved_window = it->m_window_hash;
			m_last_moved_window = m_moved_window;
		}

		if (it->m_direction)
		{
			it->m_window_position.x += g_input_system->get_delta_x() / g_render->get_dpi();
			it->m_window_position.y += g_input_system->get_delta_y() / g_render->get_dpi();

			if (!has_lbutton)
			{
				it->m_direction = false;
				m_moved_window = -1;
			}
		}

		g_gui->m_current_window = -1;
	}
}

void c_gui::win32_processing(int index) {

	if (index < 0 || index > 255)
		return;

	if (index != VK_LSHIFT && index != VK_RSHIFT)
	{
		if (!g_gui->has_hold(index))
		{
			g_gui->buttons[index].first_press_ = false;
			return;
		}
	}

	int index_ = index;

	if (g_gui->has_hold(VK_LSHIFT) || g_gui->has_hold(VK_RSHIFT))
	{
		//if (islower(index_)) {
			index_ = toupper(index_);
		//}
	}

	auto char_ = key_to_string(index_);

	//input_character_queue += char_;

	if (g_gui->buttons[index].repeat_time_ == 0.f)
		g_gui->buttons[index].repeat_time_ = g_gui->buttons[index].first_press_ ? 1.f : 0.2f;
}

std::optional<gui_window> c_gui::find_window(std::string name)
{
	if (m_windows.empty())
		return std::nullopt;

	for (auto& window : m_windows)
	{
		if (window.m_window_name.find(name) == std::string::npos)
			continue;

		return std::make_optional(std::ref(window));
	}

	return std::nullopt;
}

bool c_gui::has_moved_window()
{
	if (m_windows.empty())
		return false;

	for (auto window : m_windows)
	{
		if (!window.m_direction)
			continue;

		return true;
	}

	return false;
}

render_color c_gui_helper::animation_color(render_color non_active, render_color active, float multiplication)
{
	render_color new_color = render_color::white();
	new_color._r = non_active._r + ((active._r - non_active._r) * multiplication);
	new_color._g = non_active._g + ((active._g - non_active._g) * multiplication);
	new_color._b = non_active._b + ((active._b - non_active._b) * multiplication);
	new_color._a = non_active._a * g_render->get_override_alpha();

	return new_color;
}

void c_gui::create_hotkey(std::string item, std::uint64_t hash_item, int type, std::vector<std::string> name, std::vector<double> items)
{
	g_hotkey->hotkeys_->try_emplace(hash_item);
	hotkey_impl h;
	h.key = -1;
	h.mode = 0;
	h.visible = true;
	h.value = std::move(items);
	h.type = type;
	h.enabled = false;
	h.current = 0;
	g_hotkey->hotkeys_->at(hash_item).binds.push_back(h);
	g_hotkey->hotkeys_->at(hash_item).current = 0;
	g_hotkey->hotkeys_->at(hash_item).name_ = item;
	//g_hotkey->hotkeys_->at(hash_item).name = std::move(name);
	g_hotkey->hotkeys_->at(hash_item).name_visuals = std::move(name);
}

void c_gui::create_hotkey(std::string item, std::uint64_t hash_item, int type, std::vector<std::string> name_visual, std::vector<std::string> name, std::vector<double> items)
{
	g_hotkey->hotkeys_->try_emplace(hash_item);
	hotkey_impl& bind = g_hotkey->hotkeys_->at(hash_item).binds.emplace_back();
	bind.key = -1;
	bind.mode = 0;
	bind.visible = true;
	bind.value = std::move(items);
	bind.type = type;
	bind.enabled = false;
	bind.current = 0;
	g_hotkey->hotkeys_->at(hash_item).current = 0;
	g_hotkey->hotkeys_->at(hash_item).name_ = item;
	g_hotkey->hotkeys_->at(hash_item).name = std::move(name);
	g_hotkey->hotkeys_->at(hash_item).name_visuals = std::move(name_visual);
}

void c_gui::add_bind(hotkeys& hotkey, int type, std::vector<std::string> name, std::vector<double> items)
{
	hotkey_impl new_hotkey;
	new_hotkey.key = -1;
	new_hotkey.mode = 0;
	new_hotkey.value = std::move(items);
	new_hotkey.type = type;
	new_hotkey.visible = false;
	new_hotkey.enabled = false;
	new_hotkey.current = 0;
	hotkey.binds.push_back(new_hotkey);
	hotkey.name = {};
	hotkey.name_visuals = std::move(name);
}

void c_gui::add_bind(hotkeys& hotkey, int type, std::vector<std::string> name_visual, std::vector<std::string> name, std::vector<double> items)
{
	hotkey_impl& bind = hotkey.binds.emplace_back();
	bind.key = -1;
	bind.mode = 0;
	bind.value = std::move(items);
	bind.type = type;
	bind.visible = false;
	hotkey.name = std::move(name);
	hotkey.name_visuals = std::move(name_visual);

}

bool c_gui::contains_hotkey(std::uint64_t item)
{
	return g_hotkey->hotkeys_->find(item) != g_hotkey->hotkeys_->end();
}

render_size c_gui::get_group_size()
{
	render_size m_rsSize;

	if (current_popup == -1) {
		m_rsSize = m_groups.top().size_;
	}
	else {
		m_rsSize = m_popup.find(current_popup)->second.size_;
	}

	return m_rsSize;
}

std::string c_gui::get_name_key(char key)
{
	switch (key)
	{
	case VK_LBUTTON:
		return "M1";
	case VK_RBUTTON:
		return "M2";
	case VK_MBUTTON:
		return "M3";
	case VK_XBUTTON1:
		return "M4";
	case VK_XBUTTON2:
		return "M5";
	case 186:
		return ";";
	case 222:
		return "'";
	case 17:
		return "CTRL";
	case 18:
		return "ALT";
	case 16:
		return "SHIFT";
	case 20:
		return "CAPS";
	case 9:
		return "TAB";
	case 220:
		return "\\";
	case 219:
		return "[";
	case 221:
		return "]";
	case 188:
		return ",";
	case 190:
		return ".";
	case 191:
		return "/";
	case 0x70:
	case 0x71:
	case 0x72:
	case 0x73:
	case 0x74:
	case 0x75:
	case 0x76:
	case 0x77:
	case 0x78:
	case 0x79:
	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
	case 0x84:
	case 0x85:
	case 0x86:
	case 0x87:
	{
		int number_f = std::fabs((111 - key));
		std::string s_key = std::format("F{}", number_f);
		return s_key;
	}
	default:
		return std::string(1, key);
	}

	return "?";
}

std::wstring c_gui::key_to_string(int key) {
	WCHAR name[32] = L"";
	BYTE kbState[256] = { 0 };
	DWORD idThread;
	idThread = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);
	long code = MapVirtualKeyExW(key, MAPVK_VK_TO_VSC,
		GetKeyboardLayout(idThread)) << 16;
	ToUnicodeEx(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), kbState, name,
		32, 0, GetKeyboardLayout(idThread));

	return name;
}

void c_gui::get_elements()
{
	auto groups = m_groups2.find(active_tab)->second;

	for (auto group : groups) {

		begin_group(group.name_, group.size_, group.same_line_);
		{
			for (auto& element : group.elements) {

				std::string var_ = element.var_;
				auto vars_ = element.vars_;

				if (element.should_multi_weapons) {
					var_ += std::format("_{}", g_user->GetConfig()[xorstr_("group_select")]);
					for (auto& i : vars_) i += std::format("_{}", g_user->GetConfig()[xorstr_("group_select")]);
				}

				switch (element.type_) {
				case 0:
					checkbox(element.name_, var_);
					break;
				case 1:
					slider(element.name_, var_, element.min_, element.max_);
					break;
				case 2:
					combo(element.name_, var_, element.names_);
					break;
				case 3:
					multicombo(element.name_, vars_, element.names_);
					break;
				case 4:
				{

					std::uint32_t hex = g_user->GetConfig()[var_];

					if (!hex)
						g_user->GetConfig()[var_] = 0xffffffff;

					auto r = hex >> 24 & 0xFF;
					auto g = hex >> 16 & 0xFF;
					auto b = hex >> 8 & 0xFF;
					auto a = hex >> 0 & 0xFF;

					auto group_info = m_groups.top();
					text(element.name_, true);
					set_cursor_pos(get_cursor_pos() + render_position(group_info.size_.x - 20 - padding_element.x, padding_element.y));
					g_render->rect_filled(get_position(), render_size(20, 14), render_color(r, g, b, a), 0, 5.f);
					if (begin_popup(element.name_ + xorstr_("_popup"), render_size(20, 14), render_size(150, 200), VK_LBUTTON))
					{
						colorpicker(element.name_ + xorstr_("_colorpicker"), var_);
					}
					end_popup();
					set_cursor_pos(get_cursor_pos() - render_position(group_info.size_.x - 20 - padding_element.x, -12));
					break;
				}
				case 5:
				{
					std::uint32_t hex = g_user->GetConfig()[var_];

					if (!hex)
						g_user->GetConfig()[var_] = 0xffffffff;

					auto r = hex >> 24 & 0xFF;
					auto g = hex >> 16 & 0xFF;
					auto b = hex >> 8 & 0xFF;
					auto a = hex >> 0 & 0xFF;

					auto group_info = m_groups.top();
					set_cursor_pos(get_cursor_pos() + render_position(group_info.size_.x - 50 - padding_element.x, padding_element.y - 27));
					g_render->rect_filled(get_position(), render_size(20, 14), render_color(r, g, b, a), 0, 5.f);
					if (begin_popup(element.name_ + xorstr_("_popup"), render_size(20, 14), render_size(150, 200), VK_LBUTTON))
					{
						colorpicker(element.name_ + xorstr_("_colorpicker"), var_);
					}
					end_popup();
					set_cursor_pos(get_cursor_pos() - render_position(group_info.size_.x - 50 - padding_element.x, -12 - 5));
				}
				break;
				}
			}
		}
		end_group();

	}
}

void c_gui::handle_begin()
{
	has_popup_open_ = has_popup_open();

	g_render->push_override_alpha(animation[hash_menu].base);

	g_render->set_limit(m_window_pos_, window_size);
}

void c_gui::handle_end()
{
	if (direction && !has_active() && !has_popup_open_ && m_moved_window == FNV32("menu"))
	{
		m_window_pos_.x += g_input_system->get_delta_x();
		m_window_pos_.y += g_input_system->get_delta_y();
	}
	
	if (!direction)
	{
		if (m_window_pos_.x > g_render->get_screen_size().x)
			m_window_pos_.x = 0;
		else if (m_window_pos_.x < -window_size.x)
			m_window_pos_.x = 0;

		if (m_window_pos_.y > g_render->get_screen_size().y)
			m_window_pos_.y = 0;
		else if (m_window_pos_.y <= -55)
			m_window_pos_.y = 0;
	}
	g_render->pop_override_alpha();
}

void c_gui::decoration()
{
	const render_position position = m_window_pos_;

	g_render->rect_filled(position, render_size(window_size.x, 55), render_color::black(), c_render_manager::render_flags_::blur, 10.f, render_rounding_flags_::ROUND_RECT_TOP);
	g_render->rect_filled(position, render_size(window_size.x, 55), render_color(13, 13, 14, 240), 0, 10.f, render_rounding_flags_::ROUND_RECT_TOP);

	g_render->rect_filled(position + render_position(0, window_size.y - 56), render_size(window_size.x, 55), render_color::black(), c_render_manager::render_flags_::blur, 10.f, render_rounding_flags_::ROUND_RECT_BOT);
	g_render->rect_filled(position + render_position(0, window_size.y - 56), render_size(window_size.x, 55), render_color(13, 13, 14, 240), 0, 10.f, render_rounding_flags_::ROUND_RECT_BOT);
	g_render->rect_filled(position + render_position(0, 55), render_size(window_size.x + 1, window_size.y - 110), render_color(11, 11, 12, 255));

	g_render->add_texture(position + render_position(351, 15), render_size(58, 25), g_gui->m_texture[1]);

	bool has_active = active_tab == 0 || helper.is_hovered(m_mouse_pos_, rect_(position + render_position(window_size.x - 14 - 30 - 10 - g_render->get_font(2)->calc_text_size(13, FLT_MAX, FLT_MAX, g_user->GetUsername().c_str()).x, 16), render_size(g_render->get_font(2)->calc_text_size(13, FLT_MAX, FLT_MAX, g_user->GetUsername().c_str()).x + 15, 20)));

	animation[std::hash<std::string>()(xorstr_("profile"))].run(has_active);

	g_render->add_text(g_user->GetUsername(), position + render_position(window_size.x - 14 - 30 - 10 - g_render->get_font(2)->calc_text_size(13, FLT_MAX, FLT_MAX, g_user->GetUsername().c_str()).x, 19), helper.animation_color(render_color(86, 86, 87), render_color(221, 221, 221), animation[std::hash<std::string>()(xorstr_("profile"))].base), g_render->get_font(2), 13);

	if (helper.is_hovered(m_mouse_pos_, rect_(position + render_position(window_size.x - 14 - 30 - 10 - g_render->get_font(2)->calc_text_size(13, FLT_MAX, FLT_MAX, g_user->GetUsername().c_str()).x, 16), render_size(g_render->get_font(2)->calc_text_size(13, FLT_MAX, FLT_MAX, g_user->GetUsername().c_str()).x + 15, 20))) && has_pressed(VK_LBUTTON) && active_tab != 0)
		anim_active_id = 0;

	g_render->add_texture_circle(position + render_position(window_size.x - 14 - 30, 12), 16, g_user->GetAvatar(g_user->GetUsername()) == -1 ? 11 : g_user->GetAvatar(g_user->GetUsername()));
}

void get_messages() {
	c_flatbuffers m_buffer2;
	m_buffer2.create_request(HASH("get_message"), 1, {});
	m_buffer2.create_stream();

	g_tls_client->send(m_buffer2.m_buffer.data(), m_buffer2.m_buffer.size());
}

void c_gui::setup()
{
	padding_element = render_position(14, 11);
	hash_menu = std::hash<std::string>()(xorstr_("menu"));
	draw_ = true;
	set_window_size(760, 536);

	auto json = nlohmann::json::parse(json_menu);

	auto& tabs = json[xorstr_("tabs")];

	bool once = true;

	int group_index = 0;
	int tab_index = 0;

	groups_weapon = {
		"Pistol",
		"Rifle",
		"Machine",
		"Revolver",
		"Deagle",
		"SSG08",
		"AWP",
		"AutoSniper"
	};

	for (auto& it : tabs) {
		std::string name = it[xorstr_("name")].get<std::string>();

		auto& groups = it[xorstr_("groups")];

		if (m_groups2.find(group_index) == m_groups2.end())
			m_groups2.try_emplace(group_index);

		bool same_line = false;

		for (auto& group : groups) {
			auto elements = group[xorstr_("elements")];
			auto& group_info = m_groups2.find(group_index)->second;
			gui_group g;
			g.name_ = group[xorstr_("name")].get<std::string>();
			g.size_ = render_size(group[xorstr_("size")][0], group[xorstr_("size")][1]);
			g.same_line_ = group[xorstr_("same_line")].get<bool>();

			for (auto element : elements) {
				auto name_ = element[xorstr_("name")].get<std::string>();
				auto should_weapons = element.contains(xorstr_("should_weapons")) && element[xorstr_("should_weapons")].get<bool>();

				if (should_weapons)
				{
					for (int i{}; i < groups_weapon.size(); i++)
					{
						if (element[xorstr_("config")].is_array())
						{
							std::vector<std::string> temp_names;
							for (auto it : element[xorstr_("config_name")].get<std::vector<std::string>>())
							{
								temp_names.push_back(it);
							}
							std::vector<double> temp_values(temp_names.size());

							std::vector<std::string> temp_name_visual;
							for (auto it : element[xorstr_("config")].get<std::vector<std::string>>())
							{
								temp_name_visual.emplace_back(std::format("{}_{}", it, i));
							}

							create_hotkey(name_, std::hash<std::string>()(std::format("{}_{}", element[xorstr_("config")].get<std::vector<std::string>>()[0], i)), element[xorstr_("type")].get<int>(), temp_names, temp_name_visual, temp_values);
							for (auto it : element[xorstr_("config")].get<std::vector<std::string>>())
							{
								g_user->GetConfig().try_emplace(std::format("{}_{}", it, i));
							}
						}
						else if (element[xorstr_("config_name")].is_array())
						{
							std::vector<double> values;
							values.push_back(false);
							create_hotkey(name_, std::hash<std::string>()(std::format("{}_{}", element[xorstr_("config")].get<std::string>(), i)), element[xorstr_("type")].get<int>(), { std::format("{}_{}", element[xorstr_("config")].get<std::string>(), i) }, values);
							g_user->GetConfig().try_emplace(std::format("{}_{}", element[xorstr_("config")].get<std::string>(),i).c_str());
						}
						else
						{
							create_hotkey(name_, std::hash<std::string>()(std::format("{}_{}", element[xorstr_("config")].get<std::string>(), i)), element[xorstr_("type")].get<int>(), { std::format("{}_{}", element[xorstr_("config")].get<std::string>(), i) }, { false });
							g_user->GetConfig().try_emplace(std::format("{}_{}", element[xorstr_("config")].get<std::string>(), i).c_str());
						}
					}
				}
				else
				{
					if (element[xorstr_("config")].is_array())
					{
						for (auto it : element[xorstr_("config")].get<std::vector<std::string>>())
						{
							g_user->GetConfig().try_emplace(it);
						}
					}
					else
					{
						g_user->GetConfig().try_emplace(element[xorstr_("config")].get<std::string>());
					}
				}

				if (element[xorstr_("config")].is_array())
				{
					std::vector<double> values;
					for (auto it : element[xorstr_("config_name")].get<std::vector<std::string>>())
					{
						values.emplace_back(false);
					}
					create_hotkey(name_, std::hash<std::string>()(element[xorstr_("config")].get<std::vector<std::string>>()[0]), element[xorstr_("type")].get<int>(), element[xorstr_("config_name")].get<std::vector<std::string>>(), values);
					g.elements.emplace_back(gui_element(name_, element[xorstr_("config")].get<std::vector<std::string>>(), element[xorstr_("config_name")].get<std::vector<std::string>>(), element[xorstr_("type")], should_weapons));
					continue;
				}

				if (element[xorstr_("config_name")].is_array()) {
					std::vector<double> values;
					values.push_back(false);
					create_hotkey(name_, std::hash<std::string>()(element[xorstr_("config")].get<std::string>()), element[xorstr_("type")].get<int>(), element[xorstr_("config_name")].get<std::vector<std::string>>(), values);
					g.elements.emplace_back(gui_element(name_, element[xorstr_("config")].get<std::string>(), element[xorstr_("config_name")].get<std::vector<std::string>>(), element[xorstr_("type")], should_weapons));
					continue;
				}

				if (element[xorstr_("type")].get<int>() == 1)
				{
					create_hotkey(name_, std::hash<std::string>()(element[xorstr_("config")].get<std::string>()), element[xorstr_("type")].get<int>(), { name_ }, { false });
					g.elements.emplace_back(gui_element(name_, element[xorstr_("config")].get<std::string>(), element[xorstr_("type")], element[xorstr_("min")].get<float>(), element[xorstr_("max")].get<float>(), should_weapons));
				} else
				{
					create_hotkey(name_, std::hash<std::string>()(element[xorstr_("config")].get<std::string>()), element[xorstr_("type")].get<int>(), { name_ }, { false });
					g.elements.emplace_back(gui_element(name_, element[xorstr_("config")].get<std::string>(), element[xorstr_("type")], should_weapons));
				}
				if (g_gui->elements.find(std::hash<std::string>()(name_)) == g_gui->elements.end())
					g_gui->elements.try_emplace(std::hash<std::string>()(name_), name_, tab_index, group_index, name, g.name_);
			}


			group_info.emplace_back(g);
		}

		
		m_tabs.emplace_back(name, once);
		once = false;
		tab_index++;
		group_index++;
	}

	g_user->GetConfig()[xorstr_("misc_fov")] = 90;
		
	g_gui->m_window_pos_ = (g_render->get_screen_size() / 2) - (g_gui->window_size / 2);

	create_window(xorstr_("Keybind"), render_size(200, 35), render_size(200, 35));
	create_window(xorstr_("Spectators"), render_size(200, 35), render_size(200, 35));
	create_window(xorstr_("Chat"), render_size(300, 35), render_size(300, 396));
	create_window(xorstr_("Menu"), render_size(760, 536), render_size(760, 536));
	create_window(xorstr_("Rapid"), render_size(40, 40), render_size(40, 40));
	//get_messages();
}

void c_gui::menu()
{
	if (!draw_ && animation[hash_menu].base == 0.0f)
		return;

	auto window = find_window("Menu");

	m_window_pos_ = window->m_window_position;

	handle_begin();

	decoration();

	set_cursor_pos(render_position(10, 65));

	std::uint64_t hash_anim = std::hash<std::string>()(xorstr_("anim_elements"));

	if (animation.find(hash_anim) == animation.end())
	{
		c_animation anim_temp;
		anim_temp.base = 1.f;
		anim_temp.timer = 1.f;
		animation.insert_or_assign(hash_anim, anim_temp);
	}

	if (anim_active_id != -1)
	{
		if (anim_active_id != active_tab)
		{
			if (animation[hash_anim].base > 0.01f)
				animation[hash_anim].minus(0.15f);
			else {
				active_tab = anim_active_id;
			}
		}
		else
		{
			if (animation[hash_anim].base >= 1.0f)
			{
				anim_active_id = -1;
			}
			else
				animation[hash_anim].plus(0.15f);
		}
	}

	g_render->push_override_alpha(animation[hash_anim].base);

	if (active_tab == 0)
	{
		home_page();
	}
	else if(active_tab < 5)
	{
		get_elements();
	}
	else
	{
		inventory_page();
	}

	g_render->pop_override_alpha();

	set_cursor_pos(render_position(0, window_size.y - 55));
	tabs();

	g_render->pop_limit();

	g_render->push_override_alpha(animation[hash_anim].base);

	if (active_tab == 3)
		esp_preview();

	g_render->pop_override_alpha();

	handle_end();

}

void c_gui::present()
{
	animation[hash_menu].run(draw_);

	if (!draw_)
	{
		for (auto& popup : m_popup)
		{
			popup.second.is_open_ = false;
		}

		active_search = false;
		active_hotkey = -1;
		active_input = false;

		reset_active_id();
	}

	menu();
}