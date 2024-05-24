// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../../utilities/tls/tls.h"
#include "../hooks.hpp"
#include "../../GUI/GUI.h"

#include "../../renderer/fonts/weapons.h"
#include "../../renderer/fonts/verdana.h"
#include "../../renderer/images/cross.h"

#include <tinyformat/tinyformat.h>
#include "../../utilities/input_system/input_system.h"
#include "../../utilities/hotkey_system/hotkey_system.h"
#include "../../utilities/cloud/user.h"

#include <memory>
#include <chrono>
#include <thread>
#include "../../Logging.h"
#include "../../sdk/vtex/VTexParser.h"

#include "../../renderer/fonts/pixel.h"
#include "../../renderer/fonts/sans.h"

#include "../../feature/misc/hitmarker.h"
#include "../../utilities/service/flatbuffers.hpp"

#include <codecvt>
#include "../../utilities/hash.h"
#include "../feature/inventory_changer/inventory_changer.h"

struct dlight_color
{
	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
};

struct DynamicLight_t {
	float m_flUnk; //0x0000
	vector m_vecOrigin; //0x0004
	float m_flRadius; //0x0010
	dlight_color m_nColor; //0x0014
	std::uint8_t mult;
	float m_flDie; //0x0018
	float m_flExponent; //0x001C
	char pad_0020[40]; //0x0020
	class N000004C0* m_pSceneLayer; //0x0048
}; //Size: 0x0050

class dlight_manager
{
public:
	char pad[0x18];
	DynamicLight_t aye;
};

std::string value_to_string(hotkeys& hotkeys, hotkey_impl& hotkey) {

	std::string value = tfm::format("%d", hotkey.value[0]);

	if (hotkey.type == 0)
		value = hotkey.value[0] ? xorstr_("ON") : xorstr_("OFF");
	else if (hotkey.type == 3)
	{
		bool find = false;
		value.clear();
		value.append(xorstr_("["));
		for (auto i = 0; i < hotkey.value.size(); i++)
		{
			if (!hotkey.value[i])
				continue;

			find = true;

			value += tfm::format(xorstr_("%s, "), hotkeys.name_visuals[i]);
		}
		if (value.size() > 2)
			value.erase(value.end() - 2, value.end());
		value.append(xorstr_("]"));
		if (!find)
			value = xorstr_("None");
	}
	else if (hotkey.type == 2)
	{
		value = tfm::format(xorstr_("[%s]"), hotkeys.name_visuals[hotkey.value[0]]);
	}

	return value;
}

void render_cloud()
{
	render_size size_block = render_size(220, 50);
	auto position = render_position(g_render->get_screen_size().x, 10);

	if (g_gui->animation.find(std::hash<std::string>()(xorstr_("cloud_render"))) == g_gui->animation.end())
	{
		c_animation temp{};
		temp.base = 0.f;
		temp.timer = 0.f;
		g_gui->animation.try_emplace(std::hash<std::string>()(xorstr_("cloud_render")));
	}

	if (g_gui->animation.find(std::hash<std::string>()(xorstr_("animation_line1"))) == g_gui->animation.end())
	{
		c_animation anim_temp;
		anim_temp.base = 0.f;
		anim_temp.timer = 0.f;
		g_gui->animation.try_emplace(std::hash<std::string>()(xorstr_("animation_line1")), anim_temp);
	}

	if (g_gui->animation.find(std::hash<std::string>()(xorstr_("animation_line2"))) == g_gui->animation.end())
	{
		c_animation anim_temp;
		anim_temp.base = 0.f;
		anim_temp.timer = 0.f;
		g_gui->animation.try_emplace(std::hash<std::string>()(xorstr_("animation_line2")), anim_temp);
	}

	g_gui->animation[std::hash<std::string>()(xorstr_("animation_line1"))].run(true, 0.4f);

	if (g_gui->animation[std::hash<std::string>()(xorstr_("animation_line1"))].base > 0.75f)
		g_gui->animation[std::hash<std::string>()(xorstr_("animation_line2"))].run(true, 0.6f);

	if (g_gui->animation[std::hash<std::string>()(xorstr_("animation_line2"))].base >= 1.f)
	{
		g_gui->animation[std::hash<std::string>()(xorstr_("animation_line2"))] = g_gui->animation[std::hash<std::string>()(xorstr_("animation_line1"))] = c_animation();
	}

	auto& anim = g_gui->animation.find(std::hash<std::string>()("cloud_render"))->second;

	if (g_cs2->m_initilization) {
		anim.run(g_cs2->m_initilization && g_tls_client->has_reconnection, 0.2f);
	}
	else {
		anim.run(!g_cs2->m_initilization, 0.2f);
	}

	g_render->push_override_alpha(anim.base);

	position -= render_position((10 + size_block.x) * anim.base, 0);

	g_render->set_limit(position, size_block);
	g_render->rect_filled(position, size_block, render_color(0, 0, 0, 0), 0, 5.f);
	g_render->rect_filled(position, size_block, render_color(16, 16, 16), c_render_manager::render_flags_::blur, 5.f);
	g_render->rect_filled(position, size_block, render_color(16, 16, 16, 180), 0, 5.f);
	g_render->rect_filled(position + render_position(0, size_block.y - 6), render_size(size_block.x, 6), render_color(50, 50, 50), 0, 5.f);
	g_render->rect_filled(position + render_position(0, size_block.y - 6) + render_size(size_block.x * g_gui->animation[std::hash<std::string>()(xorstr_("animation_line2"))].base, 0), render_size(size_block.x * g_gui->animation[std::hash<std::string>()(xorstr_("animation_line1"))].base, 6), render_color(255, 108, 68), 0, 5.f);
	g_render->add_texture(position + render_position(14, 11), render_size(50, 23), g_gui->m_texture[1]);
	g_render->add_text(g_tls_client->has_reconnection ? xorstr_("Reconnecting...") : xorstr_("Connecting..."), position + render_position(82, 8), render_color::white(), g_render->get_font(1), 13.f);
	if (!g_tls_client->has_reconnection)
		g_render->add_text(tfm::format(xorstr_("Loading Weave [%d]"), g_cs2->m_initilization_stage), position + render_position(82, 26), render_color(86, 86, 87), g_render->get_font(1), 9.f);
	g_render->pop_limit();

	g_render->pop_override_alpha();
}

