#pragma once

#include "../sdk.hpp"

class c_game_scene_node;
class c_base_anim_graph_controller;
class c_base_player_weapon;

class c_weapon_cs_base : public c_base_player_weapon
{
public:
    __forceinline int recoil_index() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x1730 );
    };
    __forceinline std::uint32_t m_seq_idle() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1640 );
    };
    __forceinline std::uint32_t m_seq_fire_primary() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1644 );
    };
    __forceinline std::uint32_t m_seq_fire_secondary() {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1648 );
    };
    __forceinline c_attribute_container* attribute_manager() {
        return reinterpret_cast<c_attribute_container*>(reinterpret_cast<std::uint64_t>(this) + 0x1098 );
    };
    __forceinline uint32_t original_owner_xuid_low() {
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1540 );
    };
    __forceinline uint32_t original_owner_xuid_high() {
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1544);
    };
    __forceinline uint32_t& paint_kit() {
        return *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1548 );
    };
    __forceinline int original_team_number() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x1754 );
    };
    __forceinline int m_nPostponeFireReadyTicks() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x173C );
    };
    __forceinline float m_flPostponeFireReadyFrac() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1740 );
    };

    uint64_t original_owner_xuid() {
        return ((uint64_t)(original_owner_xuid_high()) << 32) | original_owner_xuid_low();
    }

    vector calculate_spread(unsigned int index);
    void get_spread_pattern(unsigned short item_index, int bullets, int recoil_index, float* r3, float* r4);
public:
    auto get_ref_ehandle() {
        c_handle handle;
        CALL_VIRTUAL(void*, 2, this, &handle);
        return handle;
    }
};