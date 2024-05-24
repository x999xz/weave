#pragma once

// c_cs_player_pawn.hpp
#define GET_BONE_POSITION "48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4D 8B F1"
#define WORLD_SPACE_CENTER "48 89 5C 24 08 57 48 83 EC 20 48 8B 01 48 8B FA 48 8B D9 FF 90 ?? ?? ?? ?? 48 8B CB 48"

// unk
#define CALC_ANIMATION_STATE "40 55 53 56 57 41 54 41 55 41 56 41 57 B8"
#define CALC_PARENT_SPACE_STATE "40 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 30 48 8D 6C 24 30"
#define CALC_WORLD_SPACE_BONES "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC D0"

// hooks.cpp
#define FRAME_STAGE_NOTIFY "48 89 5C 24 ? 56 48 83 EC ? 8B 05 ? ? ? ? 8D 5A" // xref: cl_change_callback_limit
#define LEVEL_INIT "48 89 5C 24 ? 57 48 83 EC ? 48 8B 0D ? ? ? ? 48 8B DA 45 33 C9" // xref: game_newmap
#define LEVEL_SHUTDOWN "E8 ?? ?? ?? ?? 48 8D 8F 48 02 00 00 33 F6" // xref: map_shutdown
#define SEND_MOVE "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 8D 55"
#define DRAWSCENEOBJECT "48 8B C4 48 89 58 08 44"
#define RUNCOMMAND "48 8B C4 48 81 EC D8 00 00 00 48 89 58 10 48 89" // xref: runcommand:%04d,tick:%u
#define CREATEMOVE "48 8B C4 44 88 48 20 4C 89 40 18 48 89 48" // xref: cl: CreateMove - Frame %d, cmd %d, attack start time indexes = [%d,%d,%d], %d history entries\n
#define STEAM_PRESENT "48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8"
#define STEAM_RESIZEBUFFERS "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 30 44 8B FA 48 8B F1"
#define START_LAGCOMPENSATION "48 89 5C 24 10 48 89 6C 24 18 56 57 41 55 41 56 41 57 48 81 EC C0"
#define START_LAGCOMPENSATION2 "48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 48 83 EC 60 48 8B 05"
#define EMIT_SOUND "48 8B C4 48 89 50 10 55 53 56 41"
#define RET_DRAW_ARRAY_EXECUTE "48 89 44 24 20 E8 ?? ?? ?? ?? 48 8B F8"
#define GET_MATERIAL_FOR_DRAW "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 49 8B 41"
#define SCOPE_PAINT "40 55 57 41 54 41 57 48 8D"
#define ON_RENDER_START "48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 70"
#define OVERRIDE_VIEW "48 89 5C 24 10 55 48 8D 6C 24 A9 48 81 EC B0 00 00 00 48 8B 01" // xref: c_thirdpersonshoulderoffset
#define INTERPOLATE_ENTITIES "40 56 48 83 EC 60 8B" // xref: C_BaseEntity::InterpolateEntities %.2fms\n
#define RUN_SIMULATION "48 8B C4 44 89 48 20 44" // xref: StorePredictionResults
#define INTERP_INTERPOLATION "4C 89 4C 24 20 48 89 4C 24 08 53 55 56 57 41 54 41 55 41 56 41 57 48 83" // хуйню клинтскую инреполяцию можно тут отключить
// она в принципе похожа на говно из кс го ну и говнище вы создали пидарасы но и так же можно найти как выключить экстраполяцию хорошо что я нашёл )) 
// отключить её можно хукнуть IsPause индекс 11 ретурн бахнуть можно только надо найти сигну в функции InterpolationEntities петухи ебанные
// xref: cl_interp_all

// c_base_player_weapon.hpp
#define GET_IN_ACCURACY "48 89 5C 24 08 57 48 81 EC 90 00 00 00 0F 29" // xref: weapon_air_spread_scale -> first function
#define GET_SPREAD "48 83 EC 38 48 63 91" // 
#define UPDATE_ACCURACY "48 89 5C 24 18 57 48 83 EC 60 48 8B F9 E8" // xref: weapon_air_spread_scale -> third function

// c_prediction.hpp
#define UPDATE "40 53 55 57 48 81 EC 80 00" // xref: CPrediction::Update

// i_trace.hpp
#define TRACE_SHAPE "48 89 54 24 10 48 89 4C 24 08 55 53 56 57 41 54 41 56 41 57 48 8D AC" // xref: Physics/TraceShape (Client)
#define POINT_CONTENTS "48 83 EC 38 F3 0F 10 15 ?? ?? ?? ?? 66" // xref: trace_to_exit
#define CLIP_RAY_TO_ENTITY "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 54 41 56 41 57 48 81 EC C0 00 00 00 48 8B 9C" // xref: clip_trace_to_players -> clip_ray_to_entity
#define CLIP_TRACE_TO_PLAYERS "48 8B C4 55 56 48 8D A8 58 FF" // xref: sv_clip_penetration_traces_to_players
#define GET_SURFACES_DATA "48 63 41 10 48 8B 0D"

// c_resource_system
#define ENUMERATE_MATERIAL "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 30 41 8B"

// game_scene_node
#define BUILD_BONE_MERGE_WORK "40 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 50 48 8D 6C 24 50"

// interfaces.cpp
#define CLIENT_MODE "4C 8D 35 ?? ?? ?? ?? 33 DB 48 8D 2D" // xref: autobuy.txt
#define CSGO_INPUT "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 8B DF"
#define ENTITY_LIST "48 8B 0D ? ? ? ? 48 8D 94 24 50 02 00 00 33 DB" // xref: Ent %3d: %s class %s name %s\n
#define GLOBAL_VARS "48 8B 05 ?? ?? ?? ?? 0F 57 FF F3 0F 10 48 44 0F 2E CF" // xref: %s:  %f tick(%d) curtime(%f) OnNetworkCycleReset set cycle 0.0f\n
#define RENDERER "66 0F 7F 05 ? ? ? ? 66 0F 7F 0D ? ? ? ? 48 89 35"
#define TRACE_MANAGER "48 8B 05 ? ? ? ? 80 A4 24"
#define GAME_EVENT_MANAGER "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 01" // xref: g_GameEventManager.Init()
#define ECON_ITEM_SYSTEM "48 83 EC 28 E8 ?? ?? ?? ?? 48 8B 40 08"

//econ_item_view.hpp
#define LOCALIZE_NAME "48 89 5C 24 10 48 89 6C 24 18 48 89 7C 24 20 41 56 48 83 EC 40 48 83" // xref: %s | %s

//movement.hpp
#define TRY_PLAYER_MOVE "48 8B C4 4C 89 48 20 4C 89 40 18 48 89 50 10 55 53 41 55 48" // xref: CCSPlayer_MovementServices::TryPlayerMove() Trace ended stuck

#define SET_LOCAL_ORIGIN "48 89 5C 24 08 57 48 83 EC 40 48 8B 01 48 8B FA 48"
#define RENDER_GAME_SYSTEM "48 8B 0D ?? ?? ?? ?? 48 8D 5E 10 48 89 44 24 28"
#define CAMERA_SERVICE_GET_FOV "40 53 48 83 EC 50 48 8B D9 E8 ?? ?? ?? ?? 48" // xref: fov_cs_debug
#define ADD_PARTICLE "48 83 EC 58 F3 41 0F 10 51"
#define ADD_EFFECT "40 57 48 83 EC 20 49 8B"