void send_message(std::string message) {
	c_flatbuffers m_buffer;
	m_buffer.create_message(g_cs2->username, message);
	m_buffer.create_stream(false);

	c_flatbuffers m_buffer2;
	m_buffer2.create_request(HASH("sent_message"), 1, m_buffer.m_buffer);
	m_buffer2.create_stream();

	g_tls_client->send(m_buffer2.m_buffer.data(), m_buffer2.m_buffer.size());

	float max_size = int(g_cs2->messages.size()) * 60;
	max_size -= (60 * 5);
	max_size = std::max(0.f, max_size);

	g_cs2->messages.push_back({ g_cs2->username, message, false, std::uint64_t(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) });

	if (g_gui->m_scrollbar[FNV32("chat")].value == max_size && g_cs2->messages.size() > 5)
		g_gui->m_scrollbar[FNV32("chat")].value += 60;
}

void sticky_message(int index, bool sticky) {
	c_flatbuffers m_buffer;
	m_buffer.create_request_sticky_message(index, sticky);
	m_buffer.create_stream(false);

	c_flatbuffers m_buffer2;
	m_buffer2.create_request(HASH("sticky_message"), 1, m_buffer.m_buffer);
	m_buffer2.create_stream();

	g_tls_client->send(m_buffer2.m_buffer.data(), m_buffer2.m_buffer.size());

	for (auto& it : g_cs2->messages)
		it.sticky = false;

	g_cs2->messages[index].sticky = sticky;
}

void draw_keybind() {
	auto window = g_gui->find_window("Keybind");

	for (auto it = g_hotkey->hotkeys_->begin(); it != g_hotkey->hotkeys_->end(); it++)
	{
		auto& binds = it->second.binds;
		auto& name = it->second.name_;
		auto hash = it->first;

		for (auto& bind : binds)
		{
			if (!bind.enabled || !bind.visible)
				continue;

			if (!it->second.name.empty() && isdigit(it->second.name.at(0).back()))
			{
				auto  current_weapon = atoi(&it->second.name.at(0).back());
				if (current_weapon != g_cs2->m_current_group)
					continue;
			}

			auto text = value_to_string(it->second, bind);

			if (std::find_if(g_misc->m_active_binds.begin(), g_misc->m_active_binds.end(), [&](const auto& x) { return x.name == name; }) != g_misc->m_active_binds.end())
				continue;

			auto& new_bind = g_misc->m_active_binds.emplace_back();
			new_bind.enabled = true;
			new_bind.value = text;
			new_bind.name = name;
			new_bind.key = bind.key;
			new_bind.mode = bind.mode;
			new_bind.hash = hash;
		}
	}

	bool has_visible = g_gui->is_open_menu() || g_misc->m_active_binds.size() > 0;

	if (window.has_value() && g_user->IsActive(xorstr_("misc_keybind"), xorstr_("misc_keybind"), 0) && has_visible)
	{
		auto position = window.value().m_window_position;
		auto name = window.value().m_window_name;
		auto calc_text = g_render->get_font(0)->calc_text_size(13.f, FLT_MAX, FLT_MAX, name.c_str());
		auto center = position + (window.value().m_window_size / 2) - (calc_text / 2);

		float size_y = 20 * std::count_if(g_misc->m_active_binds.begin(), g_misc->m_active_binds.end(), [](const auto& x) {
			return x.enabled;
			});

		g_gui->animation_lerp[FNV32("keybind_animation_y")] = std::lerp(g_gui->animation_lerp[FNV32("keybind_animation_y")], size_y, 0.1f);

		g_render->rect_filled(position, window.value().m_window_size, render_color(20, 20, 20), c_render_manager::render_flags_::blur, 5.f, render_rounding_flags_::ROUND_RECT_TOP);
		g_render->rect_filled(position, window.value().m_window_size, render_color(13, 13, 14, 220), 0, 5.f, render_rounding_flags_::ROUND_RECT_TOP);
		g_render->add_texture(position + (window.value().m_window_size / 2) - (render_size(58 * 0.65f, 25 * 0.65f) / 2), render_size(58 * 0.65f, 25 * 0.65f), g_gui->m_texture[1]);

		g_render->set_limit(position + render_position(0, 35), render_size(window.value().m_window_size.x, g_gui->animation_lerp[FNV32("keybind_animation_y")]));
		g_render->rect_filled(position + render_position(0, 35), render_size(window.value().m_window_size.x, g_gui->animation_lerp[FNV32("keybind_animation_y")]), render_color::black().override_alpha(0.4f), 0, 3.f, render_rounding_flags_::ROUND_RECT_BOT);

		position.y += 35;

		float high_size = 200.f;
		float temp_size = 0.f;

		for (auto it = g_misc->m_active_binds.begin(); it != g_misc->m_active_binds.end();)
		{
			if (!it->enabled && it->animation.base <= 0.f)
			{
				it = g_misc->m_active_binds.erase(it);
				continue;
			}

			it->animation.run(it->enabled);

			auto hotkey = std::find_if(g_hotkey->hotkeys_->at(it->hash).binds.begin(), g_hotkey->hotkeys_->at(it->hash).binds.end(), [](auto& x) {
				return x.enabled;
				});

			it->enabled = hotkey != g_hotkey->hotkeys_->at(it->hash).binds.end();
			it->value = it->enabled ? value_to_string(g_hotkey->hotkeys_->at(it->hash), *hotkey) : it->value;

			auto calc_text = g_render->get_font(0)->calc_text_size(11.f, FLT_MAX, FLT_MAX, it->value.c_str());

			auto size_window = 200.f + (calc_text.x - 70);

			if (size_window > high_size)
				high_size = std::max(size_window, 200.f);

			g_render->add_text(it->name, position + render_position(5, 2), render_color::white().override_alpha(it->animation.base), g_render->get_font(0), 11.f);
			g_render->add_text(it->value, position + render_position(window.value().m_window_size.x - calc_text.x - 5, 2), render_color::white().override_alpha(it->animation.base), g_render->get_font(0), 11.f);
			position.y += 20;

			it++;
		}

		g_render->pop_limit();

		float animation_lerp = window.value().m_window_size.x;

		animation_lerp = std::lerp(window.value().m_window_size.x, high_size, 0.1f);

		auto find = std::find_if(g_gui->m_windows.begin(), g_gui->m_windows.end(), [](gui_window window) {
			return window.m_window_name == xorstr_("Keybind");
			});

		if (find != g_gui->m_windows.end())
		{
			find->m_window_size.x = window.value().m_window_size.x = animation_lerp;
		}
	}
}

