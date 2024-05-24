#pragma once

#include "../../sdk/sdk.hpp"
#include "../../renderer/render_manager.h"
#include "../../gui/helper/animation.h"

struct hitmarker_log
{
	hitmarker_log(vector position, float time) : position(position), is_world_screen{}, world_position {}, time(time), animation() {}
	vector position;
	bool is_world_screen;
	vector world_position;
	float time;
	c_animation animation;
};

class c_hitmarker
{
public:
	void run();
	void update_world_screen();
	void add(vector position);
private:
	std::vector<hitmarker_log> logs;
	std::mutex mutex;
};

inline auto g_hitmarker = std::make_unique<c_hitmarker>();