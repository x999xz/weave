#pragma once

#include "../sdk.hpp"

struct VPhysXCollisionAttributes_t
{
public:
	uint32_t m_CollisionGroup; // 0x0	
	c_utl_vector< uint32 > m_InteractAs; // 0x8	
	c_utl_vector< uint32 > m_InteractWith; // 0x20	
	c_utl_vector< uint32 > m_InteractExclude; // 0x38	
	c_utl_string m_CollisionGroupString; // 0x50	
	c_utl_vector< c_utl_string > m_InteractAsStrings; // 0x58	
	c_utl_vector< c_utl_string > m_InteractWithStrings; // 0x70	
	c_utl_vector< c_utl_string > m_InteractExcludeStrings; // 0x88	
};

struct RnShapeDesc_t
{
public:
	uint32_t m_nCollisionAttributeIndex; // 0x0	
	uint32_t m_nSurfacePropertyIndex; // 0x4	
	c_utl_string m_UserFriendlyName; // 0x8	
};

// Registered binary: vphysics2.dll (project 'physicslib')
// Alignment: 8
// Size: 0x20
// 
// MGetKV3ClassDefaults
struct RnSphereDesc_t : public RnShapeDesc_t
{
public:
	char pad[0x10];//SphereBase_t< float > m_Sphere; // 0x10	
};

struct RnCapsule_t
{
public:
	vector m_vCenter[2]; // 0x0	
	float m_flRadius; // 0x18	
};

struct RnCapsuleDesc_t : public RnShapeDesc_t
{
public:
	// -> m_vCenter[2] - 0x10
	// -> m_flRadius - 0x28
	RnCapsule_t m_Capsule; // 0x10	
};

struct AABB_t
{
public:
	vector m_vMinBounds;
	vector m_vMaxBounds;
};

class CRegionSVM
{
public:
	c_utl_vector< c_rn_plane > m_Planes; // 0x0	
	c_utl_vector< uint32 > m_Nodes; // 0x18	
};

struct RnFace_t
{
public:
	uint8_t m_nEdge; // 0x0	
};

struct RnHalfEdge_t
{
public:
	uint8_t m_nNext; // 0x0	
	uint8_t m_nTwin; // 0x1	
	uint8_t m_nOrigin; // 0x2	
	uint8_t m_nFace; // 0x3	
};

struct RnVertex_t
{
public:
	uint8_t m_nEdge; // 0x0	
};

class RnHull_t
{
public:
	vector m_vCentroid; // 0x0	
	float m_flMaxAngularRadius; // 0xc	
	AABB_t m_Bounds; // 0x10	
	vector m_vOrthographicAreas; // 0x28	
	char m_MassProperties[48]; //matrix3x4_t m_MassProperties; // 0x34	
	float m_flVolume; // 0x64	
	float m_flSurfaceArea; // 0x68	
private:
	[[maybe_unused]] uint8_t __pad006c[0x4]; // 0x6c
public:
	c_utl_vector< RnVertex_t > m_Vertices; // 0x70	
	c_utl_vector< vector > m_VertexPositions; // 0x88	
	c_utl_vector< RnHalfEdge_t > m_Edges; // 0xa0	
	c_utl_vector< RnFace_t > m_Faces; // 0xb8	
	c_utl_vector< c_rn_plane > m_FacePlanes; // 0xd0	
	uint32_t m_nFlags; // 0xe8	
private:
	[[maybe_unused]] uint8_t __pad00ec[0x4]; // 0xec
public:
	CRegionSVM* m_pRegionSVM; // 0xf0	
};

struct RnHullDesc_t : public RnShapeDesc_t
{
public:
	RnHull_t m_Hull; // 0x10	
};

struct RnNode_t
{
public:
	vector m_vMin; // 0x0	
	uint32_t m_nChildren; // 0xc	
	vector m_vMax; // 0x10	
	uint32_t m_nTriangleOffset; // 0x1c	
};

struct RnTriangle_t
{
public:
	int32_t m_nIndex[3]; // 0x0	
};

struct RnWing_t
{
public:
	int32_t m_nIndex[3]; // 0x0	
};

