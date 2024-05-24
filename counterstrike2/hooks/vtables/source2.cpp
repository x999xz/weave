// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

#include "../../Logging.h"

#include "../../sdk/classes/c_grenade_trace.h"
#include <tinyformat/tinyformat.h>
#include "../../feature/inventory_changer/inventory_changer.h"
#include "../../feature/misc/hitmarker.h"

void fix_pvs_players() {
	for (int i = 1; i <= 65; i++)
	{
		auto controller = Interfaces::entity_list->get_controller(i);

		if (!controller)
			continue;

		if (!controller->find_class(HASH("CCSPlayerController")))
			continue;

		if (controller->is_local_player_controller())
			continue;

		auto pawn = controller->get_player_pawn();

		if (!pawn || !pawn->is_alive())
			continue;

		*(bool*)(std::uintptr_t(pawn) + 0x30) = true;
	}
}

void __fastcall hooks::frame_stage_notify::hook(i_client* client_dll, int stage)
{
	g_cs2->m_latest_hook = LoggerHack::FrameStageNotify;
	g_cs2->local_player = Interfaces::entity_list->get_split_screen_view_player(0);

	if (!Interfaces::engine->is_connected() || !Interfaces::engine->is_in_game())
		return frame_stage_notify_original(client_dll, stage);

	if (!g_cs2->local_player || (!g_cs2->local_player->find_class(HASH("C_CSPlayerPawn")) && !g_cs2->local_player->find_class(HASH("C_CSObserverPawn"))))
		return frame_stage_notify_original(client_dll, stage);

	fix_pvs_players();

	frame_stage_notify_original(client_dll, stage);

	fix_pvs_players();

	switch (stage)
	{
	case frame_net_update_end:
	{
		g_lagcompensation->run();
		g_ragebot->update_cache();
	}
		break;
	case frame_render:
		g_visuals->update_damage();
		g_hitmarker->update_world_screen();
		g_visuals->run_hit_capibara();
		g_misc->bullet_impact();
		{

			for (int i{}; i < Interfaces::entity_list->get_highest_entity_index(); i++) {
				auto entity = Interfaces::entity_list->get_entity(i);

				if (!entity)
					continue;

				c_unkown_information* info = entity->get_class_information();

				if (info->second_class_information && info->second_class_information->main_class_information && info->second_class_information->main_class_information->designer_class)
				{
					if (!strcmp(info->second_class_information->main_class_information->designer_class, "env_sky")) {
						color_t clr(g_user->GetConfig()["misc_skybox_color"]);
						*(std::uint8_t*)(std::uintptr_t(entity) + 0xce1) = clr.get_red();
						*(std::uint8_t*)(std::uintptr_t(entity) + 0xce2) = clr.get_green();
						*(std::uint8_t*)(std::uintptr_t(entity) + 0xce3) = clr.get_blue();
						CALL_VIRTUAL(void, 7, entity, 1);
					}
				}

				if (g_cs2->local_player && g_cs2->local_player->is_alive() && g_user->GetConfig()[xorstr_("misc_flashbang")]) {
					g_cs2->local_player->flash_duration() = 0.f;
				}

				//if (info->second_class_information && info->second_class_information->main_class_information && info->second_class_information->main_class_information->class_)
				//{
				//	if (!strcmp(info->second_class_information->main_class_information->class_, "C_Sun")) {
				//		*(float*)(std::uintptr_t(entity) + 0xd10) = 100.f;
				//	}
				//}
			}

			if (g_cs2->local_player && g_cs2->local_player->camera_services() && g_cs2->local_player->camera_services()->m_PostProcessingVolumes().get_size() > 0) {

				for (int i{}; i < g_cs2->local_player->camera_services()->m_PostProcessingVolumes().get_size(); i++) {

					auto postprocess = reinterpret_cast<std::uintptr_t*>(Interfaces::entity_list->get_entity(g_cs2->local_player->camera_services()->m_PostProcessingVolumes().get_element(i).get_index()));

					if (postprocess) {
						if (g_user->IsActive(xorstr_("misc_dark_mode"), xorstr_("misc_blur"), 2)) {
							*(bool*)(std::uintptr_t(postprocess) + 0xd15) = 1;
							*(float*)(std::uintptr_t(postprocess) + 0xcfc) = 0.2f;
							*(float*)(std::uintptr_t(postprocess) + 0xd00) = 0.2f;
						}
						else {
							*(bool*)(std::uintptr_t(postprocess) + 0xd15) = 0;
							*(float*)(std::uintptr_t(postprocess) + 0xcfc) = 1.f;
							*(float*)(std::uintptr_t(postprocess) + 0xd00) = 1.f;
						}
					}
				}
			}
		}
		{
			auto aye = g_cs2->find_hud(xorstr_("CCSGO_HudDeathNotice"));

			if (aye) {
				*(float*)(std::uintptr_t(aye) + 0x50) = g_user->IsActive(xorstr_("misc_killfeed"), xorstr_("misc_killfeed"), 0) ? FLT_MAX : 1.5f;
			}

			static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B 71 68" );

			if (g_cs2->m_should_clear_notice) {
				pattern.as<void(__fastcall*)(std::uintptr_t)>()(std::uintptr_t(aye) - 0x28);
				g_cs2->m_should_clear_notice = false;
			}
		}
		break;
	}

	g_inventory_changer->on_frame_stage_notify(stage);

	//g_cs2->local_player = g_cs2->get_localplayer();

	g_visuals->update(stage);
}

bool __fastcall hooks::draw_crosshair::hook(std::uintptr_t* a1)
{
	g_cs2->m_latest_hook = LoggerHack::DrawCrosshair;
	if (g_user->IsActive(xorstr_("misc_force_crosshair"), xorstr_("misc_force_crosshair"),0) && g_cs2->local_player && g_cs2->local_player->is_alive() && !g_cs2->local_player->is_scoped())
		return true;

	return draw_crosshair_original(a1);
}

bool __fastcall hooks::is_loadout_allowed::hook(void* a1)
{
	g_cs2->m_latest_hook = LoggerHack::IsLoadoutAllowed;
	if (g_user->IsActive(xorstr_("misc_unlock_inventory"), xorstr_("misc_unlock_inventory"),0))
		return true;

	return is_loadout_allowed_original(a1);
}