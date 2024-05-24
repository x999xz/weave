// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "visuals.hpp"

#include <tinyformat/tinyformat.h>

#include "../../GUI/GUI.h"

#include "../lagcompensation/lagcompensation.hpp"
#include "../ragebot/ragebot.hpp"
#include "../misc/misc.h"

std::pair<bool, box_t> c_visuals::get_bounding_box(vector origin, vector mins, vector maxs)
{
	vector flb, brt, blb, frt, frb, brb, blt, flt = { };
	float left, top, right, bottom = 0.f;

	vector Min = mins + origin;
	vector Max = maxs + origin;

	std::array<vector, 8> points = {
		vector(Min.x, Min.y, Min.z),
		vector(Min.x, Min.y, Max.z),
		vector(Min.x, Max.y, Min.z),
		vector(Min.x, Max.y, Max.z),
		vector(Max.x, Min.y, Min.z),
		vector(Max.x, Min.y, Max.z),
		vector(Max.x, Max.y, Min.z),
		vector(Max.x, Max.y, Max.z) };

	if (!math::world_to_screen(points[3], flb)
		|| !math::world_to_screen(points[5], brt)
		|| !math::world_to_screen(points[0], blb)
		|| !math::world_to_screen(points[4], frt)
		|| !math::world_to_screen(points[2], frb)
		|| !math::world_to_screen(points[1], brb)
		|| !math::world_to_screen(points[6], blt)
		|| !math::world_to_screen(points[7], flt))
		return {};

	std::array<vector, 8> arr = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (std::int32_t i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;

		if (bottom < arr[i].y)
			bottom = arr[i].y;

		if (right < arr[i].x)
			right = arr[i].x;

		if (top > arr[i].y)
			top = arr[i].y;
	}

	box_t box;

	box.x = left;
	box.y = top;
	box.w = right - left;
	box.h = bottom - top;

	return { true, box };
}

void render_text(render_position pos, render_color clr, const char* txt, render_font* font = nullptr, int size = 11, bool outline = false)
{
	g_render->get_buffer()->text(font, size, txt, pos, clr.override_alpha(g_render->get_override_alpha()), outline);
}

void draw_box(box_t& box, render_color clr)
{
	g_render->rect(render_position(box.x - 1, box.y - 1), render_size(box.w + 2, box.h + 2), render_color(0, 0, 0));
	g_render->rect(render_position(box.x + 1, box.y + 1), render_size(box.w - 2, box.h - 2), render_color(0, 0, 0));
	g_render->rect(render_position(box.x, box.y), render_size(box.w, box.h), clr);
}
//
void draw_health(box_t& box, std::int32_t player_health)
{
	float bar_height = player_health * box.h / 100.f;
	std::uint8_t color_scale = static_cast<std::uint8_t>(player_health * 2.55);

	box_t bar_box = { box.x - 5.f, box.y, 3.f, box.h };
	box_t health_bar = { box.x - 5.f, box.y + box.h - bar_height, 3.f, bar_height };

	g_render->rect_filled(render_position(bar_box.x, health_bar.y), render_size(health_bar.w, health_bar.h), render_color(255 - color_scale, color_scale, 0));
	g_render->rect(render_position(bar_box.x, bar_box.y), render_size(bar_box.w, bar_box.h), render_color::black());

	if (player_health < 93)
	{
		render_text(render_position(health_bar.x, health_bar.y) - render_position(g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, std::to_string(player_health).c_str()).x / 2 + 5, 0), render_color::white(), std::to_string(player_health).c_str(), g_render->get_font(6), 10, true);
	}
}
//
void draw_name(box_t& box, const char* player_name, std::uint64_t steamid, std::uint32_t clr)
{
	std::string name(player_name);

	if (name.empty())
		return;

	if (name.size() > 15)
		name = name.substr(0, 15) + "...";

	auto calc_text = g_render->get_font(8)->calc_text_size(10, FLT_MAX, FLT_MAX, name.c_str());

	auto pos = render_position(box.x + (box.w / 2) - calc_text.x / 2, box.y - calc_text.y - 4);

	render_text(pos + render_position(1, 1), render_color::black().override_alpha(0.5f), name.c_str(), g_render->get_font(8), 10, false);
	render_text(pos, clr, name.c_str(), g_render->get_font(8), 10, false);

	if (g_misc->m_avatars_cache_[steamid] > 0 && g_user->IsActive(xorstr_("esp_avatar"), xorstr_("esp_avatar"), 0))
		g_render->add_texture(pos - render_position(12, 0), render_size(10, 8), g_misc->m_avatars_cache_[steamid]);
}

void rotate_triangle(std::array<render_position, 3>& points, float rotation)
{
	const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
	for (auto& point : points)
	{
		point -= points_center;

		const auto temp_x = point.x;
		const auto temp_y = point.y;

		const auto theta = math::deg2rad(rotation);
		const auto c = cosf(theta);
		const auto s = sinf(theta);

		point.x = temp_x * c - temp_y * s;
		point.y = temp_x * s + temp_y * c;

		point += points_center;
	}
}

