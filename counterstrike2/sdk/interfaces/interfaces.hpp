#pragma once

#include "../math/color_t.hpp"

#include "virtual.hpp"

#include "i_convars.hpp"
#include "i_scene_debug_overlay.hpp"
#include "i_client.hpp"
#include "i_csgo_input.hpp"
#include "i_engine_client.hpp"
#include "i_entity_list.hpp"
#include "i_input_system.hpp"
#include "i_schema_system.hpp"
#include "i_engine_trace.hpp"
#include "c_resource_system.hpp"
#include "i_pvs_manager.h"
#include "c_localize.h"
#include "../classes/c_render_game_system.hpp"
#include "../classes/c_client_mode.hpp"
#include "../classes/global_vars.hpp"
#include "../classes/game_event_manager.hpp"
#include "../classes/game_event_listener.hpp"
#include "../classes/c_econ_item_system.hpp"
#include "../classes/c_prediction.hpp"
#include "../steam/steam_api.h"
#include "../classes/c_game_particle_manager_system.hpp"
#include "../classes/c_particle_manager.h"
#include "../classes/c_network_game_client.hpp"
#include "../classes/c_cs_player_inventory.hpp"
#include "../classes/c_cs_inventory_manager.hpp"
#include "i_network_game_service.hpp"
#include "../classes/c_base_file_system.hpp"
#include "../classes/c_cs_game_rules.h"
#include "../classes/c_fx_queue_manager_impl.h"
#include "../classes/c_scene_view_debug_overlays.h"
#include "../classes/c_swap_chain.h"
#include "../classes/c_material_system2_app_system_dict.h"
#include "../classes/c_scene_utils.h"
#include "../classes/c_command_line.h"
#include "../classes/c_application.h"
#include "../classes/c_panorama_ui_engine2.h"
#include "c_game_ui_service.h"
#include "../classes/c_network_messages.h"
#include "c_memalloc.h"

#include <span>

class CUIPanel
{
public:
	char pad[0x8];
	std::uintptr_t* panel_2d;
	const char* GetId;
};

class PanelListNode {
	void* unk0, * unk1;
public:
	CUIPanel* uiPanel;
private:
	void* unk2;
};

class CUIEngineSource2
{
public:
	void RunScript(std::uintptr_t* panel, const char* entireJSCode, const char* pathToXMLContext, void* unk)
	{
		CALL_VIRTUAL(void, 81, this, panel, entireJSCode, pathToXMLContext, unk);
	}

	template<uint32_t size>
	auto GetPanelList() {
		auto data = *reinterpret_cast<PanelListNode**>(std::uintptr_t(this) + 0xf0);
		return std::span{ data, size };
	}
};

class CPanoramaUIEngine
{
public:
	CUIEngineSource2* AccessUIEngine()
	{
		return CALL_VIRTUAL(CUIEngineSource2*, 13, this);
	}
};

namespace Interfaces {
	inline ccvar* convars = nullptr;
	inline i_client* client = nullptr;
	inline i_csgo_input* csgo_input = nullptr;
	inline i_engine_client* engine = nullptr;
	inline i_entity_list* entity_list = nullptr;
	inline c_input_sys* input_system = nullptr;
	inline i_schema_system* schema_system = nullptr;
	inline i_trace* trace = nullptr;
	inline c_global_vars* globals = nullptr;
	inline c_resource_system* resource_system = nullptr;
	inline i_material_system* material_system = nullptr;
	inline game_event_manager* event_manager = nullptr;
	inline c_pvs_manager* pvs_manager = nullptr;
	inline c_econ_item_system* econ_item_system = nullptr;
	inline ISteamClient* m_steam_client = nullptr;
	inline ISteamGameCoordinator* m_steam_game_coordinator = nullptr;
	inline ISteamUser* m_steam_user = nullptr;
	inline ISteamFriends* m_steam_friends = nullptr;
	inline ISteamUtils* m_steam_utils = nullptr;
	inline c_prediction* m_prediction = nullptr;
	inline c_client_mode* m_client_mode = nullptr;
	inline c_render_game_system* m_render_game_system = nullptr;
	inline c_game_particle_manager_system* m_game_particle_manager_system = nullptr;
	inline c_particle_manager* m_particle_manager = nullptr;
	inline c_network_game_client* m_network_game_client = nullptr;
	inline i_network_game_service* m_network_game_service = nullptr;
	inline c_cs_inventory_manager* m_cs_inventory_manager = nullptr;
	inline c_gc_client_system* m_gc_client = nullptr;
	inline c_base_file_system* m_base_file_system = nullptr;
	inline c_localize* m_localize = nullptr;
	inline c_cs_game_rules* m_game_rules = nullptr;
	inline c_fx_queue_manager_impl* m_fx_queue_manager = nullptr;
	inline c_scene_view_debug_overlays* m_scene_view_debug_overlays = nullptr;
	inline c_scene_utils* m_scene_utils = nullptr;
	inline c_command_line* m_command_line = nullptr;
	inline c_application* m_application = nullptr;
	inline c_panorama_ui_engine2* panorama_ui_engine2 = nullptr;
	inline c_game_ui_service* m_game_ui_service = nullptr;
	inline CPanoramaUIEngine* m_panorama_engine = nullptr;;
	inline c_network_messages* m_network_messages = nullptr;
	inline c_memalloc* m_mem_alloc = nullptr;

	extern bool initialize();
	template<typename T>
	extern T* get_interface(std::uint64_t module, const char* interface_name, bool hash = false, std::uint64_t hash_interface = 0);
}