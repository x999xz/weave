#pragma once

#include "../sdk.hpp"

enum class EGrenadeThrowState : uint32_t
{
	NotThrowing = 0x0,
	Throwing = 0x1,
	ThrowComplete = 0x2,
};

class c_base_cs_grenade : public c_weapon_cs_base
{
public:
	__forceinline float throw_time() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1A88 );
	};
	__forceinline EGrenadeThrowState throw_status() {
		return *reinterpret_cast<EGrenadeThrowState*>(reinterpret_cast<std::uint64_t>(this) + g_pSchemaOffset->m_eThrowStatus); // din pl
	};
	__forceinline bool pin_pulled() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x1A83 );
	};
	__forceinline bool jump_throw() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x1A84 );
	};
	__forceinline bool redraw() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x1A98 );
	};
	__forceinline float drop_time() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1A94 );
	};
	__forceinline bool throw_animating() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x1A85 );
	};
	__forceinline float m_flThrowStrength() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x1A8C );
	};
public:
	int unk_penis()
	{
		return CALL_VIRTUAL(int, 406, this);
	}
};