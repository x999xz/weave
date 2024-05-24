// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#include "../../sdk/sdk.hpp"
#include "../../sdk/math/vector.hpp"
#include "../../sdk/math/math.hpp"
#include <deque>
#include <mutex>
#include "../../gui/helper/animation.h"

class c_specs
{
public:
	std::string name;
	std::uint64_t steam_id;
	bool m_show;
	c_animation m_animation;
	int texture_id;
};

class c_active_binds
{
public:
	std::uint64_t hash;
	std::string name;
	std::string value;
	int key;
	int mode;
	bool enabled;
	c_animation animation;
};

class c_notify
{
public:
	std::string title;
	std::string decription;
	float time_to_de;
	c_animation animation;
};

class c_misc
{
public:
	void on_post();
	void bullet_impact();
	void watermark();
	void add_bullet_trace(vector start, vector end, color_t clr);
	void add_grenade_trail(vector* points, int size, float time = 0.5f);
	void grenade_prediction();
	void buybot();
	void penetration_crosshair();
private:
	int last_count_bullet = 0;
public:
	std::unordered_map<std::uint64_t, int> m_avatars_cache_;
	std::vector<c_specs> specs_;
public:
	int setup_avatar(c_cs_player_pawn* player_pawn);
public:
	void spectators();
	void keybinds();
	void notify();
	void add_notify(std::string title, std::string decription, float time_to_de)
	{
		auto& notify = m_notify.emplace_back();
		notify.title = title;
		notify.decription = decription;
		notify.time_to_de = time_to_de;
	}
public:
	std::mutex grenade_prediction_m;
	std::unordered_map<std::uint64_t, float> grenades_trail;
	std::deque<vector> lines;
	std::vector< c_active_binds> m_active_binds;
	vector direction_grenade[2];
	std::vector< c_notify> m_notify;
};

inline auto g_misc = std::make_unique<c_misc>();