#pragma once

#include "../sdk.hpp"
#include "../interfaces/virtual.hpp"

struct scene_hitbox
{
	c_hitbox* hitbox;
	char pad[0x8];
};

struct scene_hitbox_data
{
	std::uint64_t hitbox_count{};
	void* hitbox_data{};
	char pad[0x8];
	scene_hitbox hitbox_array[19]{};
};

struct hitbox_position
{
	vector position{};
	float scale{};
	vector_4d rotate{};
};

struct scene_hitbox_position
{
	std::uint64_t hitbox_count{};
	char pad[0x8]{};
	void* hitbox_data{};
	char pad2[0x8];
	hitbox_position hitbox_array[19]{};
};


class c_scene_view_debug_overlays
{
public:
	bool get_lock()
	{
		return CALL_VIRTUAL(bool, 11, this);
	}

	void set_lock(bool value)
	{
		CALL_VIRTUAL(void, 10, this, value);
	}
};