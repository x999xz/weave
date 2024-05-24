// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "math.hpp"

bool math::screen_transform(vector world_position, vector& screen_position)
{
	screen_position.x = g_cs2->world_screen[1] * world_position.y + g_cs2->world_screen[0] * world_position.x + g_cs2->world_screen[2] * world_position.z + g_cs2->world_screen[3];
	screen_position.y = g_cs2->world_screen[4] * world_position.x + g_cs2->world_screen[5] * world_position.y + g_cs2->world_screen[6] * world_position.z + g_cs2->world_screen[7];
	screen_position.z = 0.0;

	auto v9 = g_cs2->world_screen[12] * world_position.x + g_cs2->world_screen[13] * world_position.y;
	auto v10 = g_cs2->world_screen[14] * world_position.z + g_cs2->world_screen[15];

	auto v12 = v9 + v10;
	if (v12 < 0.001)
		return true;

	screen_position.x *= 1.0 / v12;
	screen_position.y *= 1.0 / v12;
	return false;
}

bool math::world_to_screen(vector& origin, vector& screen)
{
	vector out = { };
	if (screen_transform(origin, out))
		return false;

	screen.x = (1.0f + out.x) * static_cast<float>(g_cs2->screen.x * 0.5);
	screen.y = (1.0f - out.y) * static_cast<float>(g_cs2->screen.y * 0.5);

	return true;
}