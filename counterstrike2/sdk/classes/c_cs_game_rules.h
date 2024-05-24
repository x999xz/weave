#pragma once

#include "../interfaces/virtual.hpp"

class vector;

class c_view_vectors
{
public:
	vector vec_view; //0x0000
	vector hull_min; //0x000C
	vector hull_max; //0x0018
	vector duck_hull_min; //0x0024
	vector duck_hull_max; //0x0030
	vector duck_view; //0x003C
	vector obs_hull_min; //0x0048
	vector obs_hull_max; //0x0054
	vector dead_view; //0x0060
}; //Size: 0x006C

class c_cs_game_rules
{
public:
	char pad[0x30];
	bool freeze_pause;
	char pad2[0xB];
	int pause;
	char pad3[0x38];
	int game_phase;
public:
	c_view_vectors* get_view_vectors()
	{
		return CALL_VIRTUAL(c_view_vectors*, 38, this);
	}
};