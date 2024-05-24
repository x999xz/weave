#pragma once

#include "../sdk.hpp"

class c_cs_player_controller : public c_base_player_controller
{
public:
    __forceinline c_handle handle_player_pawn() {
        return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x7E4 );
    };
    __forceinline c_handle handle_observer_pawn() {
        return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x7E8 );
    };
    __forceinline const char* name() {
        return *reinterpret_cast<const char**>(reinterpret_cast<std::uint64_t>(this) + 0x748 );
    };
    __forceinline CCSPlayerController_InventoryServices* m_pInventoryServices() {
        return *reinterpret_cast<CCSPlayerController_InventoryServices**>(reinterpret_cast<std::uint64_t>(this) + 0x700 );
    };
    __forceinline c_user_cmd*& m_current_command() {
        return *(c_user_cmd**)(std::uintptr_t(this) + 0x6b8);
    }
    
public:
    c_cs_player_pawn* get_player_pawn();
    c_cs_player_pawn* get_observer_pawn();
};