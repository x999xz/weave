#pragma once

#include "../classes/trace.hpp"
#include "../../utilities/utilities.hpp"
#include "../math/vector.hpp"
#include "../../signatures.hpp"

class i_trace
{
public:
	bool trace_shape(c_ray* ray, const vector& start, const vector& end, c_trace_filter* filter, c_game_trace* trace);
	int point_contents(const vector& end, int mask, __int16 mask2);
	bool clip_ray_to_entity(c_ray* ray, const vector& start, const vector& end, c_cs_player_pawn* player, c_trace_filter* filter, c_game_trace* trace);
};