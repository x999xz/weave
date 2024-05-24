// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "core.hpp"
#include "Logging.h"
#include "../utilities/cloud/user.h"

unsigned int cs2::get_handle_entity(c_cs_player_pawn* entity)
{
	if (!entity)
		return -1;

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 85 C9 74 32 48 8B 41 10 48 85 C0 74 29 44" );
	return pattern.as<unsigned int(__fastcall*)(c_cs_player_pawn*)>()(entity);
}

int cs2::get_colision_entity(c_cs_player_pawn* entity)
{
	if (!entity)
		return -1;

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 20 48 8B D9 48 85 C9 74 24" );
	return pattern.as<int(__fastcall*)(c_cs_player_pawn*)>()(entity);
}

std::uintptr_t* cs2::find_hud(const char* str)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 55 48 83 EC 20 48 83" );
	return pattern.as<std::uintptr_t* (__fastcall*)(const char* str)>()(str);
}

void cs2::initilization_module()
{
	m_modules.insert_or_assign(FNV32("client"), g_utils->get_module_base(xorstr_(L"client.dll")));
	m_modules.insert_or_assign(FNV32("server"), g_utils->get_module_base(xorstr_(L"server.dll")));
	m_modules.insert_or_assign(FNV32("panorama"), g_utils->get_module_base(xorstr_(L"panorama.dll")));
	m_modules.insert_or_assign(FNV32("engine2"), g_utils->get_module_base(xorstr_(L"engine2.dll")));
	m_modules.insert_or_assign(FNV32("tier0"), g_utils->get_module_base(xorstr_(L"tier0.dll")));
	m_modules.insert_or_assign(FNV32("materialsystem2"), g_utils->get_module_base(xorstr_(L"materialsystem2.dll")));
	m_modules.insert_or_assign(FNV32("resourcesystem"), g_utils->get_module_base(xorstr_(L"resourcesystem.dll")));
	m_modules.insert_or_assign(FNV32("schemasystem"), g_utils->get_module_base(xorstr_(L"schemasystem.dll")));
	m_modules.insert_or_assign(FNV32("steam_api64"), g_utils->get_module_base(xorstr_(L"steam_api64.dll")));
	m_modules.insert_or_assign(FNV32("gameoverlayrenderer64"), g_utils->get_module_base(xorstr_(L"GameOverlayRenderer64.dll")));
	m_modules.insert_or_assign(FNV32("scenesystem"), g_utils->get_module_base(xorstr_(L"scenesystem.dll")));
	m_modules.insert_or_assign(FNV32("sdl3"), g_utils->get_module_base(xorstr_(L"SDL3.dll")));
	m_modules.insert_or_assign(FNV32("animationsystem"), g_utils->get_module_base(xorstr_(L"animationsystem.dll")));
	m_modules.insert_or_assign(FNV32("filesystem_stdio"), g_utils->get_module_base(xorstr_(L"filesystem_stdio.dll")));
	m_modules.insert_or_assign(FNV32("inputsystem"), g_utils->get_module_base(xorstr_(L"inputsystem.dll")));
	m_modules.insert_or_assign(FNV32("particles"), g_utils->get_module_base(xorstr_(L"particles.dll")));
	m_modules.insert_or_assign(FNV32("localize"), g_utils->get_module_base(xorstr_(L"localize.dll")));
	m_modules.insert_or_assign(FNV32("world_render"), g_utils->get_module_base(xorstr_(L"worldrenderer.dll")));
	m_modules.insert_or_assign(FNV32("render_system"), g_utils->get_module_base(xorstr_(L"rendersystemdx11.dll")));
	m_modules.insert_or_assign(FNV32("network_system"), g_utils->get_module_base(xorstr_(L"networksystem.dll")));
	LogInfo("module done");
}

std::uint64_t cs2::get_hash_function2(const char* str, std::int32_t seed)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 44 0F" );
	auto hash = pattern.as<std::uint64_t(__fastcall*)(const char*, std::int32_t)>()(str, seed);
	return hash;
}

std::uint64_t cs2::get_hash_function(const char* str, std::int32_t seed, std::uint32_t seed2, std::uint32_t seed3)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 44 0F" );

	int hash = pattern.as<std::int64_t(__fastcall*)(unsigned __int8*, std::int32_t)>()((unsigned __int8*)str, seed);
	unsigned int v65 = (seed2 * hash) ^ seed3 ^ (((seed2 * hash) ^ seed3) >> 13);
	unsigned int a2 = (seed2 * v65) ^ ((seed2 * v65) >> 15);
	return a2;
}

c_cs_player_pawn* cs2::get_localplayer() {
	c_cs_player_pawn* local_player = Interfaces::entity_list->get_split_screen_view_player(0);

	if (!local_player)
		return nullptr;

	if (local_player->is_player())
		return local_player;

	if (local_player->is_alive())
		return local_player;

	auto obs_service = local_player->observer_services();

	if (!obs_service)
		return nullptr;

	auto obs_target_handle = obs_service->m_hobserver_target();

	if (!obs_target_handle.is_valid())
		return nullptr;

	auto obs_target = Interfaces::entity_list->get_entity(obs_target_handle.get_index());

	if (!obs_target)
		return nullptr;

	return obs_target;
}

