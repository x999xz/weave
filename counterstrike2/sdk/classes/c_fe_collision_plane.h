#pragma once

#include "../sdk.hpp"

class c_fe_collision_plane
{
public:
	uint16_t nCtrlParent; // 0x0	
	uint16_t nChildNode; // 0x2	
	// -> m_vNormal - 0x4
	// -> m_flOffset - 0x10
	c_rn_plane m_Plane; // 0x4	
	float flStrength; // 0x14	
};