#pragma once

#include "../sdk.hpp"

class c_player_movement_services
{
public:
    __forceinline float m_max_speed() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x198 );
    };
    __forceinline float forward_move() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1AC );
    };
    __forceinline float side_move() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1B0 );
    };
    __forceinline bool m_bOldJumpPressed() {
        return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x4AC );
    };
    __forceinline float m_flDuckAmount() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x22C );
    };
    __forceinline float m_flSurfaceFriction() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1FC );
    };
public:
    void try_player_move(__int64 unk_target, vector position, float* unk_penis);
    void set_prediction_command(c_user_cmd* cmd);
    void reset_prediction_command();
};