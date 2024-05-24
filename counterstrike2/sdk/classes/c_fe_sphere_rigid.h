#pragma once

#include "../sdk.hpp"

class c_fe_sphere_rigid
{
public:
	fltx4 vSphere; // 0x0	
	uint16_t nNode; // 0x10	
	uint16_t nCollisionMask; // 0x12	
	uint16_t nVertexMapIndex; // 0x14	
	uint16_t nFlags; // 0x16	
};