#pragma once

#include "../sdk.hpp"

class c_phys_fe_model_desc
{
public:
	c_utl_vector< uint32_t > m_CtrlHash; // 0x0	
	c_utl_vector< c_utl_string > m_CtrlName; // 0x18	
	uint32_t m_nStaticNodeFlags; // 0x30	
	uint32_t m_nDynamicNodeFlags; // 0x34	
	float m_flLocalForce; // 0x38	
	float m_flLocalRotation; // 0x3c	
	uint16_t m_nNodeCount; // 0x40	
	uint16_t m_nStaticNodes; // 0x42	
	uint16_t m_nRotLockStaticNodes; // 0x44	
	uint16_t m_nFirstPositionDrivenNode; // 0x46	
	uint16_t m_nSimdTriCount1; // 0x48	
	uint16_t m_nSimdTriCount2; // 0x4a	
	uint16_t m_nSimdQuadCount1; // 0x4c	
	uint16_t m_nSimdQuadCount2; // 0x4e	
	uint16_t m_nQuadCount1; // 0x50	
	uint16_t m_nQuadCount2; // 0x52	
	uint16_t m_nTreeDepth; // 0x54	
	uint16_t m_nNodeBaseJiggleboneDependsCount; // 0x56	
	uint16_t m_nRopeCount; // 0x58	
private:
	[[maybe_unused]] uint8_t __pad005a[0x6]; // 0x5a
public:
	c_utl_vector< uint16_t > m_Ropes; // 0x60	
	c_utl_vector< c_fe_node_base > m_NodeBases; // 0x78	
	c_utl_vector< c_fe_simd_node_base > m_SimdNodeBases; // 0x90	
	c_utl_vector< c_fe_quad > m_Quads; // 0xa8	
	c_utl_vector< c_fe_simd_quad > m_SimdQuads; // 0xc0	
	c_utl_vector< c_fe_simd_tri > m_SimdTris; // 0xd8	
	c_utl_vector< c_fe_simd_rod_constraint > m_SimdRods; // 0xf0	
	c_utl_vector< c_fe_simd_rod_constraint_anim > m_SimdRodsAnim; // 0x108	
	c_utl_vector< c_transform > m_InitPose; // 0x120	
	c_utl_vector< c_fe_rod_constraint > m_Rods; // 0x138	
	c_utl_vector< c_fe_twist_constraint > m_Twists; // 0x150	
	c_utl_vector< c_fe_axial_edge_bend > m_AxialEdges; // 0x168	
	c_utl_vector< float > m_NodeInvMasses; // 0x180	
	c_utl_vector< c_fe_ctrl_offset > m_CtrlOffsets; // 0x198	
	c_utl_vector< c_fe_ctrl_os_offset > m_CtrlOsOffsets; // 0x1b0	
	c_utl_vector< c_fe_follow_node > m_FollowNodes; // 0x1c8	
	c_utl_vector< c_fe_collision_plane > m_CollisionPlanes; // 0x1e0	
	c_utl_vector< c_fe_node_integrator > m_NodeIntegrator; // 0x1f8	
	c_utl_vector< c_fe_simd_spring_integrator > m_SpringIntegrator; // 0x210	
	c_utl_vector< c_fe_simd_spring_integrator > m_SimdSpringIntegrator; // 0x228	
	c_utl_vector< c_fe_world_collision_params > m_WorldCollisionParams; // 0x240	
	c_utl_vector< float > m_LegacyStretchForce; // 0x258	
	c_utl_vector< float > m_NodeCollisionRadii; // 0x270	
	c_utl_vector< float > m_DynNodeFriction; // 0x288	
	c_utl_vector< float > m_LocalRotation; // 0x2a0	
	c_utl_vector< float > m_LocalForce; // 0x2b8	
	c_utl_vector< c_fe_tapered_capsule_stretch > m_TaperedCapsuleStretches; // 0x2d0	
	c_utl_vector< c_fe_tapered_capsule_rigid > m_TaperedCapsuleRigids; // 0x2e8	
	c_utl_vector< c_fe_sphere_rigid > m_SphereRigids; // 0x300	
	c_utl_vector< uint16_t > m_WorldCollisionNodes; // 0x318	
	c_utl_vector< uint16_t > m_TreeParents; // 0x330	
	c_utl_vector< uint16_t > m_TreeCollisionMasks; // 0x348	
	c_utl_vector< c_fe_tree_children > m_TreeChildren; // 0x360	
	c_utl_vector< uint16_t > m_FreeNodes; // 0x378	
	c_utl_vector< c_fe_fit_matrix > m_FitMatrices; // 0x390	
	c_utl_vector< c_fe_fit_weight > m_FitWeights; // 0x3a8	
	c_utl_vector< c_fe_node_reverse_offset > m_ReverseOffsets; // 0x3c0	
	c_utl_vector< c_fe_anim_stray_radius > m_AnimStrayRadii; // 0x3d8	
	c_utl_vector< c_fe_simd_anim_stray_radius > m_SimdAnimStrayRadii; // 0x3f0	
	c_utl_vector< c_fe_kelager_bend2 > m_KelagerBends; // 0x408	
	c_utl_vector< c_fe_ctrl_soft_offset > m_CtrlSoftOffsets; // 0x420	
	c_utl_vector< c_fe_indexed_jiggle_bone > m_JiggleBones; // 0x438	
	c_utl_vector< uint16_t > m_SourceElems; // 0x450	
	c_utl_vector< uint32_t > m_GoalDampedSpringIntegrators; // 0x468	
	c_utl_vector< c_fe_tri > m_Tris; // 0x480	
	uint16_t m_nTriCount1; // 0x498	
	uint16_t m_nTriCount2; // 0x49a	
	uint8_t m_nReservedUint8; // 0x49c	
	uint8_t m_nExtraPressureIterations; // 0x49d	
	uint8_t m_nExtraGoalIterations; // 0x49e	
	uint8_t m_nExtraIterations; // 0x49f	
	c_utl_vector< c_fe_box_rigit > m_BoxRigids; // 0x4a0	
	c_utl_vector< uint8_t > m_DynNodeVertexSet; // 0x4b8	
	c_utl_vector< uint32_t > m_VertexSetNames; // 0x4d0	
	c_utl_vector< c_fe_rigid_collider_indices > m_RigidColliderPriorities; // 0x4e8	
	c_utl_vector< c_fe_morph_layer_depr > m_MorphLayers; // 0x500	
	c_utl_vector< uint8_t > m_MorphSetData; // 0x518	
	c_utl_vector< c_fe_vertex_map_desc > m_VertexMaps; // 0x530	
	c_utl_vector< uint8_t > m_VertexMapValues; // 0x548	
	c_utl_vector< c_fe_effect_desc > m_Effects; // 0x560	
	c_utl_vector< c_fe_ctrl_offset > m_LockToParent; // 0x578	
	c_utl_vector< uint16_t > m_LockToGoal; // 0x590	
	c_utl_vector< int16_t > m_SkelParents; // 0x5a8	
	c_utl_vector< c_fe_node_wind_base > m_DynNodeWindBases; // 0x5c0	
	float m_flInternalPressure; // 0x5d8	
	float m_flDefaultTimeDilation; // 0x5dc	
	float m_flWindage; // 0x5e0	
	float m_flWindDrag; // 0x5e4	
	float m_flDefaultSurfaceStretch; // 0x5e8	
	float m_flDefaultThreadStretch; // 0x5ec	
	float m_flDefaultGravityScale; // 0x5f0	
	float m_flDefaultVelAirDrag; // 0x5f4	
	float m_flDefaultExpAirDrag; // 0x5f8	
	float m_flDefaultVelQuadAirDrag; // 0x5fc	
	float m_flDefaultExpQuadAirDrag; // 0x600	
	float m_flRodVelocitySmoothRate; // 0x604	
	float m_flQuadVelocitySmoothRate; // 0x608	
	float m_flAddWorldCollisionRadius; // 0x60c	
	float m_flDefaultVolumetricSolveAmount; // 0x610	
	uint16_t m_nRodVelocitySmoothIterations; // 0x614	
	uint16_t m_nQuadVelocitySmoothIterations; // 0x616	
};