std::string get_time_string(messages& message) {

}

void draw_chat() {
	auto has_visible = g_gui->is_open_menu() && g_cs2->m_open_chat || g_gui->animation[FNV32("chat_anim")].base > 0.0f;

	auto window = g_gui->find_window("Chat");

	bool is_shift = g_gui->has_hold(VK_SHIFT);

	if (window.has_value() && has_visible && g_gui->m_scrollbar.contains(FNV32("chat")))
	{
		auto position = window.value().m_window_position;

		g_gui->animation[FNV32("chat_anim")].run(g_gui->is_open_menu() && g_cs2->m_open_chat);

		g_render->push_override_alpha(g_gui->animation[FNV32("chat_anim")].base);

		g_render->rect_filled(position + render_position(0, 0), render_size(window.value().m_window_size.x, 396), render_color(13, 13, 14), 0, 10.f);
		g_render->rect_filled_multi(position, render_size(window.value().m_window_size.x, 40), render_color_multi(render_color(255, 139, 59, 50), render_color(255, 139, 59, 50), render_color(14, 14, 16, 50), render_color(14, 14, 16, 50)), 10.f, render_rounding_flags_::ROUND_RECT_TOP);
		g_render->add_text(xorstr_("Chat"), position + render_position(30, 10), render_color(220, 220, 220), g_render->get_font(1), 13);

		if (g_gui->helper.is_hovered(g_gui->m_mouse_pos_, rect_(position + render_position(window.value().m_window_size.x - 5 - 20, 5), render_size(20, 20))) && g_gui->has_pressed(VK_LBUTTON) && g_cs2->m_open_chat) {
			g_cs2->m_open_chat = false;
		}

		float padding = 0.f;

		g_render->set_limit(position + render_position(8, 51), render_size(window.value().m_window_size.x - 16, 297));

		g_user->mutex_.lock();
		int index = 0;

		auto pos_ = position + render_position(8, 56);
		pos_.y -= g_gui->m_scrollbar[FNV32("chat")].lerp_value;

		auto stick_message = std::find_if(g_cs2->messages.begin(), g_cs2->messages.end(), [](auto msg) { return msg.sticky; });

		for (auto& msg : g_cs2->messages) {

			if (!g_cs2->animation_alpha.contains(index)) {
				g_cs2->animation_alpha.insert_or_assign(index, 0.f);
				g_cs2->animation_lerp.insert_or_assign(index, padding - 20);
			}

			g_cs2->animation_alpha[index] = std::clamp(g_cs2->animation_alpha[index] + 0.05f, 0.f, 1.f);
			g_cs2->animation_lerp[index] = std::lerp(g_cs2->animation_lerp[index], padding, 0.2f);

			/*if (g_gui->helper.is_hovered(g_gui->m_mouse_pos_, rect_(render_position(pos_.x + 10, pos_.y + g_cs2->animation_lerp[index]), render_size(window.value().m_window_size.x - 20, 50))) && g_gui->has_pressed(VK_RBUTTON) && !g_cs2->m_popup_message[index]) {
				g_cs2->m_popup_message[index] = true;
				g_cs2->m_popup_position[index] = vector(g_gui->m_mouse_pos_.x, g_gui->m_mouse_pos_.y, 0.f);
				//sticky_message(index, !msg.sticky);
			}*/

			//g_render->rect_filled(render_position(pos_.x + 10, pos_.y + g_cs2->animation_lerp[index]), render_size(window.value().m_window_size.x - 20, 50), render_color(12, 12, 10, 255.f * g_cs2->animation_alpha[index]), 0, 7.f);
			auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, msg.username.c_str());
			g_render->add_texture_circle(render_position(pos_.x, pos_.y + g_cs2->animation_lerp[index]), 12, g_user->GetAvatar(msg.username));
			g_render->add_text(tfm::format("%s", msg.username), render_position(pos_.x + 30, pos_.y + g_cs2->animation_lerp[index] + 3), render_color(255, 255, 255, 255.f * g_cs2->animation_alpha[index]), g_render->get_font(0), 12.f);
			g_render->add_text(g_utils->get_time_date(msg), render_position(pos_.x + 30 + calc_text.x + 4, pos_.y + g_cs2->animation_lerp[index] + 3), render_color(92, 92, 92, 255.f * g_cs2->animation_alpha[index]), g_render->get_font(0), 12.f);
			g_render->add_text(tfm::format("%s", msg.message), render_position(pos_.x + 30, pos_.y + g_cs2->animation_lerp[index] + 23), render_color(174, 174, 174, 255.f * g_cs2->animation_alpha[index]), g_render->get_font(0), 13.f);

			/*if (g_cs2->m_popup_message[index]) {
				g_render->rect_filled(render_position(g_cs2->m_popup_position[index].x, g_cs2->m_popup_position[index].y), render_size(80, 60), render_color(0, 0, 0, 255), 0, 10.f);

				g_render->rect_filled(render_position(g_cs2->m_popup_position[index].x + 10, g_cs2->m_popup_position[index].y + 10), render_size(60, 30), render_color(20, 20, 20, 255), 0, 10.f);

				if (g_gui->helper.is_hovered(g_gui->m_mouse_pos_, rect_(render_position(g_cs2->m_popup_position[index].x + 10, g_cs2->m_popup_position[index].y + 10), render_size(60, 30))) && g_gui->has_pressed(VK_LBUTTON)) {
					sticky_message(index, !msg.sticky);
					g_cs2->m_popup_message[index] = false;
				}
			}*/

			padding += 60;
			index++;
		}

		/*if (stick_message != g_cs2->messages.end()) {
			g_render->rect_filled(render_position(pos_.x + 10, pos_.y + 20), render_size(window.value().m_window_size.x - 20, 50), render_color(255, 0, 0, 255.f), 0, 7.f);
			g_render->add_text(tfm::format("%s:", stick_message->username), render_position(pos_.x + 20, pos_.y + 20 + 5), render_color(255, 255, 255, 255.f), g_render->get_font(0), 12.f);
			g_render->add_text(tfm::format("%s", stick_message->message), render_position(pos_.x + 20, pos_.y + 20 + 19), render_color(255, 255, 255, 255.f), g_render->get_font(0), 13.f);
		}*/

		g_user->mutex_.unlock();

		g_render->pop_limit();


		if (g_gui->has_focus_chat)
		{
			if (!g_gui->has_pressed(VK_RETURN))
			{
				if (g_gui->has_pressed(VK_BACK))
				{
					if (!g_gui->message.empty())
						g_gui->message.pop_back();
				}
				else if (g_gui->message.size() < 24) {
					g_gui->message += g_gui->input_character_queue;
				}
			}
		}

		if (g_gui->has_focus_chat && g_gui->has_pressed(VK_RETURN) && !g_gui->has_time_out_chat && g_gui->message.size() != 0) {
			auto message = g_gui->get_string_input(g_gui->message);
			send_message(message);
			g_gui->message.clear();
			g_gui->has_time_out_chat = true;
			g_gui->time_out_chat = 1.f;
		}

		if (g_gui->has_time_out_chat && !g_gui->has_pressed(VK_RETURN))
		{
			g_gui->time_out_chat -= g_render->get_delta_render();
			if (g_gui->time_out_chat <= 0.f)
				g_gui->has_time_out_chat = false;
		}

		if (g_gui->helper.is_hovered(g_gui->m_mouse_pos_, rect_({ position + render_position(8, 367), render_size(window.value().m_window_size.x - 16, 24) }))) {
			if (g_gui->has_pressed(VK_LBUTTON) && !g_gui->has_focus_chat)
				g_gui->has_focus_chat = true;
		}
		else if (g_gui->has_pressed(VK_LBUTTON)) {
			g_gui->has_focus_chat = false;
		}

		g_render->rect_filled(position + render_position(8, 367), render_size(window.value().m_window_size.x - 16, 24), render_color(23, 23, 23, 255), 0, 10.f);
		if (g_gui->has_focus_chat) {
			auto calc_input = g_render->get_font(0)->calc_text_size(11.f, FLT_MAX, FLT_MAX, g_gui->get_string_input(g_gui->message).c_str());
			g_render->add_text(g_gui->get_string_input(g_gui->message), position + render_position(18, 367 + 12 - (calc_input.y / 2)), render_color(255, 255, 255, 255), g_render->get_font(0), 11.f);
		}
		else {
			auto calc_input = g_render->get_font(0)->calc_text_size(11.f, FLT_MAX, FLT_MAX, "Message in Chat");
			g_render->add_text("Message in Chat", position + render_position(18, 367 + 12 - (calc_input.y / 2)), render_color(86, 86, 87, 255), g_render->get_font(0), 11.f);
		}

		g_render->pop_override_alpha();

		float max_size = int(g_cs2->messages.size()) * 60;
		max_size -= (60 * 5);
		max_size = std::max(0.f, max_size);

		if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == window->m_window_hash)
		{
			g_gui->m_scrollbar[FNV32("chat")].value += 60 * -g_input_system->get_scroll();
			g_gui->m_scrollbar[FNV32("chat")].value = std::max(0.f, g_gui->m_scrollbar[FNV32("chat")].value);
			g_gui->m_scrollbar[FNV32("chat")].value = std::clamp(g_gui->m_scrollbar[FNV32("chat")].value, 0.f, max_size);
			g_input_system->reset_scrolling();
		}

		g_gui->m_scrollbar[FNV32("chat")].update();
	}
}

