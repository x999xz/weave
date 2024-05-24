#pragma once

#include "../sdk.hpp"

struct c_fe_rigid_collider_indices
{
public:
	uint16_t m_nTaperedCapsuleRigidIndex; // 0x0	
	uint16_t m_nSphereRigidIndex; // 0x2	
	uint16_t m_nBoxRigidIndex; // 0x4	
	uint16_t m_nCollisionPlaneIndex; // 0x6	
};