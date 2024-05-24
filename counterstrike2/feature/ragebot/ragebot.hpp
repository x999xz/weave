#pragma once

#include "../../sdk/classes/user_cmd.hpp"
#include "../../sdk/interfaces/i_csgo_input.hpp"
#include "../../sdk/sdk.hpp"
#include "../../sdk/math/vector.hpp"

#include "../../sdk/math/math.hpp"
#include "../../hooks/hooks.hpp"
#include "../../feature/lagcompensation/lagcompensation.hpp"

struct c_points
{
	vector m_vecPosition;
	bool m_bCenter;
};

class c_trace_data;

struct c_player_cache {
	c_handle handle = -1;
	c_cs_player_pawn* pawn = nullptr;
};

struct c_best_scan {
	vector point;
	float damage;
	int hitbox;
	c_lagrecord record;
	c_cs_player_pawn* player;
};

struct c_ragebot_config
{
	bool scope;
	int hitchance;
	bool no_spread;
	bool hide_shot;
	bool penetration;
	bool enabled;
	bool auto_fire;
	int damage;
	bool autostop;
	bool beetwen;
	bool accuracy;
	bool molotov;
	bool silent;
	bool m_head;
	bool m_chest;
	bool m_stomach;
	bool m_arms;
	bool m_legs;
	bool m_feet;
	bool m_head2;
	bool m_chest2;
	bool m_stomach2;
	bool m_arms2;
	bool m_legs2;
	bool m_feet2;
	float point_scale;
};

struct dropped_players {
	int tick;
	std::deque<c_player_cache> m_players;
};

class c_rage_bot
{
public:
	void on_post(c_user_cmd* cmd);
	bool can_shoot(int tick) const;
	bool auto_stop(c_user_cmd* cmd);
	float get_max_speed() const;
	void revolver_cock(c_user_cmd* cmd) const;
	bool multipoints(c_cs_player_pawn* pawn, c_bone_data* bones, int index, std::vector<c_points>& points, bool predicted);
	bool valid_interpolation_timing();
	void update_cache();
	void setup_config();
protected:
	void setup_hitboxes(c_cs_player_pawn* pawn);
	bool hitchance(vector& pos, c_bone_data* matrix, c_cs_player_pawn* player, int index);
	std::optional<c_best_scan> Scan(c_cs_player_pawn* player, bool predicted);
public:
	bool no_spread(c_user_cmd* cmd, vector& pos, c_cs_player_pawn* player, int index);
private:
	vector calculate_spread(unsigned int index, int bullets, float accuracy, float spread, unsigned short weapon_index, int recoil_index);
	void add_point(vector pos, bool center, std::vector<c_points>& point)
	{
		point.emplace_back(c_points(pos, center));
	}
private:
	c_ragebot_config m_config;
	std::vector<e_hitboxes> m_hitboxes;
public:
	vector best_target;
	c_cs_player_pawn* best_player;
	bool m_should_extapolation;
	vector best_point;
	bool set_next_angle = false;
	vector angle{};
	bool m_auto_stop = false;
	bool m_should_skip_tick = false;
	vector pred_position_;
	int next_cock_time;
	std::mutex m_mutex;
	std::deque< c_player_cache> m_players;
	std::deque< dropped_players> m_dropped_players;
	std::optional<c_player_cache> m_better_player;
};

class c_firebullet
{
public:
	bool fire_bullet(vector& start, vector& end, bool& visible, float& currentDamage, c_cs_player_pawn* player, int hitbox_index);
	void scale_damage(int hit_group, c_cs_player_pawn* player, c_weapon_cs_base_v_data* wpn_data, float& damage);
private:
	bool trace_to_exit(vector start, vector dir, vector& end, c_game_trace& enter_trace, c_game_trace& exit_trace, float step_size, float max_distance);
	bool handle_bullet_penetration(vector& start, vector& dir, vector& end, int& penetration_count, float penetration, float& current_damage, bool hit_grate, int enter_material, float penetration_modifier_enter, c_game_trace& trace);
	void clip_trace_to_players(vector start, vector end, float min, c_cs_player_pawn* player, c_trace_filter& filter, c_game_trace& trace);
	float get_hitgroup_damage_multiplier(c_cs_player_pawn* player, float head_shot_mult, int hit_group);
};

class c_firebullet_cs2
{
public:
	bool run(c_cs_player_pawn* entity, vector& start, vector& end, float& damage, int& hitbox);
	c_trace_data* trace_data = nullptr;
};

class c_fx_firebullet
{
public:
	bool run(c_cs_player_pawn* entity, vector& start, vector& end, float& damage, int& hitbox);
};

inline auto g_firebullet = std::make_unique<c_firebullet>();
inline auto g_firebullet_cs2 = std::make_unique<c_firebullet_cs2>();
inline auto g_fx_firebullet = std::make_unique<c_fx_firebullet>();
inline auto g_ragebot = std::make_unique<c_rage_bot>();