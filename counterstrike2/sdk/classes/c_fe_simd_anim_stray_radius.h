#pragma once

#include "../sdk.hpp"

struct c_fe_simd_anim_stray_radius
{
public:
	uint16_t nNode[2][4]; // 0x0	
	fltx4 flMaxDist; // 0x10	
	fltx4 flRelaxationFactor; // 0x20	
};