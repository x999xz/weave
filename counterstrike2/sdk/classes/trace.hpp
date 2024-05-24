#pragma once

#include <cstdint>

#include "../math/vector.hpp"

class c_cs_player_pawn;
class c_hitbox;

class c_ray
{
public:
	vector start;
	vector end;
	vector mins;
	vector maxs;
	std::uint32_t N000002C7;
	std::uint8_t N000002BE;
};
static_assert(sizeof(c_ray) == 0x38);

class c_trace_filter
{
public:
	std::uintptr_t* ptr; // 0x0
	std::uint64_t trace_mask; // 0x8
	std::uint64_t unk1;
	std::uint64_t unk2;
	int skip_handle1; // 0x20
	int skip_handle2; // 0x24
	int skip_owner_handle1;
	int skip_owner_handle2;
	std::uint16_t collision1; // 0x30
	std::uint16_t collision2; // 0x32
	std::uint16_t N0000011C; // 0x34
	std::uint8_t layer; // 0x36
	std::uint8_t flags; // 0x37
	std::uint8_t null_it3; // 0x38
	c_trace_filter(std::uint64_t trace_mask, c_cs_player_pawn* local_player, c_cs_player_pawn* entity, std::uint8_t layer);
};

static_assert(sizeof(c_trace_filter) == 0x40);

class c_surfaces_data
{
public:
	char pad00[8];
	float penetration_modifier;
	float damage_modifier;
	char pad01[4];
	int material;
};

class c_game_trace
{
public:
	void* surfaces; // 0x0
	c_cs_player_pawn* entity; // 0x8
	c_hitbox* trace_model; // 0x10
	char penis4[0x10]; //0x18
	int contents; // 0x28
	char penis3[0x24];
	int flags;
	char penis2[0x24];
	vector start_pos;
	vector end_pos;
	vector normal;
	char penis[16];
	float fraction;
	char unk[7];
	bool start_solid;
public:
	bool DidHit()
	{
		return this->fraction < 0.95 || this->start_solid;
	}
	c_surfaces_data* get_surfaces_data();
};
static_assert(sizeof(c_game_trace) == 0xB8);