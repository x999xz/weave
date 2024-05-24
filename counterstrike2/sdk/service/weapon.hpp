#pragma once

#include <cstdint>
#include "../math/vector.hpp"
#include "../sdk.hpp"

class c_player_weapon_services
{
public:
	__forceinline c_handle m_hactive_weapon() {
		return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x58 );
	};
	__forceinline c_utl_vector<c_handle> m_hmyweapons() {
		return *reinterpret_cast<c_utl_vector<c_handle>*>(reinterpret_cast<std::uint64_t>(this) + 0x40 );
	};
	__forceinline float next_attack() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x10B4 );
	};
public:
	__forceinline vector get_shoot_pos()
	{
		vector temp;
		CALL_VIRTUAL(void, 23, this, &temp);
		return temp;
	}
	bool weapon_owns_this_type(const char* name);

	c_shoot_position_history_data* get_shoot_position_history() const {
		auto shoot_position_data = reinterpret_cast<c_shoot_position_history_data*>(uintptr_t(this) + 0xC8);
		return shoot_position_data;
	}
};