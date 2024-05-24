// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"

void c_gui::hotkey(std::string name, std::string hash_name, render_position position)
{
	if (name.find(xorstr_("_value_bind")) != std::string::npos || name.find(xorstr_("_visible_bind")) != std::string::npos)
		return;

	auto backup = get_cursor_pos();

	set_cursor_pos(get_cursor_pos() + position);

	if (!begin_popup(name + xorstr_("_popup"), render_size(20, 14), render_size(180, 155), VK_RBUTTON))
	{
		end_popup();
		set_cursor_pos(backup);
		return;
	}

	auto hash = std::hash<std::string>()(hash_name);
	auto& hotkey = g_hotkey->hotkeys_->at(hash);

	int backup_current = hotkey.current;

	if (hotkey.name_.find(name) == std::string::npos)
		hotkey.name_ = name;

	std::vector<std::string> binds = hotkey.get_binds();

	binds.push_back(xorstr_("Add Bind"));
	g_render->push_override_buffer(5);
	combo(xorstr_("Binds"), xorstr_("Binds"), hotkey.current, binds);
	g_render->pop_override_buffer(3);

	if (removed_bind != -1)
	{
		if (hotkey.binds.size() > removed_bind)
			hotkey.binds.erase(hotkey.binds.begin() + removed_bind);

		removed_bind = -1;

		if (hotkey.binds.size() == hotkey.current)
			hotkey.current--;
	}

	if (hotkey.current == hotkey.binds.size())
	{
		std::vector<std::string> temp_name;
		std::vector<double> temp_value(1);
		temp_name.push_back(hash_name);
		add_bind(hotkey, 0, temp_name, temp_value);
		hotkey.current = backup_current;
	}

	std::vector<std::string> mode = { xorstr_("Hold"), xorstr_("Toggle") };

	g_render->push_override_buffer(4);
	combo(xorstr_("Mode"), xorstr_("Mode"), hotkey.binds[hotkey.current].mode, mode);
	g_render->pop_override_buffer(3);
	text(xorstr_("Key"), true);

	std::string key = xorstr_("[ ]");
	int key_ = hotkey.binds[hotkey.current].key;

	if (hotkey.binds[hotkey.current].key != -1)
	{
		key.clear();
		key = get_name_key(hotkey.binds[hotkey.current].key);
	}

	set_cursor_pos(get_cursor_pos() + render_position(180 - 50, 0));

	if (helper.is_hovered(get_mouse_pos(), rect_(get_position(), render_size(30, 30))) && has_pressed(VK_LBUTTON))
	{
		active_hotkey = hash;
		buttons[VK_LBUTTON] = {};
	}

	if (active_hotkey == hash) {
		key = "[ - ]";

		for (int i{}; i < 256; i++)
		{
			if (!has_pressed(i))
				continue;

			if (i == VK_ESCAPE)
			{
				hotkey.binds[hotkey.current].key = -1;
				active_hotkey = -1;
				buttons[VK_LBUTTON] = c_buttons();
				break;
			}

			auto k = i;

			if (isupper(k) && i < 0x70 && i > 0x87)
				k = std::tolower(k);

			hotkey.binds[hotkey.current].key = i;
			active_hotkey = -1;
			buttons[VK_LBUTTON] = c_buttons();
			break;
		}
	}

	text(key, false);
	set_cursor_pos(get_cursor_pos() - render_position(180 - 50, 0));
	text(xorstr_("Value"), true);
	bool value2 = hotkey.binds[hotkey.current].value[0];
	checkbox(std::format("%s_value_bind", name), std::format("%s_value_bind", hash_name), value2);
	hotkey.binds[hotkey.current].value[0] = value2;

	text(xorstr_("Visible"), true);
	checkbox(std::format("%s_visible_bind", name), std::format("%s_visible_bind", hash_name), hotkey.binds[hotkey.current].visible);

	end_popup();
	set_cursor_pos(backup);
}