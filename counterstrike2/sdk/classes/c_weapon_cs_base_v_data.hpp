#pragma once

#include "../sdk.hpp"

class c_weapon_cs_base_v_data
{
public:
	__forceinline int weapon_type() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x248 );
	};
	__forceinline bool is_revolver() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0xC1A);
	};
	__forceinline const char*& name() {
		return *reinterpret_cast<const char**>(reinterpret_cast<std::uint64_t>(this) + 0xC20 );
	};
	__forceinline bool has_burst_mode() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0xC19 );
	};
	__forceinline float max_speed() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xC4C );
	};
	__forceinline float spread() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xC54 );
	};
	__forceinline int recoil_seed() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0xCC8 );
	};
	__forceinline int spread_seed() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0xCCC );
	};
	__forceinline int damage() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0xD40 );
	};
	__forceinline float headshot_multiplier() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xD44 );
	};
	__forceinline float armor_ratio() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xD48);
	};
	__forceinline float penetration() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xD4C);
	};
	__forceinline float range() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xD50 );
	};
	__forceinline float range_modifier() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xD54 );
	};
	__forceinline int bullets() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0xC40 );
	};
	__forceinline float throw_velocity() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0xD78 );
	}
};