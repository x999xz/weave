#pragma once

#include "../sdk.hpp"

class c_cs_player_inventory;

class c_cs_inventory_manager
{
public:

	auto equip_item(int team, int slot, uint64_t item_id) {
		return CALL_VIRTUAL(bool, 54, this, team, slot, item_id);
	}

	c_cs_player_inventory* get_local_inventory()
	{
		return *(c_cs_player_inventory**)(std::uintptr_t(this) + 0x3D1C0);
	}
};