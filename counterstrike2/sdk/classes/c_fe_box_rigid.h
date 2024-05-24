#pragma once

#include "../sdk.hpp"

struct c_fe_box_rigit
{
public:
	c_transform tmFrame2; // 0x0	
	uint16_t nNode; // 0x20	
	uint16_t nCollisionMask; // 0x22	
	vector vSize; // 0x24	
	uint16_t nVertexMapIndex; // 0x30	
	uint16_t nFlags; // 0x32	
};