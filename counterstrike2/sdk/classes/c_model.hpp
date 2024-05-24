#pragma once

#include "../sdk.hpp"

class c_model
{
public:
	void* vtable;
	c_perm_model_data perm_model_data;
	//const char* m_name;							// 0x0008
	//char			pad_0x0010[0x4];				// 0x0010
	//__int32			m_nFlags;						// 0x0014
	//vector			m_vHullMin;						// 0x0018
	//vector			m_vHullMax;						// 0x0024
	//vector			m_vViewMin;						// 0x0030
	//vector			m_vViewMax;						// 0x003C
	//char			pad_0x0048[0x28];				// 0x0048
	//__int32			m_rendermesh_count;				// 0x0070
	//char			pad_0x0074[0x4];				// 0x0074
	//c_rendermeshes* m_rendermesh;					// 0x0078
	//char			pad_0x0080[0x50];				// 0x0080
	//c_physmodel* m_physmodel;					// 0x00D0
	//__int32			m_animationgroupresource_count; // 0x00D8
	//char			pad_0x00DC[0x4];				// 0x00DC
	//void* m_animationgroupresource;		// 0x00E0
	//char			pad_0x00E8[0x8];				// 0x00E8
	//__int32			m_meshes_count;					// 0x00F0
	//char			pad_0x00F4[0x4];				// 0x00F4
	//void* m_meshes;						// 0x00F8
	//char			pad_0x0100[0x28];				// 0x0100
	//void* N00000135;						// 0x0128
	//char			pad_0x0130[0x28];				// 0x0130
	//__int32			m_names_count;					// 0x0158
	//char			pad_0x015C[0x4];				// 0x015C
	//const char** m_names;						// 0x0160
	//char			pad_0x0168[0x8];				// 0x0168
	//__int32			m_elementindexcount;			// 0x0170
	//char			pad_0x0174[0x4];				// 0x0174
	//uint16_t* m_elementindex;					// 0x0178
	//char			pad_0x0180[0x8];				// 0x0180
	//__int32			N00000141;						// 0x0188
	//char			pad_0x018C[0x4];				// 0x018C
	//void* N00000142;						// 0x0190
	//char			pad_0x0198[0x8];				// 0x0198
	//__int32			N00000144;						// 0x01A0
	//char			pad_0x01A4[0x4];				// 0x01A4
	//void* N00000145;						// 0x01A8
	//char			pad_0x01B0[0x8];				// 0x01B0
	//__int32			m_pos_count;					// 0x01B8
	//char			pad_0x01BC[0x4];				// 0x01BC
	//vector* m_pos;							// 0x01C0
	//char			pad_0x01C8[0x8];				// 0x01C8
	//__int32			m_quat_count;					// 0x01D0
	//char			pad_0x01D4[0x4];				// 0x01D4
	//vector_4d* m_quat;							// 0x01D8
	//char			pad_0x01E0[0x8];				// 0x01E0
	//__int32			m_scale_count;					// 0x01E8
	//char			pad_0x01EC[0x4];				// 0x01EC
	//float* m_scale;						// 0x01F0
	//char			pad_0x01F8[0x8];				// 0x01F8
	//__int32			N00000150;						// 0x0200
	//char			pad_0x0204[0x4];				// 0x0204
	//void* N00000151;						// 0x0208
	//char			pad_0x0210[0x8];				// 0x0210
	//__int32			m_somecount2;					// 0x0218
	//char			pad_0x021C[0x4];				// 0x021C
	//uint16_t* m_somearray2;						// 0x0220
	//char			pad_0x0228[0x8];				// 0x0228
	//__int32			m_somecount1;					// 0x0230
	//char			pad_0x0234[0x4];				// 0x0234
	//uint16_t* m_somearray1;					// 0x0238
	//char			pad_0x0240[0x20];				// 0x0240
	//__int32			N0000015C;						// 0x0260
	//char			pad_0x0264[0x4];				// 0x0264
	//void* N0000015D;						// 0x0268
	//char			pad_0x0270[0x8];				// 0x0270
	//__int32			N0000015F;						// 0x0278
	//char			pad_0x027C[0x4];				// 0x027C
	//void* N00000160;						// 0x0280
	//char			pad_0x0288[0x40];				// 0x0288
	//__int32			N00000169;						// 0x02C8
	//char			pad_0x02CC[0x4];				// 0x02CC
	//void* N0000016A;						// 0x02D0
	//char			pad_0x02D8[0x8];				// 0x02D8
	//__int32			m_somecount3;					// 0x02E0
	//char			pad_0x02E4[0x4];				// 0x02E4
	//uint16_t* m_somearray3;					// 0x02E8
	//char			pad_0x02F0[0x58];				// 0x02F0
	//void* N00000179;						// 0x0348
	//char			pad_0x0350[0x8];				// 0x0350
	//__int32			N0000017B;						// 0x0358
	//char			pad_0x035C[0x4];				// 0x035C
	//void* N0000017C;						// 0x0360
	//char			pad_0x0368[0x70];				// 0x0368
	//__int32			N0000018B;						// 0x03D8
	//char			pad_0x03DC[0x4];				// 0x03DC
	//void* N0000018C;						// 0x03E0
	//char			pad_0x03E8[0x30];				// 0x03E8
	//__int32			N00000193;						// 0x0418
	//char			pad_0x041C[0x4];				// 0x041C
	//void* N00000194;						// 0x0420
	//char			pad_0x0428[0x5D8];				// 0x0428

	c_hitbox* get_hitbox(int index)
	{
		if (!this)
			return nullptr;

		if (perm_model_data.m_refMeshes.get_size() <= 0)
			return nullptr;

		auto mesh = perm_model_data.m_refMeshes.get_element(0);
		if (!mesh)
			return nullptr;

		auto hithoxsets = mesh->m_hitboxsets;
		if (!hithoxsets)
			return nullptr;

		if (hithoxsets[0].m_nHitboxCount <= 0 || index > hithoxsets[0].m_nHitboxCount)
			return nullptr;

		auto hitbox = hithoxsets[0].m_hitbox;
		if (!hitbox)
			return nullptr;

		return &hitbox[index];
	}
	const char* get_bone_name(int index)
	{
		if (perm_model_data.m_modelSkeleton.m_boneName.get_size() <= 0 || perm_model_data.m_modelSkeleton.m_boneName.get_size() > index)
			return "root";

		return perm_model_data.m_modelSkeleton.m_boneName.get_element(index).get();
	}

	const char* get_hitbox_name(int index)
	{
		auto hitbox = get_hitbox(index);

		if (!hitbox)
			return nullptr;

		return hitbox->m_name;
	}
	int get_max_hitboxes()
	{
		if (perm_model_data.m_refMeshes.get_size() <= 0)
			return -1;

		auto meshes = perm_model_data.m_refMeshes.get_element(0);
		if (!meshes)
			return -1;

		auto hithoxsets = meshes->m_hitboxsets;
		if (!hithoxsets)
			return -1;

		return hithoxsets[0].m_nHitboxCount;
	}
public:
	std::uint32_t num_bones();
	std::uint32_t bone_flags(int index);
	std::uint32_t bone_parent(int index);
};