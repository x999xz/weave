#pragma once

#include "../sdk.hpp"

class c_fe_quad
{
public:
	uint16_t nNode[4]; // 0x0	
	float flSlack; // 0x8	
	vector_4d vShape[4]; // 0xc	
};