#pragma once

#include "../sdk/sdk.hpp"

class c_grenade_prediction_ {
public:
	std::pair<vector, vector> throw_grenade(c_base_cs_grenade* grenade, vector angle);
	void physics_push_entity(vector push);
private:
	vector m_origin;
	c_cs_player_pawn* m_owner;
};