void cs2::on_rapidfire() {

	bool is_rap = g_cs2->local_player->get_weapon_active() && !g_cs2->local_player->get_weapon_active()->is_knife() && !g_cs2->local_player->get_weapon_active()->is_grenade() && !g_cs2->local_player->get_weapon_active()->is_zeus() && g_user->IsActive(xorstr_("ragebot_enable"), xorstr_("ragebot_enable"), 0) && g_user->IsActive(xorstr_("ragebot_rapidfire"), xorstr_("ragebot_rapidfire"), 0);

	if (g_cs2->local_player->get_weapon_active()) {
		if (is_rap) {
			g_cs2->m_should_rapid = true;

			if (g_cs2->local_player->get_weapon_active()->get_econ_view_item()) {
				if (g_cs2->index_id == 0) {
					g_cs2->index_id = g_cs2->local_player->get_weapon_active()->get_econ_view_item()->item_index();
				}

				int max_clip = *(int*)(std::uintptr_t(g_cs2->local_player->get_weapon_active()->get_weapon_data()) + 0x1fc);
				float cycle_time = *(float*)(std::uintptr_t(g_cs2->local_player->get_weapon_active()->get_weapon_data()) + 3140);
				float delta = Interfaces::globals->global_storage.curtime - g_cs2->local_player->weapon_services()->next_attack();

				int actualy_clip = std::min(g_cs2->local_player->get_weapon_active()->clip1(), max_clip);

				if (g_cs2->index_id != g_cs2->local_player->get_weapon_active()->get_econ_view_item()->item_index()) {
					g_cs2->start_time = Interfaces::globals->global_storage.curtime + cycle_time;
					g_cs2->cycle_time = cycle_time;
					g_cs2->rapid_fire_shoots = 0;
					g_cs2->index_id = g_cs2->local_player->get_weapon_active()->get_econ_view_item()->item_index();
				}
				else if (Interfaces::globals->global_storage.curtime > g_cs2->start_time && g_cs2->rapid_fire_shoots < actualy_clip) {
					g_cs2->rapid_fire_shoots++;
					g_cs2->start_time = Interfaces::globals->global_storage.curtime + cycle_time;
				}
			}
		}
		else {
			g_cs2->rapid_fire_shoots = 0;
			g_cs2->m_should_rapid = false;
		}
	}
}

int cs2::get_weapon_group()
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

void cs2::set_flags_weave() {
	for (int i = 1; i <= 65; i++)
	{
		auto controller = Interfaces::entity_list->get_controller(i);

		if (!controller)
			continue;

		if (!controller->find_class(HASH("CCSPlayerController")))
			continue;

		if (!controller->is_local_player_controller() && g_cs2->weave_users.find(controller->handle_player_pawn().get_handle()) == g_cs2->weave_users.end())
			continue;

		*(int*)(std::uintptr_t(controller->m_pInventoryServices()) + 0x58) = 994;
	}
}

void cs2::rapidfire() {
	if (g_user->IsActive(xorstr_("ragebot_enable"), xorstr_("ragebot_enable"), 0)) {
		if (g_cs2->m_current_command->buttons.buttonstate[0] & 1) {
			if (g_cs2->m_current_command->input_history.m_pRep) {
				for (std::int32_t i = 0; i < g_cs2->m_current_command->input_history.m_nCurrentSize; i++)
				{
					csgo_input_history_entry* tick = g_cs2->m_current_command->input_history.m_pRep->m_tElements[i];

					if (tick)
					{
						if (g_user->IsActive(xorstr_("ragebot_rapidfire"), xorstr_("ragebot_rapidfire"), 0)) {
							tick->player_tick_count = 0;
							g_cs2->m_current_command->set_attack_history(-1);
						}
					}
				}
			}
		}
		g_user->GetConfig()[xorstr_("legitbot_enabled")] = false;
	}
	else if (g_user->IsActive(xorstr_("legitbot_enabled"), xorstr_("legitbot_enabled"), 0)) {
		g_user->GetConfig()[xorstr_("ragebot_enable")] = false;
	}
}

void cs2::auto_pistols() {
	if (!g_user->IsActive(xorstr_("ragebot_enable"), xorstr_("ragebot_enable"), 0) || !g_user->IsActive(xorstr_("ragebot_rapidfire"), xorstr_("ragebot_rapidfire"), 0))
		return;

	if (!g_cs2->local_player->get_weapon_active() || g_cs2->local_player->get_weapon_active()->is_knife() || g_cs2->local_player->get_weapon_active()->is_grenade() || g_cs2->local_player->get_weapon_active()->get_econ_view_item()->item_index() == weapon_revolver || g_cs2->local_player->get_weapon_active()->get_econ_view_item()->item_index() == weapon_deagle || !g_cs2->rapid_fire_shoots)
		return;

	if (!g_cs2->rapid_tick) {
		if (g_cs2->m_current_command->buttons.buttonstate[0] & 1) {
			g_cs2->rapid_tick = 1;
		}
	}
	else {
		g_cs2->rapid_tick = 0;
		g_cs2->m_current_command->remove_button_state(1);
	}
}