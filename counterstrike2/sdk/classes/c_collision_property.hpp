#pragma once

#include "../sdk.hpp"

class c_collision_property
{
public:
    __forceinline vector mins() {
        return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0x40 );
    };
    __forceinline vector maxs() {
        return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0x4C );
    };
    __forceinline std::uint16_t solid_flags() {
        return *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint64_t>(this) + 0x5A );
    };
    __forceinline std::uint16_t solid_type() {
        return *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint64_t>(this) + 0x5A + 1);
    };

    __forceinline std::uint32_t collision_function_mask()
    {
        return *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(this) + 0x3b);
    }
};