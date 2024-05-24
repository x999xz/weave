#pragma once

#include "../sdk.hpp"

class c_cs_player_ping_services
{
public:
    __forceinline unsigned long m_handle_player_ping() {
        return *reinterpret_cast<unsigned long*>(reinterpret_cast<std::uint64_t>(this) + 0x40 );
    }
};