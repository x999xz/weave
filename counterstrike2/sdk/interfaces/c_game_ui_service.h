#pragma once
#include "../sdk.hpp"

class c_game_ui_service
{
public:
	bool console_is_visible()
	{
		return reinterpret_cast<bool(__thiscall*)(c_game_ui_service*)>(g_utils->get_virtual(this, 25))(this);
	}
};