struct RnMesh_t
{
public:
	vector m_vMin; // 0x0	
	vector m_vMax; // 0xc	
	c_utl_vector< RnNode_t > m_Nodes; // 0x18	
	char pad[0x18];//CUtlVectorSIMDPaddedVector m_Vertices; // 0x30	
	c_utl_vector< RnTriangle_t > m_Triangles; // 0x48	
	c_utl_vector< RnWing_t > m_Wings; // 0x60	
	c_utl_vector< uint8_t > m_Materials; // 0x78	
	vector m_vOrthographicAreas; // 0x90	
	uint32_t m_nFlags; // 0x9c	
	uint32_t m_nDebugFlags; // 0xa0	
};

struct RnMeshDesc_t : public RnShapeDesc_t
{
public:
	// -> m_vMin - 0x10
	// -> m_vMax - 0x1c
	// -> m_Nodes - 0x28
	// -> m_Vertices - 0x40
	// -> m_Triangles - 0x58
	// -> m_Wings - 0x70
	// -> m_Materials - 0x88
	// -> m_vOrthographicAreas - 0xa0
	// -> m_nFlags - 0xac
	// -> m_nDebugFlags - 0xb0
	RnMesh_t m_Mesh; // 0x10	
};

struct VPhysics2ShapeDef_t
{
public:
	c_utl_vector< RnSphereDesc_t > m_spheres; // 0x0	
	c_utl_vector< RnCapsuleDesc_t > m_capsules; // 0x18	
	c_utl_vector< RnHullDesc_t > m_hulls; // 0x30	
	c_utl_vector< RnMeshDesc_t > m_meshes; // 0x48	
	c_utl_vector< uint16_t > m_CollisionAttributeIndices; // 0x60	
};

class VPhysXBodyPart_t
{
public:
	uint32_t m_nFlags; // 0x0	
	float m_flMass; // 0x4	
	// -> m_spheres - 0x8
	// -> m_capsules - 0x20
	// -> m_hulls - 0x38
	// -> m_meshes - 0x50
	// -> m_CollisionAttributeIndices - 0x68
	VPhysics2ShapeDef_t m_rnShape; // 0x8	
	uint16_t m_nCollisionAttributeIndex; // 0x80	
	uint16_t m_nReserved; // 0x82	
	float m_flInertiaScale; // 0x84	
	float m_flLinearDamping; // 0x88	
	float m_flAngularDamping; // 0x8c	
	bool m_bOverrideMassCenter; // 0x90	
private:
	[[maybe_unused]] uint8_t __pad0091[0x3]; // 0x91
public:
	vector m_vMassCenterOverride; // 0x94	
};

struct VPhysXConstraintParams_t
{
public:
	int8_t m_nType; // 0x0	
	int8_t m_nTranslateMotion; // 0x1	
	int8_t m_nRotateMotion; // 0x2	
	int8_t m_nFlags; // 0x3	
	vector m_anchor[2]; // 0x4	
	c_quaternion_storage m_axes[2]; // 0x1c	
	float m_maxForce; // 0x3c	
	float m_maxTorque; // 0x40	
	float m_linearLimitValue; // 0x44	
	float m_linearLimitRestitution; // 0x48	
	float m_linearLimitSpring; // 0x4c	
	float m_linearLimitDamping; // 0x50	
	float m_twistLowLimitValue; // 0x54	
	float m_twistLowLimitRestitution; // 0x58	
	float m_twistLowLimitSpring; // 0x5c	
	float m_twistLowLimitDamping; // 0x60	
	float m_twistHighLimitValue; // 0x64	
	float m_twistHighLimitRestitution; // 0x68	
	float m_twistHighLimitSpring; // 0x6c	
	float m_twistHighLimitDamping; // 0x70	
	float m_swing1LimitValue; // 0x74	
	float m_swing1LimitRestitution; // 0x78	
	float m_swing1LimitSpring; // 0x7c	
	float m_swing1LimitDamping; // 0x80	
	float m_swing2LimitValue; // 0x84	
	float m_swing2LimitRestitution; // 0x88	
	float m_swing2LimitSpring; // 0x8c	
	float m_swing2LimitDamping; // 0x90	
	vector m_goalPosition; // 0x94	
	c_quaternion_storage m_goalOrientation; // 0xa0	
	vector m_goalAngularVelocity; // 0xb0	
	float m_driveSpringX; // 0xbc	
	float m_driveSpringY; // 0xc0	
	float m_driveSpringZ; // 0xc4	
	float m_driveDampingX; // 0xc8	
	float m_driveDampingY; // 0xcc	
	float m_driveDampingZ; // 0xd0	
	float m_driveSpringTwist; // 0xd4	
	float m_driveSpringSwing; // 0xd8	
	float m_driveSpringSlerp; // 0xdc	
	float m_driveDampingTwist; // 0xe0	
	float m_driveDampingSwing; // 0xe4	
	float m_driveDampingSlerp; // 0xe8	
	int32_t m_solverIterationCount; // 0xec	
	float m_projectionLinearTolerance; // 0xf0	
	float m_projectionAngularTolerance; // 0xf4	
};

