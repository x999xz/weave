#pragma once
#include <stack>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <format>
#include <optional>
#include "helper/animation.h"
#include "../utilities/input_system/input_system.h"
#include "../renderer/render_manager.h"
#include "../utilities/nlohmann/json.hpp"
#include "../utilities/xorstr.h"
#include "../utilities/cloud/user.h"
#include "../utilities/hotkey_system/hotkey_system.h"
#include <codecvt>

/*
	HARAM GUI 0.1
	EBANIY PIZDEC NAHYI
*/

enum action
{
	search = 1 << 0,
	tab = 1 << 1
};

struct rect_
{
	rect_(render_position min_, render_size size) {
		min = min_;
		max.x = min.x + size.x;
		max.y = min.y + size.y;
	}
	render_position min;
	render_position max;
};

class c_gui_helper
{
public:
	bool is_hovered(render_position cursor_pos, rect_ dst);
	render_color animation_color(render_color non_active, render_color active, float multiplication);
};

struct gui_config
{
	gui_config(std::string name, std::string data, std::string owner, std::string share) : name_{ name }, data_{ data }, owner_{ owner }, share_{ share } {};
	std::string name_;
	std::string data_;
	std::string owner_;
	std::string share_;
};

struct gui_element
{
	gui_element(std::string name, int type) : name_{ name }, var_{ }, type_{ type }, should_multi_weapons{ false } {};
	gui_element(std::string name, std::string var, int type, bool should_weapons = false) : name_{ name }, var_{ var }, type_{ type }, should_multi_weapons{ should_weapons } {};
	gui_element(std::string name, std::string var, int type, float min, float max, bool should_weapons = false) : name_{ name }, var_{ var }, type_{ type }, min_{ min }, max_{ max }, should_multi_weapons { should_weapons } {};
	gui_element(std::string name, std::string var, std::vector<std::string> names, int type, bool should_weapons = false) : name_{ name }, var_{ var }, names_{ names }, type_{ type }, should_multi_weapons{ should_weapons } {};
	gui_element(std::string name, std::vector<std::string> vars, std::vector<std::string> names, int type, bool should_weapons = false) : name_{ name }, vars_{ vars }, names_{ names }, type_{ type }, should_multi_weapons{ should_weapons } {};
	std::string name_;
	std::vector<std::string> names_;
	std::string var_;
	std::vector<std::string> vars_;
	int type_;
	float min_;
	float max_;
	bool should_multi_weapons = false;
};

struct gui_element2
{
	gui_element2(std::string name, int tab, int group, std::string tab_, std::string group_) : name_{ name }, tab{ tab }, group{ group }, tab_{ tab_ }, group_{ group_ } {};
	std::string name_;
	int tab;
	int group;
	std::string tab_;
	std::string group_;
};

struct gui_group
{
	gui_group() {};
	gui_group(std::string name, bool same_line, render_position cursor_pos, render_size size) : name_{ name }, same_line_{ same_line }, cursor_pos_{ cursor_pos }, size_{ size } {};
	std::string name_;
	bool same_line_;
	render_position cursor_pos_;
	render_size size_;
	std::vector<gui_element> elements;
};

struct gui_popup
{
	gui_popup(std::string name, render_position cursor_pos, render_size size, int key) : name_{ name }, m_backup_cursor_pos_{ cursor_pos }, cursor_pos_{}, size_ { size }, key_{ key }, is_open_{ false }, animation_{} {};
	std::string name_;
	render_position m_backup_cursor_pos_;
	render_position cursor_pos_{};
	render_size size_;
	int key_;
	bool is_open_;
	c_animation animation_;
};

struct gui_tab
{
	gui_tab(std::string name, bool is_home) : name_{ name }, is_home_{ is_home } {};
	std::string name_;
	bool is_home_;
	c_animation animation{};
};

struct gui_combo_info
{
	gui_combo_info() : is_trasform{ false }, transform{ 0.f } {};
	bool is_trasform;
	float transform;
};

struct gui_slider
{
	gui_slider() = default;
	float animation_previous{};
	float animation_{};
};

struct gui_text_input
{
	gui_text_input() = default;
	c_animation animation_{};
	bool active_{};
	float animation_text{};
};

struct gui_color_picker {
	gui_color_picker() {};
	float hue_bar;
	render_position picker;
	float alpha;
	int active_element = -1;
};

struct gui_scroll {
	gui_scroll()  = default;
	float scroll_amount = 0.f;
	float scroll_element_amount = 0.f;
	float animation_scroll = 0.f;
	float animation_element_scroll = 0.f;
};

struct hotkey_info {
	bool enabled;
	std::vector<double> value;
};

struct gui_window {
	std::string m_window_name;
	std::uint64_t m_window_hash;
	render_size m_window_size;
	render_size m_fully_window_size;
	render_position m_window_position;
	render_position m_cursor_position;
	bool m_direction;
	bool m_open;
};

enum type_item
{
	type_knife,
	type_weapons,
	type_agent,
	type_glove,
	type_sticker
};

