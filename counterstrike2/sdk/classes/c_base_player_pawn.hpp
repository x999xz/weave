#pragma once

#include "../sdk.hpp"

class c_base_model_entity;

class c_base_player_pawn : public c_base_model_entity
{
public:
    __forceinline c_player_weapon_services* weapon_services() {
        return *reinterpret_cast<c_player_weapon_services**>(reinterpret_cast<std::uint64_t>(this) + 0x1100 );
    };
    __forceinline c_cs_player_item_services* item_services() {
        return *reinterpret_cast<c_cs_player_item_services**>(reinterpret_cast<std::uint64_t>(this) + 0x1108 );
    };
    __forceinline c_player_observer_services* observer_services() {
        return *reinterpret_cast<c_player_observer_services**>(reinterpret_cast<std::uint64_t>(this) + 0x1118 );
    };
    __forceinline c_cs_player_camera_services* camera_services() {
        return *reinterpret_cast<c_cs_player_camera_services**>(reinterpret_cast<std::uint64_t>(this) + 0x1138 );
    };
    __forceinline c_player_movement_services* movement_services() {
        return *reinterpret_cast<c_player_movement_services**>(reinterpret_cast<std::uint64_t>(this) + 0x1140);
    };
};