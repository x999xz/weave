#pragma once

#include "../sdk.hpp"

class c_fe_tri
{
public:
	uint16_t nNode[3]; // 0x0	
	float w1; // 0x8	
	float w2; // 0xc	
	float v1x; // 0x10	
	vector_2d v2; // 0x14	
};