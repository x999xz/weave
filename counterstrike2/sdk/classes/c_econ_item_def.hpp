#pragma once

#include "../sdk.hpp"

class c_econ_item_definition {
public:
    bool is_weapon();
    bool is_custom_player();
    bool is_knife(bool excludeDefault);
    bool is_glove(bool excludeDefault);

    auto get_model_name() {
        return *reinterpret_cast<const char**>((uintptr_t)(this) + 0xD8);
    }

    auto get_stickers_supported_count() {
        return *reinterpret_cast<int*>((uintptr_t)(this) + 0x100);
    }

    auto get_simple_weapon_name() {
        return *reinterpret_cast<const char**>((uintptr_t)(this) + 0x210);
    }

    auto get_loadout_slot() {
        return *reinterpret_cast<int*>((uintptr_t)(this) + 0x2E8);
    }

    auto get_rarity() {
        return *reinterpret_cast<std::uint8_t*>((uintptr_t)(this) + 0x42);
    }

    auto get_weapon_name() {
        return *reinterpret_cast<const char**>(std::uintptr_t(this) + 0x1f0);
    }

    char pad0[0x8];  // vtable
    void* kv_item;
    uint16_t item_def;
    char pad1[0x5E];
    const char* item_base_name;
    bool proper_name;
    const char* item_type_name;
    char pad2[0x8];
    const char* item_desc_name;
    char pad3[0x10];
    const char* path_image;
    char pad4[0x28];
    const char* path_mdl;
    char pad5[0x8];
    const char* path_mdl2;
    char pad6[0x18];
    const char* path_vft;
};