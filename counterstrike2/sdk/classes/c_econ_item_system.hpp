#pragma once

#include "../sdk.hpp"

class c_econ_item_definition;

inline constexpr uint64_t Helper_GetAlternateIconKeyForWeaponPaintWearItem(uint16_t nDefIdx, uint32_t nPaintId, uint32_t nWear) {
    return (nDefIdx << 16) + (static_cast<uint64_t>(nPaintId) << 2) + nWear;
}

struct alternate_icon_data_t {
    const char* path_image;
    const char* large_path_image;

private:
    char pad0[0x8];  // no idea
    char pad1[0x8];  // no idea
};

class c_paint_kit {
public:
    bool uses_legacy_model();

    int id;
    const char* name;
    const char* description_string;
    const char* description_name;
    char pad0[0x8];  // no idea
    char pad1[0x8];  // no idea
    char pad2[0x8];  // no idea
    char pad3[0x8];  // no idea
    char pad4[0x4];  // no idea
    int rarity;
};

class c_sticker_kit {
public:
    int id;
    int rarity;
    const char* name;
    const char* description_name;
    const char* item_name;
    const char* material_path;
    const char* material_path_no_drips;
    const char* inventory_image;
    char pad[0x18];
    float rotate_start;
    float rotate_end;
    float scale_min;
    float scale_max;
    const char* path_image;
    void* unk;
    const char* path_image_large;
    char pad2[0x20];
};

class c_econ_item_system
{
public:
    auto get_attribute_definition_interface(int iAttribIndex) {
        return CALL_VIRTUAL(void*, 27, this, iAttribIndex);
    }

    CEconItemAttributeDefinition* get_attribute_definition_by_name(const char* name);

    auto& get_sorted_item_definition_map() {
        return *reinterpret_cast<CUtlMap<int, c_econ_item_definition*>*>((uintptr_t)(this) + 0x128);
    }

    auto& get_alternate_icons_map() {
        return *reinterpret_cast<CUtlMap<uint64_t, alternate_icon_data_t>*>((uintptr_t)(this) + 0x278);
    }

    auto& get_paint_kits() {
        return *reinterpret_cast<CUtlMap<int, c_paint_kit*>*>((uintptr_t)(this) + 0x2F0);
    }

    auto& get_sticker_kits() {
        return *reinterpret_cast<CUtlMap<int, c_sticker_kit*>*>((uintptr_t)(this) + 0x318);
    }
};