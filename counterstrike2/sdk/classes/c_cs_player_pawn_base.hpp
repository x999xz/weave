#pragma once

#include "../sdk.hpp"

class c_base_player_pawn;

class c_cs_player_pawn_base : public c_base_player_pawn
{
public:
	__forceinline c_cs_player_action_tracking_services action_tracking_services() {
		return *reinterpret_cast<c_cs_player_action_tracking_services*>(reinterpret_cast<std::uint64_t>(this) + 0x1490 );
	};
	__forceinline c_cs_player_ping_services ping_services() {
		return *reinterpret_cast<c_cs_player_ping_services*>(reinterpret_cast<std::uint64_t>(this) + 0x12B8 );
	};
	__forceinline c_cs_player_viewmodel_services* viewmodel_services() {
		return *reinterpret_cast<c_cs_player_viewmodel_services**>(reinterpret_cast<std::uint64_t>(this) + 0x12C0 );
	};
	__forceinline bool is_scoped() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x2290 );
	};
	__forceinline bool is_walking() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x2220 );
	};
	__forceinline int armor_value() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x22C0 );
	};
	__forceinline bool has_gun_immunity() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x1314 );
	};
	__forceinline vector get_aim_punch() {
		return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0x14D4 );
	};
	__forceinline c_handle handle_controller() {
		return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x1460 );
	};
	__forceinline float m_flLastSmokeOverlayAlpha() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1408 );
	};
	__forceinline int shots_fired() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x22A4 );
	};
	__forceinline bool m_bWaitForNoAttack() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x22B4 );
	}
};