void rendering(bool once = false)
{
	while (true) {

		if (!g_gui->rendering)
			continue;

		g_render->begin();
		g_render->push_dpi_scale(1.f);

		if (g_cs2->m_initilization)
		{

			g_cs2->local_player = Interfaces::entity_list->get_split_screen_view_player(0);

			if (Interfaces::engine->is_connected() && Interfaces::engine->is_in_game()) {

				g_visuals->render_damage();
				g_hitmarker->run();
				g_visuals->run_present();

				std::vector<render_position> p;

				g_misc->grenade_prediction_m.lock();
				for (auto& it : g_misc->lines)
				{
					p.emplace_back(render_position(it.x, it.y));
				}
				g_misc->grenade_prediction_m.unlock();

				if (p.size() > 2)
					g_render->get_buffer()->poly_line(p.data(), p.size(), render_color::white(), 1);

				if (g_legit_bot->m_last_point_render.is_valid())
					g_render->circle_filled(render_position(g_legit_bot->m_last_point_render.x, g_legit_bot->m_last_point_render.y), 2, render_color::red());

				if (g_user->IsActive(xorstr_("legitbot_enabled"), xorstr_("legitbot_enabled"), 0) && g_cs2->local_player && g_user->IsActive(xorstr_("legitbot_draw_fov"), xorstr_("legitbot_draw_fov"), 0))
				{
					//auto view_field_of_view_radians = DirectX::XMConvertToRadians(g_cs2->local_player->get_controller()->desired_fov());
					auto view_field_of_view_radians = DirectX::XMConvertToRadians(g_cs2->local_player->camera_services()->get_fov());
					{
						auto aim_field_of_view_radians = DirectX::XMConvertToRadians(g_user->IsActive(xorstr_("legitbot_fov"), xorstr_("legitbot_fov"), 0) * 0.8f);
						auto radius = tan(aim_field_of_view_radians * 0.5f) / tan(view_field_of_view_radians * 0.5f) * (float)g_cs2->screen.x;
						if (radius > 0.0f)
							g_render->get_buffer()->circle(render_position(g_cs2->screen.x * 0.5f, g_cs2->screen.y * 0.5f), radius, render_color::white().override_alpha(0.75f), 1);
					}
					{
						auto aim_field_of_view_radians = DirectX::XMConvertToRadians(g_user->IsActive(xorstr_("legitbot_fov_psilent"), xorstr_("legitbot_fov_psilent"), 0) * 0.8f);
						auto radius = tan(aim_field_of_view_radians * 0.5f) / tan(view_field_of_view_radians * 0.5f) * (float)g_cs2->screen.x;
						if (radius > 0.0f)
							g_render->get_buffer()->circle(render_position(g_cs2->screen.x * 0.5f, g_cs2->screen.y * 0.5f), radius, render_color::red().override_alpha(0.75f), 1);

					}
				}

				if (g_cs2->local_player && g_cs2->local_player->is_player() && g_cs2->local_player->is_scoped() && g_user->IsActive(xorstr_("misc_remove_scope"), xorstr_("misc_disable_light"), 2))
				{
					g_render->get_buffer()->line(render_position(0, g_cs2->screen.y / 2), render_position(g_cs2->screen.x, g_cs2->screen.y / 2), render_color::black(), 1);
					g_render->get_buffer()->line(render_position(g_cs2->screen.x / 2, 0), render_position(g_cs2->screen.x / 2, g_cs2->screen.y), render_color::black(), 1);
				}

				if (g_user->IsActive(xorstr_("misc_penetration_crosshair"), xorstr_("misc_penetration_crosshair"), 0) && g_cs2->local_player && g_cs2->local_player->is_alive())
				{
					g_render->circle_filled(render_position(g_cs2->screen.x * 0.5f, g_cs2->screen.y * 0.5f) + render_position(0.5, 0.5), 2, g_cs2->can_penetration ? render_color(0, 255, 0, 255) : render_color(255, 0, 0, 255));
				}

				if (g_user->IsActive(xorstr_("misc_autopeek"), xorstr_("misc_autopeek"), 0) && g_cs2->local_player && g_cs2->local_player->is_alive())
				{
					g_render->circle_filled_3d(render_position_3d(g_movement->m_autopeek.m_old_origin.x, g_movement->m_autopeek.m_old_origin.y, g_movement->m_autopeek.m_old_origin.z), 25.f, render_color::white().override_alpha(140));
					g_render->circle_3d(render_position_3d(g_movement->m_autopeek.m_old_origin.x, g_movement->m_autopeek.m_old_origin.y, g_movement->m_autopeek.m_old_origin.z), 25.f, render_color::white());
				}
			}

			if (g_gui->m_last_moved_window != -1)
			{
				auto window = *std::find_if(g_gui->m_windows.begin(), g_gui->m_windows.end(), [&](auto& x) { return x.m_window_hash == g_gui->m_last_moved_window; });
				for (auto it = g_gui->m_windows.begin(); it != g_gui->m_windows.end();) {
					if (it->m_window_hash == g_gui->m_last_moved_window)
					{
						it = g_gui->m_windows.erase(it);
						continue;
					}

					it++;
				}

				g_gui->m_windows.insert(g_gui->m_windows.end(), window);
			}

			g_misc->notify();

			g_render->push_dpi_scale(g_gui->dpi_scale);

			g_gui->m_hovered_window = -1;

			for (auto it = g_gui->m_windows.rbegin(); it != g_gui->m_windows.rend(); it++)
			{
				if (g_gui->helper.is_hovered(g_gui->m_mouse_pos_, rect_(it->m_window_position, it->m_fully_window_size)) && g_gui->m_hovered_window == -1)
					g_gui->m_hovered_window = it->m_window_hash;
			}

			if (g_user->IsActive(xorstr_("misc_watermark"), xorstr_("misc_keybind"), 2))
			{
				auto size = render_size(160, 25);
				auto position = render_position(g_render->get_screen_size().x - 10 - size.x, 10);

				int ping = 0;

				if (Interfaces::m_network_game_service->get_network_game_client() && Interfaces::m_network_game_service->get_network_game_client()->get_net_channel2())
					ping = Interfaces::m_network_game_service->get_network_game_client()->get_net_channel2()->get_network_latency() * 1000.f;

				auto calc_text = g_render->get_font(7)->calc_text_size(13.f, FLT_MAX, FLT_MAX, tfm::format(xorstr_("| %s | ping %dms"), g_cs2->username, ping).c_str());

				size.x = 45 + 5 + 10 + calc_text.x;
				position = render_position(g_render->get_screen_size().x - 10 - size.x, 10);

				g_render->rect_filled(position, size, render_color::black(), c_render_manager::render_flags_::blur, 5.f);
				g_render->rect_filled(position, size, render_color(20, 20, 20, 150), 0, 5.f);
				g_render->add_texture(position + render_position(10, 6), render_size(30, 13), g_gui->m_texture[1]);
				g_render->add_text(tfm::format(xorstr_("| %s | ping %dms"), g_cs2->username, ping), position + render_position(45, ((25 * 0.5f) - calc_text.y * 0.5f) - 2), render_color::white(), g_render->get_font(7), 12.f);
			}

			for (int i{}; i < 256; i++)
			{
				if (g_input_system->get_pressed_key(i))
					g_gui->buttons[i].pressed_ = !g_gui->buttons[i].pressed_;

				if (g_input_system->get_on_pressed_key(i))
					g_gui->buttons[i].on_pressed_ = !g_gui->buttons[i].on_pressed_;

				bool held = g_gui->buttons[i].hold_;

				g_gui->buttons[i].hold_ = g_input_system->get_hold_key(i);

				if (held != g_gui->buttons[i].hold_ && g_gui->buttons[i].hold_)
				{
					g_gui->m_pressed_mouse_pos_ = g_gui->m_mouse_pos_;
				}
			}

			for (auto& window : g_gui->m_windows) {

				g_gui->m_current_window = window.m_window_hash;

				if (window.m_window_hash == FNV32("Keybind"))
				{
					draw_keybind();
				}
				else if (window.m_window_hash == FNV32("Chat")) {
					draw_chat();
				}
				else if (window.m_window_hash == FNV32("Spectators")) {
					g_misc->spectators();
				}
				else if (window.m_window_hash == FNV32("Menu")) {
					g_gui->present();
				}
				else if (window.m_window_hash == FNV32("Rapid")) {

					g_gui->animation[FNV32("Rapid")].run(window.m_open || g_cs2->m_should_rapid);

					g_render->push_override_alpha(g_gui->animation[FNV32("Rapid")].base);

					auto position = window.m_window_position + render_position(20, 20);
					g_render->circle_filled(position, 20.f, render_color::black());

					float delta = 0.f;

					if (Interfaces::engine && Interfaces::engine->is_connected() && Interfaces::engine->is_in_game()) {

						delta = 1.f - ((g_cs2->start_time - Interfaces::globals->global_storage.curtime) / g_cs2->cycle_time);

						if (Interfaces::globals->global_storage.curtime >= g_cs2->start_time) {
							delta = 1.f;
						}
					}

					g_render->arc_line(render_position(position.x, position.y + 20), 270, 360 * delta, 20.f, render_color::red(), 3.f);

					g_render->add_text(std::to_string(g_cs2->rapid_fire_shoots), render_position(position.x - 2 - (g_render->get_font(1)->calc_text_size(16.f, FLT_MAX, FLT_MAX, std::to_string(g_cs2->rapid_fire_shoots).c_str()).x / 2), position.y - 10), render_color::white(), g_render->get_font(1), 16.f);

					g_render->pop_override_alpha();
				}

				g_gui->m_current_window = -1;
			}

			g_gui->update_windows();

			g_input_system->reset_delta();

			g_hotkey->update();

			g_gui->reset_buttons();
			g_gui->input_character_queue.clear();
		}

		render_cloud();

		g_render->pop_dpi_scale();
		g_render->end();
		g_gui->rendering = false;

		if (once)
			break;
	}
}

