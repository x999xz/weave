#pragma once

#include "../sdk.hpp"

class c_fe_tapered_capsule_rigid
{
public:
	fltx4 vSphere[2]; // 0x0	
	uint16_t nNode; // 0x20	
	uint16_t nCollisionMask; // 0x22	
	uint16_t nVertexMapIndex; // 0x24	
	uint16_t nFlags; // 0x26	
};