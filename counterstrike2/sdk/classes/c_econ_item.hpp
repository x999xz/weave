#pragma once

#include "../sdk.hpp"

class c_econ_item {
    void set_dynamic_attribute_value(int index, void* value);
    void set_dynamic_attribute_value_string(int index, const char* value);

public:
    c_econ_item* create_instance();

    auto destruct() { return CALL_VIRTUAL(void, 1, this, true); }

    void set_paint_kit(float kit) { set_dynamic_attribute_value(6, &kit); }
    void set_paint_seed(float seed) { set_dynamic_attribute_value(7, &seed); }
    void set_paint_wear(float wear) { set_dynamic_attribute_value(8, &wear); }
    void set_stat_trak(int count) { set_dynamic_attribute_value(80, &count); }
    void set_stat_trak_type(int type) { set_dynamic_attribute_value(81, &type); }
    void set_custom_name(const char* pName);
    void set_sticker(int index, int id);

    char pad0[0x10];  // 2 vtables
    uint64_t id;
    uint64_t original_id;
    void* custom_data_optimized_object;
    uint32_t account_id;
    uint32_t inventory;
    uint16_t def_index;
    uint16_t origin : 5;
    uint16_t quality : 4;
    uint16_t level : 2;
    uint16_t rarity : 4;
    uint16_t dirtybit_in_use : 1;
    int16_t item_set;
    int so_update_frame;
    uint8_t flags;
};