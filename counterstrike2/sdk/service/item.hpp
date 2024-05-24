#pragma once

#include "../sdk.hpp"

class c_cs_player_item_services
{
public:
    __forceinline bool m_has_defuser() {
        return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x40 );
    };
    __forceinline bool m_has_helmet() {
        return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x41 );
    };
    __forceinline bool m_has_heavy_armor() {
        return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x42 );
    };
};