struct gui_skins {
	int item_def;
	std::string paint_name;
	std::string name;
	uint64_t skin_key;
	int paint_id;
	int rarity;
	int texture_id;
	int type;
	std::string path_image;
	bool is_initilization;
	int paint_seed;
	int paint_wear;
	int stattrak;
	std::array<int, 5> stickers;
	std::string custom_name;
	std::uint64_t id;
};

struct gui_scrollbar_animation {
	float value;
	float lerp_value;
	void update() {
		lerp_value = std::lerp(lerp_value, value, g_render->get_delta_render() * 8.f);
	}
};

class c_gui
{
public:
	void present();
	void setup();
	void win32_processing(int index);
private:
	void set_window_size(float x, float y)
	{
		window_size = render_size(x, y);
	}
public:
	void set_mouse_pos(float x, float y)
	{
		m_mouse_pos_ = render_position(x, y);
	}

	render_position get_mouse_pos() const
	{
		return m_mouse_pos_;
	}

	bool has_pressed(int index)
	{
		if (m_moved_window != -1 && m_moved_window != m_current_window)
			return false;

		if (m_hovered_window != -1 && m_hovered_window != m_current_window)
			return false;

		return buttons[index].pressed_;
	}

	bool has_on_pressed(int index)
	{
		if (m_moved_window != -1 && m_moved_window != m_current_window)
			return false;

		if (m_hovered_window != -1 && m_hovered_window != m_current_window)
			return false;

		return buttons[index].on_pressed_;
	}

	bool has_hold(int index)
	{
		if (m_moved_window != -1 && m_moved_window != m_current_window)
			return false;

		if (m_hovered_window != -1 && m_hovered_window != m_current_window)
			return false;

		return buttons[index].hold_;
	}

	bool has_active()
	{
		return active_id != -1;
	}

	void set_cursor_pos(render_position new_cursor_pos)
	{
		m_cursor_pos_ = new_cursor_pos;
	}

	bool is_open_menu() {
		return draw_;
	}

	render_position get_cursor_pos()
	{
		return m_cursor_pos_;
	}

	render_position get_position()
	{
		return m_window_pos_ + m_cursor_pos_;
	}

	void reset_buttons()
	{
		for (int i{}; i < 256; i++)
		{
			buttons[i].pressed_ = false;
			buttons[i].on_pressed_ = false;
			buttons[i].repeat_time_ = std::clamp(buttons[i].repeat_time_ - g_render->get_delta_render(), 0.f, buttons[i].repeat_time_);
		}
	}

	static bool is_open(gui_popup popup) {
		return !popup.is_open_ && popup.animation_.base <= 0.0f;
	};

	std::string get_name_key(char key);

	bool has_popup_open()
	{
		bool value = true;
		auto popup = std::find_if(begin(m_popup), end(m_popup), [&value](const std::pair<std::uint64_t, gui_popup>& p) {
			return p.second.is_open_ == value;
			});
		return popup != m_popup.end();
	}

	hotkey_info has_active_bind(std::string var) {
		double value = true;
		std::vector<double> value_ = {};
		bool find = false;
		g_hotkey->mutex_.lock();
		if (g_hotkey->hotkeys_->find(std::hash<std::string>()(var)) != g_hotkey->hotkeys_->end() && !g_hotkey->hotkeys_->at(std::hash<std::string>()(var)).binds.empty())
		{

			auto bind = std::find_if(begin(g_hotkey->hotkeys_->at(std::hash<std::string>()(var)).binds), end(g_hotkey->hotkeys_->at(std::hash<std::string>()(var)).binds), [&value](const hotkey_impl& p) {
				return p.enabled == value && p.key != -1;
				});
			find = bind != g_hotkey->hotkeys_->at(std::hash<std::string>()(var)).binds.end();

			if (find)
				value_ = bind->value;
		}
		g_hotkey->mutex_.unlock();

		hotkey_info temp{};
		temp.enabled = find;
		temp.value = value_;

		return temp;
	}

