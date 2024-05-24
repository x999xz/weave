#pragma once

#include "../sdk.hpp"

class CAnimDesc_Flag
{
public:
	bool m_bLooping; // 0x0	
	bool m_bAllZeros; // 0x1	
	bool m_bHidden; // 0x2	
	bool m_bDelta; // 0x3	
	bool m_bLegacyWorldspace; // 0x4	
	bool m_bModelDoc; // 0x5	
	bool m_bImplicitSeqIgnoreDelta; // 0x6	
	bool m_bAnimGraphAdditive; // 0x7	
};

class CAnimBoneDifference
{
public:
	c_buffer_string m_name; // 0x0	
	c_buffer_string m_parent; // 0x10	
	vector m_posError; // 0x20	
	bool m_bHasRotation; // 0x2c	
	bool m_bHasMovement; // 0x2d	
};

class CAnimMorphDifference
{
public:
	c_buffer_string m_name; // 0x0	
};

class CAnimUserDifference
{
public:
	c_buffer_string m_name; // 0x0	
	int32_t m_nType; // 0x10	
};

class CAnimEncodeDifference
{
public:
	c_utl_vector< CAnimBoneDifference > m_boneArray; // 0x0	
	c_utl_vector< CAnimMorphDifference > m_morphArray; // 0x18	
	c_utl_vector< CAnimUserDifference > m_userArray; // 0x30	
	c_utl_vector< unsigned char > m_bHasRotationBitArray; // 0x48	
	c_utl_vector< unsigned char > m_bHasMovementBitArray; // 0x60	
	c_utl_vector< unsigned char > m_bHasMorphBitArray; // 0x78	
	c_utl_vector< unsigned char > m_bHasUserBitArray; // 0x90	
};

class CAnimFrameBlockAnim
{
public:
	int32_t m_nStartFrame; // 0x0	
	int32_t m_nEndFrame; // 0x4	
	c_utl_vector< int32_t > m_segmentIndexArray; // 0x8	
};

class CAnimEncodedFrames
{
public:
	c_buffer_string m_fileName; // 0x0	
	int32_t m_nFrames; // 0x10	
	int32_t m_nFramesPerBlock; // 0x14	
	c_utl_vector< CAnimFrameBlockAnim > m_frameblockArray; // 0x18	
	// -> m_boneArray - 0x30
	// -> m_morphArray - 0x48
	// -> m_userArray - 0x60
	// -> m_bHasRotationBitArray - 0x78
	// -> m_bHasMovementBitArray - 0x90
	// -> m_bHasMorphBitArray - 0xa8
	// -> m_bHasUserBitArray - 0xc0
	CAnimEncodeDifference m_usageDifferences; // 0x30	
};

class CAnimEventDefinition
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x8]; // 0x0
public:
	int32_t m_nFrame; // 0x8	
	float m_flCycle; // 0xc	
	//KeyValues3 m_EventData; // 0x10	
	// MKV3TransferName "m_sOptions"
	c_buffer_string m_sLegacyOptions; // 0x20	
	//CGlobalSymbol m_sEventName; // 0x30	
};

class CAnimMovement
{
public:
	int32_t endframe; // 0x0	
	int32_t motionflags; // 0x4	
	float v0; // 0x8	
	float v1; // 0xc	
	float angle; // 0x10	
	vector vector_; // 0x14	
	vector position; // 0x20	
};

class CAnimLocalHierarchy
{
public:
	c_buffer_string m_sBone; // 0x0	
	c_buffer_string m_sNewParent; // 0x10	
	int32_t m_nStartFrame; // 0x20	
	int32_t m_nPeakFrame; // 0x24	
	int32_t m_nTailFrame; // 0x28	
	int32_t m_nEndFrame; // 0x2c	
};

class CAnimActivity
{
public:
	c_buffer_string m_name; // 0x0	
	int32_t m_nActivity; // 0x10	
	int32_t m_nFlags; // 0x14	
	int32_t m_nWeight; // 0x18	
};

class CAnimSequenceParams
{
public:
	float m_flFadeInTime; // 0x0	
	float m_flFadeOutTime; // 0x4	
};

