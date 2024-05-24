#pragma once

#include "../sdk.hpp"

class c_hitbox
{
public:
	const char* m_name; // 0x0	
	const char* m_sSurfaceProperty; // 0x8	
	const char* m_sBoneName; // 0x10	
	vector m_vMinBounds; // 0x18	
	vector m_vMaxBounds; // 0x24	
	float m_flShapeRadius; // 0x30	
	uint32_t m_nBoneNameHash; // 0x34	
	int32_t m_nGroupId; // 0x38	
	uint8_t m_nShapeType; // 0x3c	
	bool m_bTranslationOnly; // 0x3d	
private:
	uint8_t __pad003e[0x2]; // 0x3e
public:
	uint32_t m_CRC; // 0x40	
	color_t m_cRenderColor; // 0x44	
	uint16_t m_nHitBoxIndex; // 0x48
	char pad2[0x26];
};

class c_hitboxsets
{
public:
	char	  pad_0x0000[0x20]; // 0x0000
	uint32_t  m_nNameHash;		// 0x0020
	char	  pad_0x0024[0x4];	// 0x0024
	__int32	  m_nHitboxCount;	// 0x0028
	char	  pad_0x002C[0x4];	// 0x002C
	c_hitbox* m_hitbox;			// 0x0030
	char	  pad_0x0038[0x18]; // 0x0038
};