	void reset_active_id()
	{
		active_id = -1;
	}

private:
	void menu();
	void decoration();
	void handle_begin();
	void handle_end();
private: // elements
	void begin_group(const std::string name, const render_size size, bool same_line = false);
	void end_group();
	void tabs();
	void combo(const std::string name, const std::string hash_name, int& select, std::vector<std::string >& list);
	void combo(const std::string name, std::string var, std::vector<std::string >& list);
	void multicombo(const std::string name, std::vector<std::string> vars, std::vector<std::string > list);
	void multicombo(const std::string name, const std::vector<std::string> hash_name, std::vector<double>& values, std::vector<std::string > list);
	bool begin_popup(const std::string name, const render_size region_size, const render_size popup_size, const int key);
	void end_popup();
	void colorpicker(std::string name, std::string var);
	void checkbox(const std::string name, std::string var);
	void checkbox(const std::string name, const std::string hash_name, bool& value);
	void slider(const std::string name, std::string var, const int min, const int max);
	void slider(const std::string name, const std::string hash_name, int& value, const int min, const int max);
	void slider_float(const std::string name, std::string var, const float min, const float max);
	void slider_float(const std::string name, const std::string hash_name, float& value, const float min, const float max);
	void text(const std::string name, const bool same_line);
	void hotkey(std::string name, std::string hash_name, render_position position);
private: // helpers
	void create_hotkey(std::string item, std::uint64_t hash_item, int type, std::vector<std::string> name, std::vector<double> items);
	void create_hotkey(std::string item, std::uint64_t hash_item, int type, std::vector<std::string> name_visual, std::vector<std::string> name, std::vector<double> items);
	void add_bind(hotkeys& hotkey, int type, std::vector<std::string> name, std::vector<double> items);
	void add_bind(hotkeys& hotkey, int type, std::vector<std::string> name_visual, std::vector<std::string> name, std::vector<double> items);
	bool contains_hotkey(std::uint64_t item);
	render_size get_group_size();
	bool is_hovered_pressed(rect_ dst);
	bool is_hovered(rect_ dst);
	void create_window(std::string name, render_size window_size, render_size fully_window_size);
public:
	std::string get_string_input(std::wstring& input) {
		return std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(input);
	}

	std::wstring get_wstring_input(std::string& input) {
		return std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(input);
	}
	void update_windows();
private:
	bool has_moved_window();
public:
	std::optional<gui_window> find_window(std::string name);
	std::wstring key_to_string(int key);
private: // pages
	void home_page();
	void esp_preview();
	void inventory_page();
private:
	void get_elements();
public:
	render_position m_mouse_pos_{};
	render_position m_pressed_mouse_pos_{}; // pizdec nahyi
	render_position m_cursor_pos_{};
	render_position m_window_pos_{};
	bool draw_{};
	bool direction{};
	c_gui_helper helper{};
	render_size window_size{};
	bool has_popup_open_{};
public:
	std::vector< gui_config> configs{};
	std::string select_config;
public:
	std::unordered_map<std::uint64_t, gui_element2> elements;
	std::wstring search{};
	bool active_search{};
	std::wstring input{};
	bool active_input{};
	bool changed_config{};
	int removed_bind = -1;
public:
	std::unordered_map<std::uint64_t, c_animation> animation{};
	std::unordered_map<std::uint64_t, float> animation_lerp{};
public:
	std::array<c_buttons, 256> buttons;
public:
	std::uint64_t anim_active_id = -1;
	std::uint64_t active_id = -1;
	std::uint64_t active_hotkey = -1;
	std::uint64_t current_index_config = -1;
	std::string current_config;
	int active_tab = 0;
public:
	std::stack< gui_group> m_groups;
	std::unordered_map<int, std::vector<gui_group>> m_groups2;
	std::map<std::uint64_t, gui_popup> m_popup{};
	std::map<std::uint64_t, gui_combo_info> m_combo_info{};
	std::map<std::uint64_t, gui_slider> m_slider{};
	std::map<std::uint64_t, gui_text_input> m_input_text{};
	std::map<std::uint64_t, gui_color_picker> m_color_picker{};
	std::map<std::uint64_t, gui_scroll> m_scroll{};
	std::map<std::uint64_t, gui_scrollbar_animation> m_scrollbar{};
	std::map<std::uint64_t, std::uint64_t> m_texture{};
	std::uint64_t current_popup = -1;
	std::vector< gui_tab> m_tabs;
	std::vector<gui_window> m_windows{};
	std::uint32_t m_current_window = -1;
	std::uint32_t m_moved_window = -1;
	std::uint32_t m_last_moved_window = -1;
	std::uint32_t m_hovered_window = -1;
	std::wstring input_character_queue;
	float dpi_scale = 1.f;
public:
	render_position padding_element;
public:
	std::uint64_t hash_menu;
public:
	int current_tab;
	int current_group;
public:
	std::wstring input_skin;
	bool is_active_input_skin;
	std::vector<std::string> groups_weapon;
	bool rendering = false;
	std::vector<gui_skins> item_default;
	std::vector<gui_skins> item_knife_default;
	std::vector<gui_skins> item_stickers;
	std::vector<gui_skins> item_agent;
	std::vector<gui_skins> item_glove;
	std::map<std::uint64_t, std::vector<gui_skins>> item_weapons;
	std::vector<gui_skins> skin_preview;
	std::vector<gui_skins> skin_added;
	gui_skins current_skin{};
	int current_sticker = -1;
	std::array<gui_skins, 5> current_stickers{};
	int inventory_tab = 0;
	int skins_item_def = -1;
	int saved_item_def = -1;
	int paint_seed = 0;
	int paint_wear = 0;
	int stattrack = 0;
	std::wstring message;
	bool has_focus_chat = false;
	bool has_time_out_chat = false;
	float time_out_chat = 1.f;
	int type_home_tab = 0;
};

inline auto g_gui = std::make_unique<c_gui>();