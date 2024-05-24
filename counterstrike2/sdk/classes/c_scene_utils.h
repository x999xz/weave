#pragma once

#include "../interfaces/virtual.hpp"

class c_scene_utils
{
public:
    std::uintptr_t* get_unk(std::uint64_t seed)
    {
        return CALL_VIRTUAL(std::uintptr_t*, 25, this, seed);
    }

    c_material_system2_app_system_dict* get_material_system2_app_system_dict() {
        auto material_app_address = std::uintptr_t(this) + 0xB8; // Verify this offset
        if (material_app_address == 0) {
            return nullptr;
        }

        auto material_app = *reinterpret_cast<std::uintptr_t**>(material_app_address);
        if (material_app == nullptr) {
            return nullptr;
        }

        auto dict_address = std::uintptr_t(material_app) + 0x5B8; // Corrected offset based on the latest data
        if (dict_address == 0) {
            return nullptr;
        }

        return reinterpret_cast<c_material_system2_app_system_dict*>(dict_address);
    }
};