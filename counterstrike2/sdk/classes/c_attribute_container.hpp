#pragma once

#include "../sdk.hpp"

class c_attribute_container
{
public:
	__forceinline c_econ_item_view* item() {
		return reinterpret_cast<c_econ_item_view*>(reinterpret_cast<std::uint64_t>(this) + 0x50);
	};
};