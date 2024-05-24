#pragma once

#include "../sdk.hpp"

class c_planted
{
public:
    __forceinline bool bomb_ticking() {
        return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0xED8 );
    };
    __forceinline int bomb_site() {
        return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0xEDC );
    };
    __forceinline float blow() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xF08 );
    };
    __forceinline float timer_length() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xF10 );
    };
    __forceinline float defuse_length() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xF24 );
    };
    __forceinline float defuse_count_down() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xF28 );
    };
    __forceinline float bomb_defused() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xF2C);
    };
    __forceinline unsigned long handle_bomb_defuser() {
        return *reinterpret_cast<unsigned long*>(reinterpret_cast<std::uint64_t>(this) + 0xF30 );
    };
};