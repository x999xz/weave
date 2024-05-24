#pragma once

#include "../sdk.hpp"

class c_shoot_position_history_entry_t {
public:
	int tick;
	vector position;
	float unk;
	float speed;
	float unk2;
};

class c_shoot_position_history_data {
public:
	void* vtable;
	std::array<c_shoot_position_history_entry_t, 32> entries;
};