render_position RotateVertex(const vector& p, const render_position& v, float angle) {
	// convert theta angle to sine and cosine representations.
	float c = std::cos(math::deg2rad(angle));
	float s = std::sin(math::deg2rad(angle));

	return {
		p.x + (v.x - p.x) * c - (v.y - p.y) * s,
		p.y + (v.x - p.x) * s + (v.y - p.y) * c
	};
}

void draw_oof(c_cs_player_pawn* player) {

	if (!player->game_scene_node())
		return;

	if (!g_user->IsActive(xorstr_("esp_oof"), xorstr_("esp_oof"), 0))
		return;

	vector view_origin, target_pos, delta;
	vector screen_pos, offscreen_pos;
	float  leeway_x, leeway_y, radius, offscreen_rotation;
	bool   is_on_screen;
	std::array<render_position, 3> verts;

	// todo - dex; move this?
	auto get_offscreen_data = [](const vector& delta, float radius, vector& out_offscreen_pos, float& out_rotation) {
		vector  view_angles(Interfaces::csgo_input->view_angle);
		vector fwd, right, up(0.f, 0.f, 1.f);
		float  front, side, yaw_rad, sa, ca;

		// get viewport angles forward directional vector.
		math::angle_vectors(view_angles, fwd);

		// convert viewangles forward directional vector to a unit vector.
		fwd.z = 0.f;
		fwd.normalize();

		// calculate front / side positions.
		right = up.cross(fwd);
		front = delta.dot(fwd);
		side = delta.dot(right);

		// setup offscreen position.
		out_offscreen_pos.x = radius * -side;
		out_offscreen_pos.y = radius * -front;

		// get the rotation ( yaw, 0 - 360 ).
		out_rotation = math::rad2deg(std::atan2(out_offscreen_pos.x, out_offscreen_pos.y) + math::get_pi());

		// get needed sine / cosine values.
		yaw_rad = math::deg2rad(-out_rotation);
		sa = std::sin(yaw_rad);
		ca = std::cos(yaw_rad);

		// rotate offscreen position around.
		out_offscreen_pos.x = (int)((g_cs2->screen.x / 2.f) + (radius * sa));
		out_offscreen_pos.y = (int)((g_cs2->screen.y / 2.f) - (radius * ca));
		};

	// get the player's center screen position.
	target_pos = player->game_scene_node()->abs_origin();
	is_on_screen = math::world_to_screen(target_pos, screen_pos);

	// give some extra room for screen position to be off screen.
	leeway_x = g_cs2->screen.x / 18.f;
	leeway_y = g_cs2->screen.y / 18.f;

	// origin is not on the screen at all, get offscreen position data and start rendering.
	if (!is_on_screen
		|| screen_pos.x < -leeway_x
		|| screen_pos.x >(g_cs2->screen.x + leeway_x)
		|| screen_pos.y < -leeway_y
		|| screen_pos.y >(g_cs2->screen.y + leeway_y)) {

		// get viewport origin.
		view_origin = g_cs2->local_player->game_scene_node()->abs_origin();

		// get direction to target.
		delta = (target_pos - view_origin).normalized();

		// note - dex; this is the 'YRES' macro from the source sdk.
		radius = 200.f * (g_cs2->screen.y / 480.f);

		// get the data we need for rendering.
		get_offscreen_data(delta, radius, offscreen_pos, offscreen_rotation);

		// bring rotation back into range... before rotating verts, sine and cosine needs this value inverted.
		// note - dex; reference: 
		// https://github.com/VSES/SourceEngine2007/blob/43a5c90a5ada1e69ca044595383be67f40b33c61/src_main/game/client/tf/tf_hud_damageindicator.cpp#L182
		offscreen_rotation = -offscreen_rotation;

		// setup vertices for the triangle.
		verts[0] = { offscreen_pos.x, offscreen_pos.y };        // 0,  0
		verts[1] = { offscreen_pos.x - 12.f, offscreen_pos.y + 24.f }; // -1, 1
		verts[2] = { offscreen_pos.x + 12.f, offscreen_pos.y + 24.f }; // 1,  1

		// rotate all vertices to point towards our target.
		verts[0] = RotateVertex(offscreen_pos, verts[0], offscreen_rotation);
		verts[1] = RotateVertex(offscreen_pos, verts[1], offscreen_rotation);
		verts[2] = RotateVertex(offscreen_pos, verts[2], offscreen_rotation);

		g_render->get_buffer()->poly_fill(verts.data(), verts.size(), g_user->IsActive(xorstr_("esp_oof_color"), xorstr_("esp_oof_color"), 0));
	}
}