struct VPhysXRange_t
{
public:
	float m_flMin; // 0x0	
	float m_flMax; // 0x4	
};

struct VPhysXConstraint2_t
{
public:
	uint32_t m_nFlags; // 0x0	
	uint16_t m_nParent; // 0x4	
	uint16_t m_nChild; // 0x6	
	VPhysXConstraintParams_t m_params; // 0x8	
};

struct VPhysXJoint_t
{
public:
	uint16_t m_nType; // 0x0	
	uint16_t m_nBody1; // 0x2	
	uint16_t m_nBody2; // 0x4	
	uint16_t m_nFlags; // 0x6	
private:
	[[maybe_unused]] uint8_t __pad0008[0x8]; // 0x8
public:
	c_transform m_Frame1; // 0x10	
	c_transform m_Frame2; // 0x30	
	bool m_bEnableCollision; // 0x50	
	bool m_bEnableLinearLimit; // 0x51	
private:
	[[maybe_unused]] uint8_t __pad0052[0x2]; // 0x52
public:
	VPhysXRange_t m_LinearLimit; // 0x54	
	bool m_bEnableLinearMotor; // 0x5c	
private:
	[[maybe_unused]] uint8_t __pad005d[0x3]; // 0x5d
public:
	vector m_vLinearTargetVelocity; // 0x60	
	float m_flMaxForce; // 0x6c	
	bool m_bEnableSwingLimit; // 0x70	
private:
	[[maybe_unused]] uint8_t __pad0071[0x3]; // 0x71
public:
	VPhysXRange_t m_SwingLimit; // 0x74	
	bool m_bEnableTwistLimit; // 0x7c	
private:
	[[maybe_unused]] uint8_t __pad007d[0x3]; // 0x7d
public:
	VPhysXRange_t m_TwistLimit; // 0x80	
	bool m_bEnableAngularMotor; // 0x88	
private:
	[[maybe_unused]] uint8_t __pad0089[0x3]; // 0x89
public:
	vector m_vAngularTargetVelocity; // 0x8c	
	float m_flMaxTorque; // 0x98	
	float m_flLinearFrequency; // 0x9c	
	float m_flLinearDampingRatio; // 0xa0	
	float m_flAngularFrequency; // 0xa4	
	float m_flAngularDampingRatio; // 0xa8	
	float m_flFriction; // 0xac	
};

class c_physmodel
{
public:
	uint16_t m_nFlags; // 0x0	
	uint16_t m_nRefCounter; // 0x2	
private:
	[[maybe_unused]] uint8_t __pad0004[0x4]; // 0x4
public:
	c_utl_vector<std::uint32_t> m_bonesHash;
	c_utl_vector<c_utl_string> m_boneName;
	c_utl_vector< uint16_t > m_indexNames; // 0x38	
	c_utl_vector< uint16_t > m_indexHash; // 0x50	
	c_utl_vector< matrix3x4_t > m_bindPose; // 0x68	
	c_utl_vector< VPhysXBodyPart_t > m_parts; // 0x80	
	c_utl_vector< VPhysXConstraint2_t > m_constraints2; // 0x98	
	c_utl_vector< VPhysXJoint_t > m_joints; // 0xb0	
	c_phys_fe_model_desc* m_pFeModel; // 0xc8	
	c_utl_vector< uint16_t > m_boneParents; // 0xd0	
	c_utl_vector< uint32_t > m_surfacePropertyHashes; // 0xe8	
	c_utl_vector< VPhysXCollisionAttributes_t > m_collisionAttributes; // 0x100	
	c_utl_vector< c_utl_string > m_debugPartNames; // 0x118	
	c_utl_string m_embeddedKeyvalues; // 0x130	
};