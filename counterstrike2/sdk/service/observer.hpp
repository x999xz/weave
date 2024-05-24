#pragma once

#include "../sdk.hpp"

class c_player_observer_services
{
public:
    __forceinline int m_observer_mode() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x40 );
    };
    __forceinline c_handle m_hobserver_target() {
        return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x44 );
    };
    __forceinline int m_observer_last_mode() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x48 );
    };
    __forceinline int m_forced_observer_mode() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x4C );
    };
};