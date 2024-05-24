#pragma once

#include "../sdk.hpp"

class c_weapon_cs_base;

class c_base_player_weapon : public c_base_model_entity
{
public:
	__forceinline int next_primary_attack_tick() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x15B8 );
	};
	__forceinline float next_primary_attack_tick_ratio() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x15BC );
	};
	__forceinline int next_secondary_attack_tick() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x15C0);
	};
	__forceinline float next_secondary_attack_tick_ratio() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x15C4 );
	};
	__forceinline int clip1() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x15C8 );
	};
	__forceinline int clip2() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x15CC);
	};
public:
	c_econ_item_view* get_econ_view_item()
	{
		return  reinterpret_cast<c_econ_item_view*>(std::uintptr_t(this) + 0x10E8);
	}

	c_weapon_cs_base_v_data* get_weapon_data()
	{
		return *reinterpret_cast<c_weapon_cs_base_v_data**>(std::uintptr_t(this) + 0x368);
	}

	c_weapon_cs_base* get_weapon_base()
	{
		return reinterpret_cast<c_weapon_cs_base*>(this);
	}

	float get_spread();
	float get_accuracy();
	void update_accuracy();

	bool is_knife()
	{
		auto econ_item_view = get_econ_view_item();

		if (!econ_item_view)
			return false;

		auto weapon_data = get_weapon_data();

		if (!weapon_data)
			return false;

		if (econ_item_view->item_index() == e_weapon_item::weapon_taser)
			return false;

		return weapon_data->weapon_type() == e_weapon_type::knife;
	}

	bool is_zeus()
	{
		auto econ_item_view = get_econ_view_item();

		if (!econ_item_view)
			return false;

		return econ_item_view->item_index() == weapon_taser;
	}

	bool is_sniper()
	{
		auto weapon_data = get_weapon_data();

		if (!weapon_data)
			return false;

		return weapon_data->weapon_type() == e_weapon_type::snipers;
	}

	bool is_rifle()
	{
		auto weapon_data = get_weapon_data();

		if (!weapon_data)
			return false;

		return weapon_data->weapon_type() == e_weapon_type::rifles;
	}

	bool is_pistols()
	{
		auto weapon_data = get_weapon_data();

		if (!weapon_data)
			return false;

		return weapon_data->weapon_type() == e_weapon_type::pistols;
	}

	bool is_grenade()
	{
		auto weapon_data = get_weapon_data();

		if (!weapon_data)
			return false;

		return weapon_data->weapon_type() == e_weapon_type::grenade;
	}

	bool is_c4()
	{
		auto weapon_data = get_weapon_data();

		if (!weapon_data)
			return false;

		return weapon_data->weapon_type() == e_weapon_type::c4;
	}
};