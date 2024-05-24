// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "hooks.hpp"
#include "../Logging.h"
#include <tinyformat/tinyformat.h>
#include "../utilities/exception/weave_error.h"

#define add_hook(pattern, function, original) if (MH_CreateHook(pattern.as<void*>(), &function, reinterpret_cast<void**>(&original)) != MH_OK) \
												{ \
													weave_error(xorstr_(#function));\
													return false; \
												} \

#define init_hook() 	if (MH_Initialize() != MH_OK) \
	{ \
		weave_error(xorstr_("failed to initialize minhook")); \
		return false; \
	} \

#define enable_hooks() 	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) \
	{ \
		weave_error(xorstr_("Failed Hook Enable")); \
		return false; \
	} \

// Define the add_hook macro
//#define add_hook(pattern, function, original) \
//    if (MH_CreateHook(pattern, reinterpret_cast<LPVOID>(function), reinterpret_cast<LPVOID*>(&original)) != MH_OK) { \
//        weave_error("hooks::" #function ":hook"); \
//        return false; \
//    }

// Function to log errors or debug information
void log_debug(const char* message) {
	// Example implementation, you can replace it with your actual logging mechanism
	OutputDebugStringA(message);
}

bool hooks::render_initilization()
{
	log_debug("Initializing render hooks...\n");

	Interfaces::m_scene_utils = Interfaces::get_interface<c_scene_utils>(std::uint64_t(GetModuleHandleA("scenesystem.dll")), xorstr_("SceneUtils_001"));
	if (!Interfaces::m_scene_utils) {
		log_debug("Failed to get m_scene_utils interface.\n");
		return false; // Add error handling if the interface cannot be found
	}

	auto swap_chain = Interfaces::m_scene_utils->get_material_system2_app_system_dict();
	if (!swap_chain) {
		log_debug("Failed to get swap_chain.\n");
		return false; // Add error handling if swap_chain is nullptr
	}

	g_cs2->m_patterns[FNV32("present")] = std::uintptr_t(g_utils->get_virtual(swap_chain, 8));
	g_cs2->m_patterns[FNV32("resize_buffers")] = std::uintptr_t(g_utils->get_virtual(swap_chain, 13));

	log_debug("Patterns retrieved, initializing hooks...\n");

	init_hook();

	if (!add_hook(g_cs2->m_patterns[FNV32("present")], hooks::swap_chain_present::hook, original_swap_chain_present)) {
		log_debug("Failed to add hook for present.\n");
		return false;
	}
	if (!add_hook(g_cs2->m_patterns[FNV32("resize_buffers")], hooks::swap_chain_resize_buffers::hook, original_swap_chain_resize_buffers)) {
		log_debug("Failed to add hook for resize_buffers.\n");
		return false;
	}

	enable_hooks();
	log_debug("Render hooks initialized successfully.\n");

	return true;
}

// Declare original function pointers
decltype(&PanoramaIcon) original_swap_chain_present;
decltype(&PanoramaIcon) original_swap_chain_resize_buffers;

// Ensure the implementation of the hook functions and error handling
void weave_error(const char* message) {
	// Implement error logging or handling here
	// Example: OutputDebugStringA(message);
	log_debug(message);
}

extern void __fastcall PanoramaIcon(const char* str, std::uintptr_t* aye);

decltype(&PanoramaIcon) original_panorama_icon;

//E8 ?? ?? ?? ?? 48 8B 4F 18 48 8D 53 20
void PanoramaIcon(const char* str, std::uintptr_t* aye)
{
	g_cs2->m_latest_hook = LoggerHack::PanoramaImage;
	if(str && !strcmp(str, xorstr_("econ/status_icons/trophy_majors_finalists")))
		return original_panorama_icon(xorstr_("icons/xp/level2234"), aye);

	return original_panorama_icon(str, aye);
}

void __fastcall input_history(c_input_message* input_message, csgo_input_history_entry* history, bool has_attack, std::uint64_t a4, std::uint64_t a5, std::uint64_t a6)
{
	g_cs2->m_latest_hook = LoggerHack::InputHistory;
	if(!g_cs2->local_player || !g_cs2->local_player->is_alive())
		return  original_input_history(input_message, history, has_attack, a4, a5, a6);

	if (!g_ragebot->valid_interpolation_timing())
		return original_input_history(input_message, history, has_attack, a4, a5, a6);
	
	if(has_attack)
		original_input_history(input_message, history, has_attack, a4, a5, a6);

	return original_input_history(input_message, history, true, a4, a5, a6);
}

extern void __fastcall render_scope_shader(std::uintptr_t* a1, std::uintptr_t* a2);

decltype(&render_scope_shader) original_is_render_scope_shader;

void __fastcall render_scope_shader(std::uintptr_t* a1, std::uintptr_t* a2) {
	g_cs2->m_latest_hook = LoggerHack::RenderScope;
	if (g_user->IsActive(xorstr_("misc_remove_scope"), xorstr_("misc_disable_light"), 2))
		return;

	return original_is_render_scope_shader(a1, a2);
}

extern void __fastcall calculation_view_bob(std::uintptr_t* a1, std::uintptr_t* a2, float* a3, float* a4);

decltype(&calculation_view_bob) original_calculation_view_bob;

void __fastcall calculation_view_bob(std::uintptr_t* a1, std::uintptr_t* a2, float* a3, float* a4) {
	g_cs2->m_latest_hook = LoggerHack::CalculationViewBob;
	if (g_user->IsActive(xorstr_("misc_remove_bob"), xorstr_("misc_disable_light"), 6))
		return;

	return original_calculation_view_bob(a1, a2, a3, a4);
}

extern void __fastcall world_render_(std::uintptr_t* a1, int* a2, std::uintptr_t* a3, std::uintptr_t* a4);

decltype(&world_render_) original_world_render;

void __fastcall world_render_(std::uintptr_t* a1, int* a2, std::uintptr_t* a3, std::uintptr_t* a4) {

	if(!Interfaces::engine->is_connected() || !Interfaces::engine->is_in_game())
		return original_world_render(a1, a2, a3, a4);

	return original_world_render(a1, a2, a3, a4);
}

extern std::uintptr_t* __fastcall animation_fix(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3);

decltype(&animation_fix) original_animation_fix;

std::uintptr_t* __fastcall animation_fix(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3) {
	g_cs2->m_latest_hook = LoggerHack::AnimationFix;
	const char* is_knife = *(const char**)(std::uintptr_t(a1) + 0x8);
	if (strstr(is_knife, xorstr_("weapons/models/knife")) != nullptr)
		*(std::uintptr_t**)(std::uintptr_t(a3) + 0x30) = nullptr;
	return original_animation_fix(a1, a2, a3);
}


struct penis_cvar {
	char* name;
};

struct aye_convar {
	char pad[0x8];
	penis_cvar* p_cvar;
};


extern void* __fastcall get_cvar(aye_convar* cvar, int flags);
decltype(&get_cvar) original_get_cvar;

unsigned long long get_hash(char* txt) {
	return HASH_RT(txt);
}

int* SetCvar(aye_convar* cvar, int flags) {

	if (!cvar->p_cvar)
		return nullptr;

	if (get_hash(cvar->p_cvar->name) == HASH("lb_enable_lights") && g_cs2->m_disable_light)
	{
		int value = 0;
		return &value;
	}

	return nullptr;
}

void* __fastcall get_cvar(aye_convar* cvar, int flags) {

	g_cs2->m_latest_hook = LoggerHack::GetCvarValue;

	if(!cvar)
		return original_get_cvar(cvar, flags);

	int* cvar_ = SetCvar(cvar, flags);

	if(cvar_ == nullptr)
		return original_get_cvar(cvar, flags);

	return cvar_;
}

extern __int64 __fastcall server_seed_hash(vector angle, int tick);

decltype(&server_seed_hash) original_server_seed_hash;

__int64 __fastcall server_seed_hash(vector angle, int tick) {
	LogInfo(std::to_string(tick));
	return original_server_seed_hash(angle, tick);
}

extern void AggregateP(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, std::uintptr_t* a4);
decltype(&AggregateP) original_aggregate;
void AggregateP(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, std::uintptr_t* a4) {
	return original_aggregate(a1, a2, a3, a4);
}

extern bool __fastcall should_grenade_crosshair(c_base_cs_grenade* grenade);
decltype(&should_grenade_crosshair) original_should_grenade_crosshair;
bool __fastcall should_grenade_crosshair(c_base_cs_grenade* grenade) {
	g_cs2->m_latest_hook = LoggerHack::ShouldGrenadeCrosshair;
	if (g_user->IsActive(xorstr_("misc_remove_grenade_crosshair"), xorstr_("misc_remove_grenade_crosshair"), 0))
		return false;

	return original_should_grenade_crosshair(grenade);
}

#define pattern(a, b) g_utils->pattern_scan( a, b )
#define pattern_relative(a, b, c) g_utils->pattern_scan( a, b ).get_absolute_address(c, 0)

bool hooks::initialize()
{
	add_trace(__PRETTY_FUNCTION__);

	// g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 8B DF" ).get_absolute_address( 3, 0 )

	add_hook( g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 30 0F 29 74 24 20 48 8B D9 E8 ?? ?? ?? ?? 48 85" ), should_grenade_crosshair, original_should_grenade_crosshair);
	add_hook( g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B C4 44 89 48 20 44 89 40 18 48 89 50" ), hooks::run_simulation::hook, run_simulation_original);
	add_hook( g_utils->pattern_scan( g_cs2->m_module_system.get_scenesystem( ), "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B 71 08" ), get_cvar, original_get_cvar);
	add_hook( g_utils->pattern_scan( g_cs2->m_module_system.get_animationsystem( ), "48 89 5C 24 08 48 89 74 24 18 57 48 83 EC 20 49" ), animation_fix, original_animation_fix);
	add_hook( g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 20 55 41 56 41 57 48 81" ), calculation_view_bob, original_calculation_view_bob);
	add_hook( g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 56 57 48 83 EC 68" ), render_scope_shader, original_is_render_scope_shader);
	add_hook( g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "85 D2 0F 85 8A" ), hooks::verify_input::hook, verify_input_original);
	add_hook(pattern( g_cs2->m_module_system.get_client(), "89 54 24 10 4C 8B DC 53" ), hooks::setup_view::hook, setup_view_original );
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 48 8D 6C 24 B1" ), hooks::calc_viewmodel_view::hook, calc_viewmodel_view_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 70" ), hooks::on_render_start::hook, on_render_start_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 57 48 83 EC 20 48 8B D9 E8 ?? ?? ?? ?? 48 85" ), hooks::draw_crosshair::hook, draw_crosshair_original);
	//add_hook(g_cs2->m_patterns[FNV32("debug_info")], hooks::debug_info::hook, debug_info_original);
	add_hook( pattern( g_cs2->m_module_system.get_engine2( ), "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 66 0F 6E CA 41" ), hooks::set_function_bool::hook, set_function_bool_original);
	add_hook( pattern( g_cs2->m_module_system.get_engine2( ), "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 66 0F 6E CA 49 8B F8 66 0F 70 C9 00 8B F2 48 8B D9 45 33 C9 48 8B C1 66 66 0F 1F 84 00 00 00 00 00 66 0F 6F C1 4C 8D 15 ?? ?? ?? ?? 66 0F 76 00 0F 50 C8 85 C9 75 5A 41 FF C1 48 83 C0 10 41 83 F9 " ), hooks::set_function_vector::hook, set_function_vector_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "40 53 48 81 EC 80 00 00 00 48 8B D9 E8 ?? ?? ?? ?? 48 85" ), hooks::get_fov::hook, get_fov_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 57 48 83 EC 20 48 8B 41 30 48" ), hooks::get_fov2::hook, get_fov2_original); // 48 89 5C 24 08 57 48 83 EC 20 48 8B 41 30 48
	//add_hook(g_cs2->m_patterns[FNV32("run_command")], hooks::run_command::hook, run_command_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 40 48 8B 9C 24 88 00 00 00 4D" ), hooks::smoke_voxel_draw::hook, smoke_voxel_draw_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 56 48 83 EC 30 8B 05" ), hooks::frame_stage_notify::hook, frame_stage_notify_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "85 D2 0F 85 52" ), hooks::create_move::hook, create_move_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 18 56 48 83 EC 30 48" ), hooks::level_init::hook, level_init_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 74 24 10 57 48 83 EC 20 48 8B F9 E8 ?? ?? ?? ?? 48 8D 8F" ), hooks::level_shutdown::hook, level_shutdown_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 55 48 8D 6C 24 A9 48 81 EC B0 00 00 00 48 8B 01" ), hooks::override_view::hook, override_view_original);
	add_hook( pattern( g_cs2->m_module_system.get_scenesystem( ), "48 8B C4 48 89 50 10 55 41" ), hooks::draw_scene_object::hook, draw_scene_object_original);
	add_hook( pattern( g_cs2->m_module_system.get_input_system( ), "48 89 5C 24 ? 57 48 83 EC 20 0F B6 FA 48 8B D9 FF 15" ), hooks::relative_mouse_mode::hook, relative_mouse_mode_original);
	add_hook( pattern( g_cs2->m_module_system.get_engine2( ), "40 55 53 56 57 48 8D" ), hooks::send_move_internal::hook, send_move_internal_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "40 57 48 83 EC 40 48 8B F9 BA" ), hooks::grenade_tracer::hook, grenade_tracer_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 18 4C 89 4C 24 20 89" ), hooks::draw_processing::hook, draw_processing_original);
	//add_hook(g_cs2->m_patterns[FNV32("processing")], hooks::post_processing::hook, post_processing_original);
	add_hook(pattern( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 20 48 8B D9 E8 ?? ?? ?? ?? 48 85 C0 0F 85" ), hooks::show_legs::hook, show_legs_original);
	add_hook(pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 48 89 7C 24 20 55 48 8B EC 48 83 EC 50" ), hooks::set_model::hook, set_model_original);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 74 24 18 57 48 83 EC 20 48 8B 0D" ), hooks::is_loadout_allowed::hook, is_loadout_allowed_original);
	add_hook( pattern( g_cs2->m_module_system.get_network_system( ), "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 60 48" ), hooks::recview_message::hook, recview_message_original);
	add_hook( pattern_relative( g_cs2->m_module_system.get_client( ), "E8 ?? ?? ?? ?? 48 8B 4F 18 48 8D 53 20", 1 ), PanoramaIcon, original_panorama_icon);
	add_hook( pattern( g_cs2->m_module_system.get_client( ), "48 8B C4 4C 89 48 20 55 56 41 56 48 8D 68" ), input_history, original_input_history);
	//add_hook(sign, world_render_, original_world_render);
	
	enable_hooks();

	LogInfo("hooks initialized");

	g_event->initilization();

	LogInfo("event manager initialized");
	return true;
}

void hooks::release()
{
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}