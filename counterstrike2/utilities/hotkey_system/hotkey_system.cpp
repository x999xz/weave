// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "hotkey_system.h"
#include "../input_system/input_system.h"
#include "../../gui/gui.h"
#include "../../sdk/sdk.hpp"

void c_hotkey::update()
{

	if (!Interfaces::engine)
		return;

	if (!Interfaces::engine->is_connected() || !Interfaces::engine->is_in_game())
		return;

	auto ccsgo_hudchat = (c_csgo_hud_chat*)g_cs2->find_hud("CCSGO_HudChat");

	if (ccsgo_hudchat && ccsgo_hudchat->is_open)
		return;

	if (!Interfaces::m_game_ui_service)
		return;

	if (Interfaces::m_game_ui_service->console_is_visible())
		return;

	mutex_.lock();

	for (auto it = hotkeys_->begin(); it != hotkeys_->end(); it++)
	{
		auto& hotkey_list = it->second.binds;

		for (auto& hotkey : hotkey_list)
		{
			if (hotkey.key == -1 || g_gui->active_hotkey != -1)
				continue;

			switch (hotkey.mode)
			{
			case e_hotkey_mode::hold:
				hotkey.enabled = g_gui->has_hold(hotkey.key);
				break;
			case e_hotkey_mode::toggle:
			{
				if (g_gui->has_pressed(hotkey.key))
				{
					bool active = hotkey.enabled = !hotkey.enabled;

					for (auto& hotkey_ : hotkey_list)
					{
						hotkey_.enabled = false;
					}

					hotkey.enabled = active;
				}
			}
			break;
			}
		}
	}

	mutex_.unlock();
}

std::vector<std::string> hotkeys::get_binds()
{
	std::vector<std::string> m_sBinds;

	for (auto bind : binds)
	{
		std::string b = xorstr_("Bind");

		if (bind.key != -1)
			b += " [" + g_gui->get_name_key(bind.key) + "]";

		m_sBinds.push_back(b);
	}

	return m_sBinds;
}