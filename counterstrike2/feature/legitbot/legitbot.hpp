#pragma once

#include "../../sdk/classes/user_cmd.hpp"
#include "../../sdk/interfaces/i_csgo_input.hpp"
#include "../../sdk/sdk.hpp"
#include "../../sdk/math/vector.hpp"

#include "../../sdk/math/math.hpp"

struct legit_target
{
	bool visible;

	int hitbox;
	int hitgroup;

	float field_of_view;
	vector point;
	c_cs_player_pawn* player = nullptr;
	bool psilent; 
	legit_target()
	{
		reset(); //-V1053
	}
	operator bool() const {
		return player != nullptr;
	}
	void reset()
	{
		visible = true;

		hitbox = -1;
		hitgroup = -1;
		field_of_view = FLT_MAX;
		point = vector();
		player = nullptr;
		psilent = false;
	}
};


class c_legit_bot
{
public:
	void on_post(c_user_cmd* cmd);
	void recoil_control_system(c_user_cmd* cmd);
	bool can_see_player_position(c_cs_player_pawn* player, vector& position);
	vector get_aim_punch();
	vector get_prev_aim_punch();
	bool perform_checks();
	void get_hitbox_selection();
	bool scan(c_user_cmd* cmd, c_cs_player_pawn* force_player = nullptr);
	void fire(c_user_cmd* cmd, bool force_attack = false);
	void trigger(c_user_cmd* cmd);
	float get_smooth_value();
	vector m_last_point_render;
private:
	std::vector<std::uint32_t> m_hitboxes;
	vector m_old_aim_punch = vector();
	vector m_original_viewangles = vector();
	legit_target m_force_target;
	legit_target m_final_target;
};

inline auto g_legit_bot = std::make_unique<c_legit_bot>();