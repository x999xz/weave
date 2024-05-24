#pragma once

#include "../sdk.hpp"

class c_econ_entity
{
public:
	__forceinline c_attribute_container attribute_manager() {
		return *reinterpret_cast<c_attribute_container*>(reinterpret_cast<std::uint64_t>(this) + 0x1098 );
	};
};