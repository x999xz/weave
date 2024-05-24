#pragma once
#include "../../utilities/utilities.hpp"
#include "../../sdk/sdk.hpp"
#include "../../sdk/math/math.hpp"

#include <array>
#include <mutex>
#include "../../renderer/render_manager.h"
#include "../../gui/helper/animation.h"

typedef struct _box_t
{
	float x, y, w, h;
} box_t;

struct clr_t
{
	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
	std::uint8_t a;
};

struct hit_t
{
	float time;
	scene_hitbox_data hitbox_data;
	scene_hitbox_position hitbox_position;
	clr_t clr;
};

struct skeleton_t {
	vector child;
	vector parent;
};

class c_player_storage {
public:
	std::uint64_t handle;
	vector abs_origin, mins, maxs;
	std::array<skeleton_t, 128> m_skeleton{};
	std::pair<bool, std::array<render_position, 3>> m_arrow;
	std::vector<std::string> m_flags;
	std::string username;
	std::string weapon_name;
	int item_index;
	std::uint64_t steamid;
	int health;
	bool is_dead;
	bool is_invalid;
};

class c_dropped_weapons {
public:
	bool is_invalid;
	std::uint64_t handle;
	vector abs_origin;
	vector mins;
	vector maxs;
	std::string weapon_name;
	int item_index;
};

class c_damage_marker {
public:
	c_damage_marker(std::string damage, vector position, float time) : damage(damage), position(position), is_world_screen{}, world_position{}, time(time), animation() {}
	bool is_world_screen;
	vector position;
	vector world_position;
	std::string damage;
	float time;
	c_animation animation;
	c_animation animation2;
};

class c_visuals {
public:
	void run_hit_capibara();
	void run_present();
	void update(int stage);
	void update_damage();
	void add_damage(std::string damage, vector position);
	void render_damage();
protected:
	void run_overlay_render();
	void run_player_esp(c_cs_player_controller* controller);
	void run_c4_esp(c_planted* c4);
	void run_weapons_world_esp();
	void run_grenade_trail();
	void run_removables();
private:
	std::pair<bool, box_t> get_bounding_box(vector origin, vector mins, vector maxs);
public:
	c_cs_player_pawn* defuser_bomb_pawn = nullptr;
	float timer = 0.f;
	int damage = 0;
	std::unordered_map< int, char > m_weapon_icons;
	std::vector< hit_t> hit_capibara;
	std::mutex m_mutex;
	std::deque<c_player_storage> m_players;
	std::vector< c_dropped_weapons> m_dropped_weapons;
	bool chams_visible, chams_invisible, attachment_chams;
	int chams_type;
	std::uint32_t chams_visible_clr, chams_invisible_clr, attachment_chams_clr;
	std::array<bool, 6> m_flags;
	std::vector< c_damage_marker> m_damage_marker;
	std::mutex m_damage_mutex;

};

inline auto g_visuals = std::make_unique<c_visuals>();