bool once = false;

long __fastcall hooks::swap_chain_present::hook(IDXGISwapChain* swap_chain, std::uint32_t sync_interval, std::uint32_t flags)
{
	if (!g_d3d11_helper->get_device())
	{
		g_d3d11_helper->set_swapchain(swap_chain);
		g_d3d11_helper->create_render_target();

		window_procedure_original = (WNDPROC)SetWindowLongPtr(g_d3d11_helper->get_window(), GWLP_WNDPROC, (LONG_PTR)window_procedure::hook);

		RECT rect = { 0, 0, 0, 0 };
		::GetClientRect(g_d3d11_helper->get_window(), &rect);

		auto size = render_size((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));

		g_gui->dpi_scale = 1.0f;

		if (size.x > 1920 && size.y > 1080)
			g_gui->dpi_scale = 1.5f;

		g_render = new c_render_manager(g_d3d11_helper->get_device(), g_d3d11_helper->get_context(), render_size((float)(rect.right - rect.left), (float)(rect.bottom - rect.top)), 10);
		g_cs2->screen = vector_2d(g_render->get_screen_size().x, g_render->get_screen_size().y);
		g_render->push_font(g_render->get_manager()->add_font_mem(Inter, sizeof(Inter), 15.f, false, false, util::draw::GLYPH_RANGE_CYRILLIC, util::draw::RASTERIZER_FLAGS::NO_HINTING));
		g_render->push_font(g_render->get_manager()->add_font_mem(Inter, sizeof(Inter), 15.f, false, false, util::draw::GLYPH_RANGE_CYRILLIC));
		g_render->push_font(g_render->get_manager()->add_font_mem(Inter, sizeof(Inter), 15.f, false, false, util::draw::GLYPH_RANGE_CYRILLIC));
		g_render->push_font(g_render->get_manager()->add_font_mem(Inter, sizeof(Inter), 15.f, false, true, util::draw::GLYPH_RANGE_CYRILLIC));
		g_render->push_font(g_render->get_manager()->add_font_mem(Inter, sizeof(Inter), 15.f, false, false, util::draw::GLYPH_RANGE_CYRILLIC));
		g_render->push_font(g_render->get_manager()->add_font_mem(weapons_font, sizeof(weapons_font), 15.f, false, false));
		g_render->push_font(g_render->get_manager()->add_font_mem(pixel_font, sizeof(pixel_font), 15.f, false, false, util::draw::GLYPH_RANGE_CYRILLIC));
		g_render->push_font(g_render->get_manager()->add_font_mem(work_sans, sizeof(work_sans), 12.f, false, false, util::draw::GLYPH_RANGE_CYRILLIC));
		g_render->push_font(g_render->get_manager()->add_font_mem(Verdana_ttf, sizeof(Verdana_ttf), 15.f, false, false, util::draw::GLYPH_RANGE_CYRILLIC));
		g_gui->m_texture[0] = g_render->create_texture({ shunk, shunk + sizeof(shunk) });
		g_gui->m_texture[1] = g_render->create_texture({ logo, logo + sizeof(logo) });
		g_gui->m_texture[2] = g_render->create_texture({ solid_share, solid_share + sizeof(solid_share) });
		g_gui->m_texture[3] = g_render->create_texture({ solar_peng, solar_peng + sizeof(solar_peng) });
		g_gui->m_texture[4] = g_render->create_texture({ solar_user, solar_user + sizeof(solar_user) });
		g_gui->m_texture[5] = g_render->create_texture({ tabler_trash, tabler_trash + sizeof(tabler_trash) });
		g_gui->m_texture[6] = g_render->create_texture({ mdi_gear_png, mdi_gear_png + sizeof(mdi_gear_png) });
		g_gui->m_texture[7] = g_render->create_texture({ pizda2_png, pizda2_png + sizeof(pizda2_png) });
		g_gui->m_texture[8] = g_render->create_texture({ pizda3_png, pizda3_png + sizeof(pizda3_png) });
		g_gui->m_texture[9] = g_render->create_texture({ cross_image, cross_image + sizeof(cross_image) });
		g_gui->setup();
		//std::thread(rendering).detach();
	}

	if (g_user->textures_[g_user->username_] == -1 && !g_user->avatar.empty()) {
		g_user->textures_[g_user->username_] = g_render->create_texture(g_user->avatar);
	}

	g_input_system->wrap_mouse_move(g_d3d11_helper->get_window());

	RECT rect = { 0, 0, 0, 0 };
	::GetClientRect(g_d3d11_helper->get_window(), &rect);
	g_render->update_screen_size(render_size((float)(rect.right - rect.left), (float)(rect.bottom - rect.top)));
	g_cs2->screen = vector_2d(g_render->get_screen_size().x, g_render->get_screen_size().y);

	if (!g_gui->rendering)
		g_render->m_render_timer.tick();

	g_gui->rendering = true;

	rendering(true);

	g_visuals->chams_visible = g_user->IsActive(xorstr_("chams_visible"), xorstr_("chams_visible"), 0);
	g_visuals->chams_invisible = g_user->IsActive(xorstr_("chams_invisible"), xorstr_("chams_invisible"), 0);
	g_visuals->attachment_chams = g_user->IsActive(xorstr_("attachment_chams"), xorstr_("attachment_chams"), 0);
	g_visuals->chams_type = g_user->IsActive(xorstr_("chams_type"), xorstr_("chams_type"), 0);
	g_visuals->chams_visible_clr = g_user->GetConfig()[xorstr_("chams_visible_color")];
	g_visuals->chams_invisible_clr = g_user->GetConfig()[xorstr_("chams_invisible_color")];
	g_visuals->attachment_chams_clr = g_user->GetConfig()[xorstr_("attachment_chams_color")];
	g_visuals->m_flags[0] = g_user->IsActive(xorstr_("esp_flags_bomb"), xorstr_("esp_flags_bomb"), 0);
	g_visuals->m_flags[1] = g_user->IsActive(xorstr_("esp_flags_kits"), xorstr_("esp_flags_bomb"), 1);
	g_visuals->m_flags[2] = g_user->IsActive(xorstr_("esp_flags_armor"), xorstr_("esp_flags_bomb"), 2);
	g_visuals->m_flags[3] = g_user->IsActive(xorstr_("esp_flags_flashed"), xorstr_("esp_flags_bomb"), 3);
	g_visuals->m_flags[4] = g_user->IsActive(xorstr_("esp_flags_zeus"), xorstr_("esp_flags_bomb"), 4);
	g_visuals->m_flags[5] = g_user->IsActive(xorstr_("esp_flags_defuser"), xorstr_("esp_flags_bomb"), 5);
	g_lagcompensation->level = g_user->IsActive(xorstr_("ragebot_track"), xorstr_("ragebot_track"), 0);
	g_cs2->m_disable_light = g_user->IsActive(xorstr_("misc_disable_light"), xorstr_("misc_disable_light"), 0);
	g_ragebot->setup_config();

	g_d3d11_helper->set_render_targets();
	g_render->get_manager()->draw();

	return swap_chain_present_original(swap_chain, sync_interval, flags);
}

