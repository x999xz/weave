#pragma once

#include "../sdk.hpp"

class c_rendermesh
{
public:
	char		   pad_0x0000[0x28];	// 0x0000
	vector		   m_vMinBounds;		// 0x0028
	vector		   m_vMaxBounds;		// 0x0034
	__int32		   m_drawCallsCount;	// 0x0040
	char		   pad_0x0044[0x4];		// 0x0044
	c_drawcalls* m_drawCalls;			// 0x0048
	char		   pad_0x0050[0x68];	// 0x0050
	__int32		   m_skeletoncount;		// 0x00B8
	char		   pad_0x00BC[0x4];		// 0x00BC
	c_bones* m_skeleton;			// 0x00C0
	char		   pad_0x00C8[0x8];		// 0x00C8
	__int32		   m_hashescount;		// 0x00D0
	char		   pad_0x00D4[0x4];		// 0x00D4
	uint32_t* m_hashes;			// 0x00D8
	char		   pad_0x00E0[0x20];	// 0x00E0
	__int32		   m_nBoneWeightCount;	// 0x0100
	char		   pad_0x0104[0xC];		// 0x0104
	c_attachments* m_attachments;		// 0x0110
	__int32		   m_attachments_count; // 0x0118
	char		   pad_0x011C[0x1C];	// 0x011C
	c_hitboxsets* m_hitboxsets;		// 0x0138
	__int32		   m_nHitboxSets;		// 0x0140
};

class c_rendermeshes
{
public:
	c_rendermesh* m_meshes;
};