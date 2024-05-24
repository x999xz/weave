// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "interfaces.hpp"

#include "../../signatures.hpp"
#include "../../utilities/utilities.hpp"
#include "../../utilities/debug_console/debug.hpp"
#include "../../utilities/hash.h"

template<typename T>
T* Interfaces::get_interface(std::uint64_t module, const char* interface_name, bool hash, std::uint64_t hash_interface)
{
	if (!interface_name)
		return nullptr;

	if(!module)
		return nullptr;

	auto create_interface = g_utils->get_proc_address(module, xorstr_("CreateInterface"));

	if (!create_interface)
		return nullptr;


	using interface_callback_fn = void* (__cdecl*)();

	typedef struct _interface_reg_t
	{
		interface_callback_fn callback;
		const char* name;
		_interface_reg_t* flink;
	} interface_reg_t;

	interface_reg_t* interface_list = *reinterpret_cast<interface_reg_t**>(g_utils->resolve_rip(create_interface, 3));

	if (!interface_list)
		return nullptr;


	for (interface_reg_t* it = interface_list; it; it = it->flink)
	{
		if (hash)
		{
			if (HASH_RT(it->name) == hash_interface)
				return reinterpret_cast<T*>(it->callback);
		}
		else {
			if (!strcmp(it->name, interface_name))
				return reinterpret_cast<T*>(it->callback());
		}

	}

	return nullptr;
}

#include <fstream>
#include "../../Logging.h"

bool Interfaces::initialize()
{
	add_trace(__PRETTY_FUNCTION__);
	auto p = get_interface<std::uintptr_t>(g_cs2->m_module_system.get_scenesystem(), xorstr_("SceneUtils_001"));
	m_scene_utils = get_interface<c_scene_utils>(g_cs2->m_module_system.get_scenesystem(), xorstr_("SceneUtils_001"));
	m_application = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 05 ?? ?? ?? ?? 48 8B 00 48 8B 0D ?? ?? ?? ?? FF 90 ?? ?? ?? ?? 0F B6 C0 85 C0 74 0B 8B 44 24 34 83 C8 02" ).get_absolute_address( 3, 0 ).as<c_application*>( ); //g_cs2->m_patterns[FNV32("application")].cast<c_application*>();
	m_command_line = reinterpret_cast<c_command_line * (__fastcall*)()>(g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("CommandLine")))();
	m_mem_alloc = *(c_memalloc**)g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), "g_pMemAlloc");

	m_game_particle_manager_system = 
		g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "E8 ? ? ? ? 40 80 FF 03" ).get_absolute_address( 1, 0 ).as<c_game_particle_manager_system * (__cdecl*)()>()();

	csgo_input = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 8B DF" ).get_absolute_address( 3, 0 ).cast<i_csgo_input*>();
	pvs_manager = g_utils->pattern_scan(g_cs2->m_module_system.get_engine2(), "48 8D 0D ? ? ? ? 33 D2 FF 50").get_absolute_address(3, 0).as<c_pvs_manager*>();
	entity_list = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ? ? ? ? 48 8D 94 24 50 02 00 00 33 DB" ).get_absolute_address( 3, 0 ).cast<i_entity_list*>();
	trace = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ?? ?? ?? ?? 48 8B D7 E8 ?? ?? ?? ?? 4C 8B E0" ).get_absolute_address( 3, 0 ).cast<i_trace*>();
	event_manager = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? 48 85 C9 74 2D" ).get_absolute_address( 3, 0 ).cast<game_event_manager*>();
	m_client_mode = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "4C 8D 35 ?? ?? ?? ?? 33 DB 48 8D 2D" ).get_absolute_address( 3, 0 ).cast<c_client_mode*>();
	m_render_game_system = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ?? ?? ?? ?? 48 8D 5E 10 48 89 44 24 28" ).get_absolute_address( 3, 0 ).cast<c_render_game_system*>(); // xref: pointer -> RenderGameSystem -> CViewSetup::OnRenderStart -> C:\\buildworker\\csgo_rel_win64\\build\\src\\game\\client\\view.cpp
	
	if (m_network_game_service)
		m_network_game_client = m_network_game_service->get_network_game_client();

	if (m_network_game_client)
		globals = m_network_game_client->get_global_vars();

	printf("%llx \n", pvs_manager);

	// g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 8B DF" ).get_absolute_address( 3, 0 )

