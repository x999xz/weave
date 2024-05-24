// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "c_cs_player_inventory.hpp"

enum EEconTypeID {
    k_EEconTypeItem = 1,
    k_EEconTypePersonaDataPublic = 2,
    k_EEconTypeGameAccountClient = 7,
    k_EEconTypeGameAccount = 8,
    k_EEconTypeEquipInstance = 31,
    k_EEconTypeDefaultEquippedDefinitionInstance = 42,
    k_EEconTypeDefaultEquippedDefinitionInstanceClient = 43,
    k_EEconTypeCoupon = 45,
    k_EEconTypeQuest = 46,
};

c_utl_vector<c_econ_item_view*>& c_cs_player_inventory::get_items()
{
	return *reinterpret_cast<c_utl_vector<c_econ_item_view*>*>(this + 0x20);
}

c_gc_client_shared_object_type_cache*  create_base_type_cache(c_cs_player_inventory* pInventory) {

    if (!Interfaces::m_gc_client) 
        return nullptr;

    auto pGCClient = Interfaces::m_gc_client->gc_client();
    if (!pGCClient) return nullptr;

    c_gc_client_shared_object_cache* pSOCache =
        pGCClient->find_so_cache(pInventory->get_owner());
    if (!pSOCache) return nullptr;

    return pSOCache->create_base_type_cache(k_EEconTypeItem);
}

bool c_cs_player_inventory::add_econ_item(c_econ_item* pItem) {
    // Helper function to aid in adding items.
    if (!pItem) return false;

    c_gc_client_shared_object_type_cache* pSOTypeCache = ::create_base_type_cache(this);
    if (!pSOTypeCache || !pSOTypeCache->add_object((c_shared_object*)pItem))
        return false;

    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "44 88 4C 24 20 44 88 44 24 18 48" );
    pattern.as<bool(__fastcall*)(void*, void*, bool, bool, bool)>()(this, pItem, true, true, true);
    return true;
}

void c_cs_player_inventory::remove_econ_item(c_econ_item* item) {
    
    if (!item) 
        return;

    c_gc_client_shared_object_type_cache* so_type_cache = ::create_base_type_cache(this);

    if (!so_type_cache) 
        return;

    const c_utl_vector<c_econ_item*>& pSharedObjects = so_type_cache->get_vec_objects<c_econ_item*>();

    so_destroyed(get_owner(), (c_shared_object*)item, eSOCacheEvent_Incremental);
    so_type_cache->remove_object((c_shared_object*)item);

    item->destruct();
}

std::pair<uint64_t, uint32_t> c_cs_player_inventory::get_highest_id() {
    uint64_t max_item_id = 0;
    uint32_t max_inventory_id = 0;

    c_gc_client_shared_object_type_cache* so_type_cache = ::create_base_type_cache(this);
    if (so_type_cache) {
        c_utl_vector<c_econ_item*>& items = so_type_cache->get_vec_objects<c_econ_item*>();

        for (int i{}; i < items.get_size(); i++)
        { 
            auto it = items.get_element(i);

            if (!it) 
                continue;

            // Checks if item is default.
            if ((it->id & 0xF000000000000000) != 0) continue;

            max_item_id = std::max(max_item_id, it->id);
            max_inventory_id = std::max(max_inventory_id, it->inventory);
        }
    }

    return std::make_pair(max_item_id, max_inventory_id);
}

c_econ_item_view* c_cs_player_inventory::get_item_view_for_item(uint64_t item_id) {
    
    c_econ_item_view* item_view = nullptr;

    c_utl_vector<c_econ_item_view*>& items = get_items();
    for (int i{}; i < items.get_size(); i++)
    {
        auto it = items.get_element(i);
        if (it && it->item_id() == item_id) {
            item_view = it;
            break;
        }
    }

    return item_view;
}

c_econ_item* c_cs_player_inventory::get_soc_data_for_item(uint64_t item_id) {
    
    c_econ_item* soc_data = nullptr;

    c_gc_client_shared_object_type_cache* so_type_cache = ::create_base_type_cache(this);
    if (so_type_cache) {
       c_utl_vector<c_econ_item*>& items = so_type_cache->get_vec_objects<c_econ_item*>();

        for (int i{}; i < items.get_size(); i++)
        {
            auto it = items.get_element(i);

            if (it && it->id == item_id) {
                soc_data = it;
                break;
            }
        }
    }

    return soc_data;
}