class CAnimDesc
{
public:
	c_buffer_string m_name; // 0x0	
	// -> m_bLooping - 0x10
	// -> m_bAllZeros - 0x11
	// -> m_bHidden - 0x12
	// -> m_bDelta - 0x13
	// -> m_bLegacyWorldspace - 0x14
	// -> m_bModelDoc - 0x15
	// -> m_bImplicitSeqIgnoreDelta - 0x16
	// -> m_bAnimGraphAdditive - 0x17
	CAnimDesc_Flag m_flags; // 0x10	
	float fps; // 0x18	
private:
	[[maybe_unused]] uint8_t __pad001c[0x4]; // 0x1c
public:
	// MKV3TransferName "m_pData"
	// -> m_fileName - 0x20
	// -> m_nFrames - 0x30
	// -> m_nFramesPerBlock - 0x34
	// -> m_frameblockArray - 0x38
	// -> m_usageDifferences - 0x50
	CAnimEncodedFrames m_Data; // 0x20	
	c_utl_vector< CAnimMovement > m_movementArray; // 0xf8	
	c_utl_vector< CAnimEventDefinition > m_eventArray; // 0x110	
	c_utl_vector< CAnimActivity > m_activityArray; // 0x128	
	c_utl_vector< CAnimLocalHierarchy > m_hierarchyArray; // 0x140	
	float framestalltime; // 0x158	
	vector m_vecRootMin; // 0x15c	
	vector m_vecRootMax; // 0x168	
private:
	[[maybe_unused]] uint8_t __pad0174[0x4]; // 0x174
public:
	c_utl_vector< vector > m_vecBoneWorldMin; // 0x178	
	c_utl_vector< vector > m_vecBoneWorldMax; // 0x190	
	// -> m_flFadeInTime - 0x1a8
	// -> m_flFadeOutTime - 0x1ac
	CAnimSequenceParams m_sequenceParams; // 0x1a8	
};

class CAnimDecoder
{
public:
	c_buffer_string m_szName; // 0x0	
	int32_t m_nVersion; // 0x10	
	int32_t m_nType; // 0x14	
};

class CAnimFrameSegment
{
public:
	int32_t m_nUniqueFrameIndex; // 0x0	
	uint32_t m_nLocalElementMasks; // 0x4	
	int32_t m_nLocalChannel; // 0x8	
private:
	[[maybe_unused]] uint8_t __pad000c[0x4]; // 0xc
public:
	c_utl_binary_block m_container; // 0x10	
};

class CAnimData
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x10]; // 0x0
public:
	c_buffer_string m_name; // 0x10	
	c_utl_vector< CAnimDesc > m_animArray; // 0x20	
	c_utl_vector< CAnimDecoder > m_decoderArray; // 0x38	
	int32_t m_nMaxUniqueFrameIndex; // 0x50	
private:
	[[maybe_unused]] uint8_t __pad0054[0x4]; // 0x54
public:
	c_utl_vector< CAnimFrameSegment > m_segmentArray; // 0x58	
};

struct ModelSkeletonData_t
{
public:
	c_utl_vector< c_utl_string > m_boneName; // 0x0	
	char pad[0x8];
	c_utl_vector< int16_t > m_nParent; // 0x18	
	char pad2[0x8];
	c_utl_vector< float > m_boneSphere; // 0x30	
	char pad3[0x8];
	c_utl_vector< uint32 > m_nFlag; // 0x48	
	char pad4[0x8];
	c_utl_vector< vector > m_bonePosParent; // 0x60	
	char pad5[0x8];
	c_utl_vector< c_quaternion_storage > m_boneRotParent; // 0x78	
	char pad6[0x8];
	c_utl_vector< float > m_boneScaleParent; // 0x90	
	char pad7[0x8];
};

class CModelConfigElement
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x8]; // 0x0
public:
	c_utl_string m_ElementName; // 0x8	
	c_utl_vector< CModelConfigElement* > m_NestedElements; // 0x10	
};


class CModelConfig
{
public:
	c_utl_string m_ConfigName; // 0x0	
	c_utl_vector< CModelConfigElement* > m_Elements; // 0x8	
	bool m_bTopLevel; // 0x20	
};

class CModelConfigList
{
public:
	bool m_bHideMaterialGroupInTools; // 0x0	
	bool m_bHideRenderColorInTools; // 0x1	
private:
	[[maybe_unused]] uint8_t __pad0002[0x6]; // 0x2
public:
	c_utl_vector< CModelConfig* > m_Configs; // 0x8	
};

enum class ModelBoneFlexComponent_t : uint32_t
{
	MODEL_BONE_FLEX_INVALID = 0xfffffff,
	MODEL_BONE_FLEX_TX = 0x0,
	MODEL_BONE_FLEX_TY = 0x1,
	MODEL_BONE_FLEX_TZ = 0x2,
};

struct ModelBoneFlexDriverControl_t
{
public:
	ModelBoneFlexComponent_t m_nBoneComponent; // 0x0	
	c_utl_string m_flexController; // 0x8	
	uint32_t m_flexControllerToken; // 0x10	
	float m_flMin; // 0x14	
	float m_flMax; // 0x18	
};

