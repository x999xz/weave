#pragma once

#include "../sdk.hpp"

class c_cs_player_pawn;

class c_csgo_player_anim_graph_state
{
public:
	char pad[0x8];
	c_cs_player_pawn* m_entity; // 0x8
	char pad2[0x84]; // 0x10
	float last_update_increment; // 0x94
	float last_update_time; // 0x98
	char pad3[0x3C];
	float eye_yaw;
	float foot_yaw;
};