#pragma once

#include "../sdk.hpp"

class c_fe_simd_tri
{
public:
	uint32_t nNode[3][4]; // 0x0	
	fltx4 w1; // 0x30	
	fltx4 w2; // 0x40	
	fltx4 v1x; // 0x50	
	// -> x - 0x60
	// -> y - 0x70
	c_four_vectors_2d v2; // 0x60	
};