;	m_game_rules = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 84 C0 74 0D 33 C0" ).get_absolute_address( 3, 0 ).cast<c_cs_game_rules*>();
	m_fx_queue_manager = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ?? ?? ?? ?? 41 81 C9 30 1E" ).get_absolute_address( 3, 0 ).cast<c_fx_queue_manager_impl*>();
	m_scene_view_debug_overlays = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 05 ?? ?? ?? ?? 48 8B 74 24 48 48 83 C4 20" ).get_absolute_address( 3, 0 ).cast<c_scene_view_debug_overlays*>();
	m_particle_manager = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 05 ?? ?? ?? ?? 48 8B 08 48 8B 59 68" ).get_absolute_address( 3, 0 ).cast<c_particle_manager*>();

	auto inventory_manager = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8D 0D ?? ?? ?? ?? 45 33 C0 0F B7 D7 E8 ?? ?? ?? ?? 48 8B D8 48 85 C0" ).get_absolute_address( 3, 0 ).get();
	m_cs_inventory_manager = *reinterpret_cast<c_cs_inventory_manager**>(&inventory_manager);

	auto gc_client = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 05 ?? ?? ?? ?? 4C 8D 45 90 48 8B 54 24 40" ).get_absolute_address( 3, 0 ).get();
	m_gc_client = *reinterpret_cast<c_gc_client_system**>(&gc_client);
	econ_item_system = *(c_econ_item_system**)(std::uintptr_t( g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 05 ?? ?? ?? ?? 48 85 C0 75 6B" ).get_absolute_address( 3, 0 ).cast<std::uintptr_t*>()) + 0x8);

	using fn_steam_client = ISteamClient*(__cdecl*)(void);
	using tt = uint64_t(__cdecl*)(void);

	std::uint64_t steam_user = reinterpret_cast<tt>(g_utils->get_proc_address(g_cs2->m_module_system.get_steam_api64(), xorstr_("SteamAPI_GetHSteamUser")))();
	std::uint64_t steam_pipe = reinterpret_cast<tt>(g_utils->get_proc_address(g_cs2->m_module_system.get_steam_api64(), xorstr_("SteamAPI_GetHSteamPipe")))();
	m_steam_client = reinterpret_cast<fn_steam_client>(g_utils->get_proc_address(g_cs2->m_module_system.get_steam_api64(), xorstr_("SteamClient")))();
	m_steam_game_coordinator = reinterpret_cast<ISteamGameCoordinator*>(m_steam_client->GetISteamGenericInterface(steam_user, steam_pipe, xorstr_("SteamGameCoordinator001")));
	m_steam_user = m_steam_client->GetISteamUser(steam_user, steam_pipe, xorstr_("SteamUser023"));
	m_steam_friends = m_steam_client->GetISteamFriends(steam_user, steam_pipe, xorstr_("SteamFriends017"));
	m_steam_utils = m_steam_client->GetISteamUtils(steam_pipe, xorstr_("SteamUtils010"));

	if (!Interfaces::m_command_line->find("-insecure")) {
		MessageBoxA(0, "add -insecure to the game parameters in order to play", 0, 0);
		exit(0);
	}


	if (!convars ||
		!csgo_input ||
		!engine ||
		!input_system ||
		!schema_system ||
		!trace ||
		!globals ||
		!material_system ||
		!event_manager ||
		!m_steam_client ||
		!m_steam_game_coordinator ||
		!m_steam_user ||
		!m_steam_friends ||
		!m_steam_utils ||
		!m_client_mode ||
		!m_render_game_system
		|| !pvs_manager)
	{
		LogError("failed to initialize interfaces");
		return false;
	}
	LogInfo("interfaces done");
	return true;
}