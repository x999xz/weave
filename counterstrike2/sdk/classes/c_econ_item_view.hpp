#pragma once

#include "../sdk.hpp"

class c_econ_item_view
{
public:
	const char* get_item_name(bool uncustomized = true);
public:
	__forceinline std::uint16_t& item_index() {
		return *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1BA );
	};
	__forceinline uint64_t& item_id() {
		return *reinterpret_cast<uint64_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1C8 );
	};
	__forceinline uint32_t& item_id_low() {
		return *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1D4 );
	};
	__forceinline uint32_t& item_id_high() {
		return *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1D0 );
	};
	__forceinline uint32_t& account_id() {
		return *reinterpret_cast<uint32_t*>(reinterpret_cast<std::uint64_t>(this) + 0x1D8 );
	};
public:
	auto custom_paint_kit_index() { 
		return CALL_VIRTUAL(int, 2, this);
	}
	auto static_data() {
		return CALL_VIRTUAL(c_econ_item_definition*, 13, this);
	}
};