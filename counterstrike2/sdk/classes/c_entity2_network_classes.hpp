#pragma once

#include "../sdk.hpp"

class c_entity2_network_classes
{
public:
	void add_entity(std::uintptr_t* a1, std::uintptr_t a2)
	{
		return CALL_VIRTUAL(void, 3, this, a1, a2);
	}
};