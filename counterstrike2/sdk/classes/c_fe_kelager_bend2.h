#pragma once

#include "../sdk.hpp"

struct c_fe_kelager_bend2
{
public:
	float flWeight[3]; // 0x0	
	float flHeight0; // 0xc	
	uint16_t nNode[3]; // 0x10	
	uint16_t nReserved; // 0x16	
};