void c_visuals::run_present()
{
	if (!g_cs2->local_player)
		return;

	m_mutex.lock();

	bool health = g_user->IsActive(xorstr_("esp_health"), xorstr_("esp_health"), 0);
	bool box = g_user->IsActive(xorstr_("esp_box"), xorstr_("esp_box"), 0);
	bool name = g_user->IsActive(xorstr_("esp_name"), xorstr_("esp_name"), 0);
	color_t skeleton_clr(g_user->GetConfig()[xorstr_("esp_skeleton_color")]);
	auto oof_clr = g_user->IsActive(xorstr_("esp_oof_color"), xorstr_("esp_oof_color"), 0);
	bool weapon_name = g_user->IsActive(xorstr_("esp_weapons_name"), xorstr_("esp_weapons_name"), 0);
	bool weapon_icon = g_user->IsActive(xorstr_("esp_weapons_icon"), xorstr_("esp_weapons_name"), 1);
	auto box_clr = g_user->GetConfig()[xorstr_("esp_box_color")];
	auto name_clr = g_user->GetConfig()[xorstr_("esp_name_color")];
	auto skeleton_act = g_user->IsActive(xorstr_("esp_skeleton"), xorstr_("esp_skeleton"), 0);

	for (auto& it : m_dropped_weapons) {
		auto ret = get_bounding_box(it.abs_origin, it.mins, it.maxs);

		if (!ret.first)
			continue;

		auto center = ret.second.x + (ret.second.w * 0.5f);

		auto calc_text = g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, it.weapon_name.c_str());

		float multiplicator = 1.f;

		if (g_cs2->local_player->is_alive()) {
			auto delta_ = g_cs2->local_player->game_scene_node()->abs_origin().dist_to(it.abs_origin);
			if (delta_ > 500.f) {
				auto delta = 400.f - std::clamp(delta_ - 500.f, 0.f, 400.f);

				multiplicator = delta / 400.f;
			}
		}
		render_text(render_position(center - (calc_text.x / 2), ret.second.y + ret.second.h + 1), render_color(255, 255, 255, 255 * multiplicator), it.weapon_name.c_str(), g_render->get_font(6), 10, true);
	}

	for (auto& it : m_players) {

		if (it.is_invalid)
			continue;

		auto ret = get_bounding_box(it.abs_origin, it.mins, it.maxs);

		if (it.m_arrow.first && g_user->IsActive(xorstr_("esp_oof"), xorstr_("esp_oof"), 0) && g_cs2->local_player && g_cs2->local_player->is_alive())
			g_render->get_buffer()->poly_fill(it.m_arrow.second.data(), it.m_arrow.second.size(), oof_clr);

		if (!ret.first)
			continue;

		g_gui->animation[HASH_RT(it.username.c_str())].run(!it.is_dead);

		g_render->push_override_alpha(g_gui->animation[HASH_RT(it.username.c_str())].base);

		if (box)
			draw_box(ret.second, box_clr);
		if (health)
			draw_health(ret.second, it.health);
		if (name)
			draw_name(ret.second, it.username.c_str(), it.steamid, name_clr);

		if (skeleton_act) {
			for (auto& skeleton : it.m_skeleton) {

				if (skeleton.child.is_zero() || skeleton.parent.is_zero())
					continue;

				vector screen0, screen1;
				if (math::world_to_screen(skeleton.child, screen0) && math::world_to_screen(skeleton.parent, screen1))
					g_render->line(render_position(screen0.x, screen0.y), render_position(screen1.x, screen1.y), render_color(skeleton_clr.get_red(), skeleton_clr.get_green(), skeleton_clr.get_blue(), skeleton_clr.get_alpha()), render_color(skeleton_clr.get_red(), skeleton_clr.get_green(), skeleton_clr.get_blue(), skeleton_clr.get_alpha()));
			}
		}

		int padding = 0;

		for (auto& flag : it.m_flags) {
			render_text(render_position(ret.second.x + ret.second.w + 5, ret.second.y + padding), render_color(255, 255, 255, 255), flag.c_str(), g_render->get_font(6), 10, true);
			padding += g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, flag.c_str()).y + 2;
		}

		auto center = ret.second.x + (ret.second.w * 0.5f);

		auto calc_text = g_render->get_font(6)->calc_text_size(10, FLT_MAX, FLT_MAX, it.weapon_name.c_str());

		padding = 0;

		if (weapon_name)
		{
			render_text(render_position(center - (calc_text.x / 2), ret.second.y + ret.second.h + 1), render_color(255, 255, 255, 255), it.weapon_name.c_str(), g_render->get_font(6), 10, true);
			padding += calc_text.y + 2;
		}

		if (weapon_icon)
		{
			if (g_visuals->m_weapon_icons.find(it.item_index) != g_visuals->m_weapon_icons.end())
			{
				std::string txt = std::string(1, char(g_visuals->m_weapon_icons[it.item_index]));
				auto calc_icon = g_render->get_font(5)->calc_text_size(12, FLT_MAX, FLT_MAX, txt.c_str());
				render_text(render_position(center - (calc_icon.x / 2), ret.second.y + ret.second.h + 1 + padding), render_color(255, 255, 255, 255), txt.c_str(), g_render->get_font(5), 12, true);
			}
		}

		g_render->pop_override_alpha();
	}
	m_mutex.unlock();
}