#pragma once

#include <cstdint>
#include "../../utilities/utilities.hpp"
#include "../../sdk/classes/game_event_listener.hpp"

class c_event : public i_game_event_listener
{
public:
	void fire_game_event(c_game_event* event);
	void initilization();
	void player_hurt(c_game_event* event);
	void player_harmed(c_game_event* event);
	void player_death(c_game_event* event);
	void bullet_impact(c_game_event* event);
};

inline auto g_event = std::make_unique<c_event>();