#pragma once

#include "../../sdk/classes/user_cmd.hpp"
#include "../../sdk/interfaces/i_csgo_input.hpp"
#include "../../sdk/sdk.hpp"
#include "../../sdk/math/vector.hpp"

#include "../../sdk/math/math.hpp"

class c_antiaim
{
	enum e_manual
	{
		none,
		left,
		backward,
		right
	};
public:
	void run(c_user_cmd* cmd);
private:
	void pitch(c_user_cmd* cmd);
	void yaw(c_user_cmd* cmd);
public:
	float spinner_amount = 0.f;
	int manual = 0;
	vector antiaim_angle{};
	int jitter_side = -1;
};

inline auto g_antiaim = std::make_unique<c_antiaim>();