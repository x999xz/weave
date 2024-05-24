#pragma once

#include "../sdk.hpp"

class c_player_ping
{
public:
    __forceinline c_cs_player_pawn* get_player() {
        return *reinterpret_cast<c_cs_player_pawn**>(reinterpret_cast<std::uint64_t>(this) + 0x580 );
    };
};