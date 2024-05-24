// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "misc.h"
#include "../../utilities/dx11_helper/dx11_helper.hpp"
#include "../../renderer/render_manager.h"
#include "../../gui/gui.h"

int c_misc::setup_avatar(c_cs_player_pawn* player_pawn)
{
	auto controller = player_pawn->get_controller();

	if (!controller)
		return -1;

	auto steam_id = controller->steam_id();

	if (m_avatars_cache_.find(steam_id) != m_avatars_cache_.end() && m_avatars_cache_[steam_id] > 0)
		return m_avatars_cache_[steam_id];

	int iImage = Interfaces::m_steam_friends->GetLargeFriendAvatar(steam_id);
	if (iImage == -1)
		return -1;
	uint32 uAvatarWidth, uAvatarHeight;
	if (!Interfaces::m_steam_utils->GetImageSize(iImage, &uAvatarWidth, &uAvatarHeight))
		return -1;
	const int uImageSizeInBytes = uAvatarWidth * uAvatarHeight * 4;
	std::vector<uint8> avatar_rgba;
	avatar_rgba.resize(uImageSizeInBytes);
	if (!Interfaces::m_steam_utils->GetImageRGBA(iImage, avatar_rgba.data(), avatar_rgba.size()))
		return -1;

	m_avatars_cache_[steam_id] = g_render->create_texture_rgba(avatar_rgba, uAvatarWidth, uAvatarHeight);

	return m_avatars_cache_[steam_id];
}

void c_misc::spectators()
{
	if (!g_user->IsActive(xorstr_("misc_spectators"), xorstr_("misc_keybind"), 1))
		return;

	std::vector<c_specs> specs_temp{};

	auto local_player = g_cs2->get_localplayer();

	if (local_player && local_player->is_alive() && Interfaces::engine->is_connected() && Interfaces::engine->is_in_game())
	{
		auto handle_local = g_cs2->get_handle_entity(local_player);

		for (int i = 1; i < 32; i++)
		{
			auto controller = Interfaces::entity_list->get_controller(i);

			if (!controller)
				continue;

			if (!controller->find_class(HASH("CCSPlayerController")))
				continue;

			auto pawn = controller->get_player_pawn();

			if (!pawn)
				continue;

			if (pawn->is_alive())
				continue;

			if (pawn == local_player)
				continue;

			if (!pawn->is_player())
				continue;

			auto obs_pawn = controller->get_observer_pawn();

			if (!obs_pawn)
				continue;

			if (!obs_pawn->find_class(HASH("C_CSObserverPawn")))
				continue;

			if (pawn->flags() & 0x100)
				continue;

			auto obs_service = obs_pawn->observer_services();

			if (!obs_service)
				continue;

			if (obs_service->m_hobserver_target().get_handle() != handle_local)
				continue;

			auto name = std::string(controller->name(), 16);

			specs_temp.push_back({ name, controller->steam_id(), true, {}, setup_avatar(pawn) });
		}
	}

	for (auto it = specs_temp.begin(); it != specs_temp.end(); it++)
	{
		auto steam_id = it->steam_id;

		if (std::find_if(specs_.begin(), specs_.end(), [&](const auto& x) { return x.steam_id == steam_id; }) != specs_.end())
			continue;

		specs_.push_back(*it);
	}

	auto window = g_gui->find_window(xorstr_("Spectators"));
	bool has_visible = g_gui->is_open_menu() || specs_.size() > 0;

	if (window.has_value() && g_user->IsActive(xorstr_("misc_spectators"), xorstr_("misc_keybind"),1) && has_visible)
	{
		auto position = window.value().m_window_position;
		auto name = window.value().m_window_name;
		auto calc_text = g_render->get_font(0)->calc_text_size(13.f, FLT_MAX, FLT_MAX, name.c_str());
		auto center = position + (window.value().m_window_size / 2) - (calc_text / 2);

		float size_y = 25 * std::count_if(specs_.begin(), specs_.end(), [](const auto& x) {
			return x.m_show;
			});

		g_gui->animation_lerp[FNV32("spectators_animation_y")] = std::lerp(g_gui->animation_lerp[FNV32("spectators_animation_y")], size_y, 0.1f);

		g_render->rect_filled(position, window.value().m_window_size, render_color(20, 20, 20), c_render_manager::render_flags_::blur, 5.f, render_rounding_flags_::ROUND_RECT_TOP);
		g_render->rect_filled(position, window.value().m_window_size, render_color(13, 13, 14, 220), 0, 5.f, render_rounding_flags_::ROUND_RECT_TOP);
		g_render->add_texture(position + (window.value().m_window_size / 2) - (render_size(58 * 0.65f, 25 * 0.65f) / 2), render_size(58 * 0.65f, 25 * 0.65f), g_gui->m_texture[1]);

		g_render->set_limit(position + render_position(0, 35), render_size(window.value().m_window_size.x, g_gui->animation_lerp[FNV32("spectators_animation_y")]));
		g_render->rect_filled(position + render_position(0, 35), render_size(window.value().m_window_size.x, g_gui->animation_lerp[FNV32("spectators_animation_y")]), render_color::black().override_alpha(0.4f), 0, 3.f, render_rounding_flags_::ROUND_RECT_BOT);

		position.y += 35;

		float high_size = 200.f;
		float temp_size = 0.f;

		for (auto it = specs_.begin(); it != specs_.end();)
		{
			if (!it->m_show && it->m_animation.base <= 0.f)
			{
				it = specs_.erase(it);
				continue;
			}

			it->m_animation.run(it->m_show);
			it->m_show = std::find_if(specs_temp.begin(), specs_temp.end(), [&](const auto& x) { return x.steam_id == it->steam_id; }) != specs_temp.end();

			auto calc_text = g_render->get_font(0)->calc_text_size(11.f, FLT_MAX, FLT_MAX, it->name.c_str());

			auto size_window = 200.f + (calc_text.x - 35);

			if (size_window > high_size)
				high_size = std::max(size_window, 200.f);

			
			g_render->add_texture_circle(position + render_position(7, 2), 10, it->texture_id);
			g_render->add_text(it->name, position + render_position(32, 5), render_color::white().override_alpha(it->m_animation.base), g_render->get_font(0), 11.f);
			position.y += 25;

			it++;
		}

		g_render->get_buffer()->pop_clip_rect();

		float animation_lerp = window.value().m_window_size.x;

		animation_lerp = std::lerp(window.value().m_window_size.x, high_size, 0.1f);

		auto find = std::find_if(g_gui->m_windows.begin(), g_gui->m_windows.end(), [](gui_window window) {
			return window.m_window_name == xorstr_("Spectators");
			});

		if (find != g_gui->m_windows.end())
		{
			find->m_window_size.x = window.value().m_window_size.x = animation_lerp;
		}
	}
}