struct ModelBoneFlexDriver_t
{
public:
	c_utl_string m_boneName; // 0x0	
	uint32_t m_boneNameToken; // 0x8	
private:
	[[maybe_unused]] uint8_t __pad000c[0x4]; // 0xc
public:
	c_utl_vector< ModelBoneFlexDriverControl_t > m_controls; // 0x10	
};

class i_material;

struct MaterialGroup_t
{
public:
	c_utl_string m_name; // 0x0	
	c_utl_vector< strong_handle< i_material > > m_materials; // 0x8	
};

struct PermModelDataAnimatedMaterialAttribute_t
{
public:
	c_utl_string m_AttributeName; // 0x0	
	int32_t m_nNumChannels; // 0x8	
};

class CSequenceGroupData
{
public:
	char pad[0x138];
};

class CAnimBone
{
public:
	c_buffer_string m_name; // 0x0	
	int32_t m_parent; // 0x10	
	vector m_pos; // 0x14	
	c_quaternion_storage m_quat; // 0x20	
	float m_scale; // 0x30	
	c_quaternion_storage m_qAlignment; // 0x34	
	int32_t m_flags; // 0x44	
};

// Registered binary: animationsystem.dll (project 'animationsystem')
// Alignment: 8
// Size: 0x18
// 
// MGetKV3ClassDefaults
class CAnimUser
{
public:
	c_buffer_string m_name; // 0x0	
	int32_t m_nType; // 0x10	
};

class CAnimDataChannelDesc
{
public:
	c_buffer_string m_szChannelClass; // 0x0	
	c_buffer_string m_szVariableName; // 0x10	
	int32_t m_nFlags; // 0x20	
	int32_t m_nType; // 0x24	
	c_buffer_string m_szGrouping; // 0x28	ru-chat
	c_buffer_string m_szDescription; // 0x38	
	c_utl_vector< c_buffer_string > m_szElementNameArray; // 0x48	
	c_utl_vector< int32_t > m_nElementIndexArray; // 0x60	
	c_utl_vector< uint32_t > m_nElementMaskArray; // 0x78	
};

class CAnimKeyData
{
public:
	c_buffer_string m_name; // 0x0	
	c_utl_vector< CAnimBone > m_boneArray; // 0x10	
	c_utl_vector< CAnimUser > m_userArray; // 0x28	
	c_utl_vector< c_buffer_string > m_morphArray; // 0x40	
	int32_t m_nChannelElements; // 0x58	
private:
	[[maybe_unused]] uint8_t __pad005c[0x4]; // 0x5c
public:
	c_utl_vector< CAnimDataChannelDesc > m_dataChannelArray; // 0x60	
};

class CAnimationGroup
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x10]; // 0x0
public:
	uint32_t m_nFlags; // 0x10	
private:
	[[maybe_unused]] uint8_t __pad0014[0x4]; // 0x14
public:
	c_buffer_string m_name; // 0x18	
private:
	[[maybe_unused]] uint8_t __pad0028[0x38]; // 0x28
public:
	// MKV3TransferName "m_localHAnimArray"
	c_utl_vector< strong_handle< CAnimData > > m_localHAnimArray_Handle; // 0x60	
	// MKV3TransferName "m_includedGroupArray"
	c_utl_vector< strong_handle< CAnimationGroup > > m_includedGroupArray_Handle; // 0x78	
	// MKV3TransferName "m_directHSeqGroup"
	c_utl_vector<strong_handle< CSequenceGroupData >> m_directHSeqGroup_Handle; // 0x90	
	// -> m_name - 0x98
	// -> m_boneArray - 0xa8
	// -> m_userArray - 0xc0
	// -> m_morphArray - 0xd8
	// -> m_nChannelElements - 0xf0
	// -> m_dataChannelArray - 0xf8
	CAnimKeyData m_decodeKey; // 0x98	
	c_utl_vector< c_buffer_string > m_szScripts; // 0x110	
};

class CAnimationGroupResource
{
public: 
	char pad[0x10];
	CAnimationGroup* animation_group;
	const char* path_mdl;
};

class c_perm_model_data
{
public:
	c_utl_string m_name;
	c_perm_model_info m_modelInfo;
	c_utl_vector<c_perm_model_ext_part> m_ExtParts;
	c_utl_vector< c_rendermesh* >  m_refMeshes;
	char pad2[0x8];
	c_utl_vector< uint64_t > m_refMeshGroupMasks;
	char pad3[0x8];
	c_utl_vector< uint64_t > m_refPhysGroupMasks;
	char pad5[0x30];
	c_utl_vector< CAnimationGroupResource* > m_refAnimGroups; // 0x120	
	char pad9[0x70];
	ModelSkeletonData_t m_modelSkeleton; // 0x188	
};