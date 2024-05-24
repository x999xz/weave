#pragma once

#include "../sdk.hpp"

enum e_hitgroups : std::uint32_t
{
	hitgroup_generic,
	hitgroup_head,
	hitgroup_chest,
	hitgroup_stomach,
	hitgroup_leftarm,
	hitgroup_rightarm,
	hitgroup_leftleg,
	hitgroup_rightleg,
	hitgroup_neck,
	hitgroup_gear = 10U
};

enum e_hitboxes : std::uint32_t
{
	/* head */
	hitbox_head,
	hitbox_neck,
	/* body */
	hitbox_pelvis,
	hitbox_stomach,
	hitbox_chest,
	hitbox_lower_chest,
	hitbox_upper_chest,
	/* legs */
	hitbox_right_thigh,
	hitbox_left_thigh,
	hitbox_right_calf,
	hitbox_left_calf,
	hitbox_right_foot,
	hitbox_left_foot,
	/* arms */
	hitbox_right_hand,
	hitbox_left_hand,
	hitbox_right_upper_arm,
	hitbox_right_forearm,
	hitbox_left_upper_arm,
	hitbox_left_forearm,
	hitbox_max
};

enum bone_flags : uint32_t {
	FLAG_NO_BONE_FLAGS = 0x0,
	FLAG_BONEFLEXDRIVER = 0x4,
	FLAG_CLOTH = 0x8,
	FLAG_PHYSICS = 0x10,
	FLAG_ATTACHMENT = 0x20,
	FLAG_ANIMATION = 0x40,
	FLAG_MESH = 0x80,
	FLAG_HITBOX = 0x100,
	FLAG_BONE_USED_BY_VERTEX_LOD0 = 0x400,
	FLAG_BONE_USED_BY_VERTEX_LOD1 = 0x800,
	FLAG_BONE_USED_BY_VERTEX_LOD2 = 0x1000,
	FLAG_BONE_USED_BY_VERTEX_LOD3 = 0x2000,
	FLAG_BONE_USED_BY_VERTEX_LOD4 = 0x4000,
	FLAG_BONE_USED_BY_VERTEX_LOD5 = 0x8000,
	FLAG_BONE_USED_BY_VERTEX_LOD6 = 0x10000,
	FLAG_BONE_USED_BY_VERTEX_LOD7 = 0x20000,
	FLAG_BONE_MERGE_READ = 0x40000,
	FLAG_BONE_MERGE_WRITE = 0x80000,
	FLAG_ALL_BONE_FLAGS = 0xfffff,
	BLEND_PREALIGNED = 0x100000,
	FLAG_RIGIDLENGTH = 0x200000,
	FLAG_PROCEDURAL = 0x400000,
};

enum e_weapon_type : std::uint32_t
{
	knife,
	pistols,
	smg,
	rifles,
	shot_gun,
	snipers,
	machine_gun,
	c4,
	taser,
	grenade,
	equipment,
	healthshot,
};

enum e_bone_flags : std::uint32_t
{
	flag_no_bone_flags = 0,
	flag_hitbox = 1,
	flag_bone_used_by_vertex_lod0 = 4,
	flag_bone_used_by_vertex_lod1 = 8,
	flag_bone_used_by_vertex_lod2 = 16,
	flag_bone_used_by_vertex_lod3 = 32,
	flag_bone_used_by_vertex_lod4 = 64,
	flag_bone_used_by_vertex_lod5 = 128,
	flag_bone_used_by_vertex_lod6 = 256,
	flag_bone_used_by_vertex_lod7 = 512,
	flag_bone_merge_read = 1024,
	flag_bone_merge_write = 2048,
	flag_all_bone_flags = 65535
};

enum e_signon_state : std::uint32_t
{
	signon_state_none,
	signon_state_challenge,
	signon_state_connected,
	signon_state_new,
	signon_state_prespawn,
	signon_state_spawn,
	signon_state_full,
	signon_state_changelevel
};

enum animation_processing_type : std::uint32_t
{
	animation_processing_server_simulation,
	animation_processing_client_simulation,
	animation_processing_client_prediction,
	animation_processing_client_interpolation,
	animation_processing_client_render,
	animation_processing_max
};

enum animation_snapshot_type : std::uint32_t
{
	animation_snapshot_server_simulation,
	animation_snapshot_client_simulation,
	animation_snapshot_client_prediction,
	animation_snapshot_client_interpolation,
	animation_snapshot_client_render,
	animation_snapshot_final_composite,
	animation_snapshot_max
};

enum e_weapon_item : std::uint32_t
{
	weapon_deagle = 1,
	weapon_dual_berettas = 2,
	weapon_five_seven = 3,
	weapon_glock = 4,
	weapon_ak47 = 7,
	weapon_aug = 8,
	weapon_awp = 9,
	weapon_famas = 10,
	weapon_g3sg1 = 11,
	weapon_galil = 13,
	weapon_m249 = 14,
	weapon_m4a4 = 16,
	weapon_mac10 = 17,
	weapon_p90 = 19,
	weapon_ump = 24,
	weapon_mp5sd = 23,
	weapon_xm1024 = 25,
	weapon_bizon = 26,
	weapon_mag7 = 27,
	weapon_negev = 28,
	weapon_sawedoff = 29,
	weapon_tec9 = 30,
	weapon_taser = 31,
	weapon_hkp2000 = 32,
	weapon_mp7 = 33,
	weapon_mp9 = 34,
	weapon_nova = 35,
	weapon_p250 = 36,
	weapon_scar20 = 38,
	weapon_sg553 = 39,
	weapon_ssg08 = 40,
	weapon_flashbang = 43,
	weapon_hegrenade = 44,
	weapon_smoke = 45,
	weapon_molotov = 46,
	weapon_decoy = 47,
	weapon_incdendiary = 48,
	weapon_healthshot = 57,
	weapon_m4a1_s = 60,
	weapon_usp_s = 61,
	weapon_cz75 = 63,
	weapon_revolver = 64,
	weapon_Bayonet = 500,
	weapon_KnifeCss = 503,
	weapon_KnifeFlip = 505,
	weapon_KnifeGut = 506,
	weapon_KnifeKarambit = 507,
	weapon_KnifeM9Bayonet = 508,
	weapon_KnifeTactical = 509,
	weapon_KnifeFalchion = 512,
	weapon_KnifeSurvivalBowie = 514,
	weapon_KnifeButterfly = 515,
	weapon_KnifePush = 516,
	weapon_KnifeCord = 517,
	weapon_KnifeCanis = 518,
	weapon_KnifeUrsus = 519,
	weapon_KnifeGypsyJackknife = 520,
	weapon_KnifeOutdoor = 521,
	weapon_KnifeStiletto = 522,
	weapon_KnifeWidowmaker = 523,
	weapon_KnifeSkeleton = 525
};

enum c_stages : std::uint32_t
{
	frame_handler_start = 0,
	frame_handler_end = 1,
	frame_prediction = 3,
	frame_net_full_frame_update_on_remove = 2,
	frame_net_update_start = 4,
	frame_net_update_postdataupdate_start = 5,
	frame_net_update_postdataupdate_end = 6,
	frame_net_update_end = 7,
	frame_start = 8,
	frame_render = 9
};

enum movetype_t : std::uint32_t
{
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip = 7,
	movetype_ladder = 9,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4
};

enum flags_t : std::uint32_t
{
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};