HRESULT __fastcall hooks::swap_chain_resize_buffers::hook(IDXGISwapChain* swap_chain, std::uint32_t buffer_count, std::uint32_t width, std::uint32_t height, DXGI_FORMAT new_format, std::uint32_t swap_chain_flags)
{
	g_d3d11_helper->cleanup_render_target();
	HRESULT hr = swap_chain_resize_buffers_original(swap_chain, buffer_count, width, height, new_format, swap_chain_flags);
	g_d3d11_helper->set_swapchain(swap_chain);

	g_d3d11_helper->create_render_target();
	g_d3d11_helper->set_render_targets();

	DXGI_SWAP_CHAIN_DESC desc{};
	swap_chain->GetDesc(&desc);

	g_render->update_screen_size(render_size(desc.BufferDesc.Width, desc.BufferDesc.Height));
	g_cs2->screen = vector_2d(desc.BufferDesc.Width, desc.BufferDesc.Height);

	return hr;
}

HRESULT __fastcall hooks::swap_chain_create::hook(IDXGIFactory* swap_chain, void* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain)
{
 	return swap_chain_create_original(swap_chain, pDevice, pDesc, ppSwapChain);
}

int get_weapon_group2()
{
	auto weapon = g_cs2->local_player->get_weapon_active();

	if (!weapon)
		return -1;

	auto econ = weapon->get_econ_view_item();

	if (!econ)
		return -1;

	int index = econ->item_index();

	if (weapon->is_rifle())
		return 1;
	else if (index == weapon_revolver)
		return 3;
	else if (index == weapon_deagle)
		return 4;
	else if (index == weapon_ssg08)
		return 5;
	else if (index == weapon_awp)
		return 6;
	else if (index == weapon_g3sg1 || index == weapon_scar20)
		return 7;
	else if (weapon->is_pistols())
		return 0;
	else if (!weapon->is_knife() && !weapon->is_grenade())
		return 2;

	return -1;
}

