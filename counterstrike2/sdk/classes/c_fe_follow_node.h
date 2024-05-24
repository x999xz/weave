#pragma once

#include "../sdk.hpp"

class c_fe_follow_node
{
public:
	uint16_t nParentNode; // 0x0	
	uint16_t nChildNode; // 0x2	
	float flWeight; // 0x4	
};