#pragma once

#include "../sdk.hpp"

class c_econ_item_view;
class c_econ_item;

class c_cs_player_inventory
{
public:

    auto so_created(soid_t owner, c_shared_object* pObject, ESOCacheEvent eEvent) {
        return CALL_VIRTUAL(void, 0, this, owner, pObject, eEvent);
    }

    auto so_updated(soid_t owner, c_shared_object* pObject, ESOCacheEvent eEvent) {
        return CALL_VIRTUAL(void, 1, this, owner, pObject, eEvent);
    }

    auto so_destroyed(soid_t owner, c_shared_object* pObject, ESOCacheEvent eEvent) {
        return CALL_VIRTUAL(void, 2, this, owner, pObject, eEvent);
    }

    auto get_item_in_loadout(int iClass, int iSlot) {
        return CALL_VIRTUAL(c_econ_item_view*, 8, this, iClass, iSlot);
    }

    bool add_econ_item(c_econ_item* pItem);
    void remove_econ_item(c_econ_item* pItem);
    std::pair<uint64_t, uint32_t> get_highest_id();
    c_econ_item_view* get_item_view_for_item(uint64_t itemID);
    c_econ_item* get_soc_data_for_item(uint64_t itemID);

	c_utl_vector<c_econ_item_view*>& get_items();

	std::uintptr_t* get_client_shared_object()
	{
		return *(std::uintptr_t**)(std::uintptr_t(this) + 0x68);
	}

	soid_t get_owner()
	{
		return *(soid_t*)(std::uintptr_t(this) + 0x10);
	}
};