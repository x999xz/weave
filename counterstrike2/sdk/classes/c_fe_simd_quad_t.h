#pragma once

#include "../sdk.hpp"

class c_fe_simd_quad
{
public:
	uint16_t nNode[4][4]; // 0x0	
	fltx4 f4Slack; // 0x20	
	c_four_vectors vShape[4]; // 0x30	
	fltx4 f4Weights[4]; // 0xf0	
};