LRESULT __stdcall hooks::window_procedure::hook(HWND hwnd, std::uint32_t message, WPARAM wparam, LPARAM lparam)
{
	if (g_cs2->m_initilization)
	{
		g_input_system->wrap_input(message, wparam);
		g_input_system->wrap_mouse_input(message, wparam);

		if (message == WM_MOUSEWHEEL)
			g_input_system->wrap_mouse_scrolling((GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA));

		if (message == WM_KEYUP && (wparam == VK_INSERT || wparam == VK_DELETE)) {
			g_gui->draw_ = !g_gui->draw_;

			//if (g_gui->draw_ && g_cs2->local_player && g_cs2->local_player->get_weapon_active() && !g_cs2->local_player->get_weapon_active()->is_grenade() && !g_cs2->local_player->get_weapon_active()->is_knife()) {
			//	g_user->GetConfig()[xorstr_("group_select")] = get_weapon_group2();
			//}

			if (relative_mouse_mode_original)
				relative_mouse_mode_original(Interfaces::input_system, g_gui->draw_ ? false : g_cs2->RelativeLastValue);
		}

		if (g_gui->is_open_menu())
		{

			if (message == WM_CHAR) {
				std::string input;
				input.push_back(wparam);
				wchar_t wch = 0;
				::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, input.data(), 1, &wch, 1);
				g_gui->input_character_queue.push_back(wch);
			}

			switch (message)
			{
			case WM_MOUSEMOVE:
			case WM_NCMOUSEMOVE:
			case WM_MOUSELEAVE:
			case WM_NCMOUSELEAVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONDBLCLK:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONDBLCLK:
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_XBUTTONUP:
			case WM_MOUSEWHEEL:
			case WM_MOUSEHWHEEL:
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_SETFOCUS:
			case WM_KILLFOCUS:
			case WM_CHAR:
			case WM_DEVICECHANGE:
				return true;
			}
		}
	}

	return CallWindowProc(window_procedure_original, hwnd, message, wparam, lparam);
}