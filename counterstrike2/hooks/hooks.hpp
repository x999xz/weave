#pragma once

#include "../signatures.hpp"

#include "../utilities/dx11_helper/dx11_helper.hpp"

#include <minhook/MinHook.h>
#include "../utilities/utilities.hpp"
#include "../sdk/sdk.hpp"
#include "../feature/feature.hpp"

#include "../GUI/GUI.h"

#include <cstdint>
#include <utility>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11.h>

struct c_scene_data
{
	char pad[0x18];
	c_scene_animatable_object* scene_animatable_object;
	i_material* material;
	i_material* material2;
};

struct name_vfx
{
	const char* name1;
	const char* name2;
};

class post_processing_settings
{
public:
	char pad[0xBD];
	bool shadow;
};

class unknown
{
public:
	std::uintptr_t* get_penis()
	{
		return (std::uintptr_t*)(this + 0x310);
	}
};

class scene_view
{
public:
	char pad[0x38];
	unknown* unk_;
};

namespace hooks
{
	bool initialize();
	bool render_initilization();
	void release();

	namespace level_init
	{
		using function_t = void(__fastcall*)(void*, const char*);
		void __fastcall hook(void* client_mode, const char* new_map);
	}

	namespace level_shutdown
	{
		using function_t = void(__fastcall*)(std::uintptr_t*);
		void __fastcall hook(std::uintptr_t* unk);
	}

	namespace swap_chain_present
	{
		using function_t = HRESULT(__fastcall*)(IDXGISwapChain*, std::uint32_t, std::uint32_t);
		HRESULT __fastcall hook(IDXGISwapChain* swap_chain, std::uint32_t sync_interval, std::uint32_t flags);
	}

	namespace swap_chain_resize_buffers
	{
		using function_t = HRESULT(__fastcall*)(IDXGISwapChain*, std::uint32_t, std::uint32_t, std::uint32_t, DXGI_FORMAT, std::uint32_t);
		HRESULT __fastcall hook(IDXGISwapChain* swap_chain, std::uint32_t buffer_count, std::uint32_t width, std::uint32_t height, DXGI_FORMAT new_format, std::uint32_t swap_chain_flags);
	}

	namespace swap_chain_create
	{
		using function_t = HRESULT(__fastcall*)(IDXGIFactory*, void*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);
		HRESULT __fastcall hook(IDXGIFactory* swap_chain, void* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain);
	}

	namespace window_procedure
	{
		using function_t = LRESULT(__stdcall*)(HWND, std::uint32_t, WPARAM, LPARAM);
		LRESULT __stdcall hook(HWND hwnd, std::uint32_t message, WPARAM wparam, LPARAM lparam);
	}

	namespace draw_scene_object
	{
		using function_t = void(__fastcall*)(void*, void*, void*, int, void*, void*, void*, void*);
		void __fastcall hook(void* animtable_scene_object, void* dx11, c_scene_data* scene_data, int unknown_bool, void* scene_view, void* scene_layer, void* unknown_pointer, void* unknown);
	}

	namespace relative_mouse_mode
	{
		using function_t = void(__fastcall*)(void*, bool);
		void __fastcall hook(void* input_system, bool enabled);
	}

	namespace override_view
	{
		using function_t = void(__fastcall*)(c_client_mode*, __int64, __int64, __int64, unsigned long);
		void __fastcall hook(c_client_mode* a1, __int64 a2, __int64 a3, __int64 a4, unsigned long a5);
	}

	namespace frame_stage_notify
	{
		using function_t = void(__fastcall*)(i_client*, int);
		void __fastcall hook(i_client* client_dll, int stage);
	}

	namespace smoke_voxel_draw
	{
		using function_t = void(__fastcall*)(__int64, __int64*, int, int, __int64, __int64);
		void __fastcall hook(__int64 a1, __int64* a2, int a3, int a4, __int64 a5, __int64 a6);
	}

	namespace create_move
	{
		using function_t = void(__fastcall*)(i_csgo_input*, unsigned int, char);
		void __fastcall hook(i_csgo_input* input, unsigned int a2, char a3);
	}

	namespace verify_input
	{
		using function_t = void(__fastcall*)(i_csgo_input*, bool);
		void __fastcall hook(i_csgo_input* input, bool a2);
	}

	namespace run_command
	{
		using function_t = void(__fastcall*)(c_player_movement_services*, c_user_cmd*);
		void __fastcall hook(c_player_movement_services* movement, c_user_cmd* cmd);
	}

	namespace set_function_bool
	{
		using function_t = void(__fastcall*)(__int128*, unsigned int, std::uint32_t);
		void __fastcall hook(__int128* a1, unsigned int hash_function, std::uint32_t value);
	}

	namespace set_function_vector
	{
		using function_t = void(__fastcall*)(__int128*, unsigned int, vector_4d*);
		void __fastcall hook(__int128* a1, unsigned int hash_function, vector_4d* value);
	}

	namespace debug_info
	{
		using function_t = void(__fastcall*)(int, std::uintptr_t*);
		void __fastcall hook(int a1, std::uintptr_t* a2);
	}

	namespace get_fov
	{
		using function_t = float(__fastcall*)(c_player_camera_services*);
		float __fastcall hook(c_player_camera_services* camera);
	}

	namespace get_fov2
	{
		using function_t = float(__fastcall*)(c_player_camera_services*);
		float __fastcall hook(c_player_camera_services* camera);
	}

	namespace render_scope
	{
		using function_t = __int64(__fastcall*)(std::uintptr_t*);
		__int64 __fastcall hook(std::uintptr_t* csgo_hudscope);
	}

	namespace draw_crosshair
	{
		using function_t = bool(__fastcall*)(std::uintptr_t*);
		bool __fastcall hook(std::uintptr_t* a1);
	}

	namespace send_move_internal
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, std::uintptr_t*);
		void __fastcall hook(std::uintptr_t* a1, std::uintptr_t* a2);
	}

	namespace on_render_start
	{
		using function_t = void(__fastcall*)(c_view_render*);
		void __fastcall hook(c_view_render* view_setup);
	}

	namespace calc_viewmodel_view
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, std::uintptr_t*, vector, vector, char);
		void __fastcall hook(std::uintptr_t* a1, std::uintptr_t* a2, vector eye_position, vector eye_angle, char a5);
	}

	namespace setup_view
	{
		using function_t = void(__fastcall*)(c_view_render*, int);
		void __fastcall hook(c_view_render* view, int unk);
	}

	namespace skybox_draw_array
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, std::uintptr_t*, std::uintptr_t*, int, int, std::uintptr_t*, std::uintptr_t*);
		void __fastcall hook(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, int a4, int a5, std::uintptr_t* a6, std::uintptr_t* a7);
	}

	namespace base_draw
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, std::uintptr_t*, c_scene_data*, int a4, int a5, std::uint32_t*, std::uintptr_t*, std::uintptr_t*);
		void __fastcall hook(std::uintptr_t* a1, std::uintptr_t* a2, c_scene_data* a3, int a4, int a5, std::uint32_t* a6, std::uintptr_t* a7, std::uintptr_t* a8);
	}

	namespace ambient_occlusion_draw_array
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, std::uintptr_t*, std::uintptr_t*, int, std::uintptr_t*, std::uintptr_t*, std::uintptr_t*);
		void __fastcall hook(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, int a4, std::uintptr_t* a5, std::uintptr_t* a6, std::uintptr_t* a7);
	}

	namespace world_render
	{
		using function_t = void(__fastcall*)(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, std::uintptr_t* a4, int a5, int a6);
		void __fastcall hook(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, std::uintptr_t* a4, int a5, int a6);
	}

	namespace aggregate_draw
	{
		using function_t = void(__fastcall*)(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, int a4, std::uintptr_t* a5, std::uintptr_t* a6, std::uintptr_t* a7, std::uintptr_t* a8);
		void __fastcall hook(std::uintptr_t* a1, std::uintptr_t* a2, std::uintptr_t* a3, int a4, std::uintptr_t* a5, std::uintptr_t* a6, std::uintptr_t* a7, std::uintptr_t* a8);
	}

	namespace grenade_tracer
	{
		using function_t = void(__fastcall*)(c_base_cs_grenade* a1);
		void __fastcall hook(c_base_cs_grenade* a1);
	}

	namespace draw_processing
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, int, name_vfx*, std::uintptr_t*, std::uintptr_t*, std::uintptr_t*, int, unsigned int, int, char);
		void __fastcall hook(std::uintptr_t* a1, int a2, name_vfx* a3, std::uintptr_t* a4, std::uintptr_t* a5, std::uintptr_t* a6, int a7, unsigned int a8, int a9, char a10);
	}

	namespace post_processing
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, scene_view*, char, std::uintptr_t*, std::uintptr_t*, unsigned int, char);
		void __fastcall hook(std::uintptr_t* a1, scene_view* a2, char a3, std::uintptr_t* a4, std::uintptr_t* a5, unsigned int a6, char a7);
	}

	namespace show_legs
	{
		using function_t = bool(__fastcall*)(c_cs_player_pawn*);
		bool __fastcall hook(c_cs_player_pawn* pawn);
	}

	namespace set_model
	{
		using function_t = void(__fastcall*)(c_base_model_entity*, const char*);
		void __fastcall hook(c_base_model_entity* entity, const char* model);
	}

	namespace is_loadout_allowed
	{
		using function_t = bool(__fastcall*)(void*);
		bool __fastcall hook(void* a1);
	}

	namespace recview_message
	{
		using function_t = void(__fastcall*)(std::uintptr_t*, c_network_serialize_pb*, std::uintptr_t*, std::uint64_t*, std::uint64_t*, unsigned int, unsigned int);
		void __fastcall hook(std::uintptr_t* a1, c_network_serialize_pb* message_handle, std::uintptr_t* message, std::uint64_t* a4, std::uint64_t* a5, unsigned int a6, unsigned int a7);
	}

	namespace run_simulation
	{
		using function_t = int(__fastcall*)(__int64 prediction, __int64* container_unk, unsigned int bool_value, unsigned int tick, c_user_cmd* usercmd);
		int __fastcall hook(__int64, __int64*, unsigned int, unsigned int, c_user_cmd*);
	}
}


inline hooks::level_init::function_t level_init_original = nullptr;
inline hooks::swap_chain_present::function_t swap_chain_present_original = nullptr;
inline hooks::swap_chain_resize_buffers::function_t swap_chain_resize_buffers_original = nullptr;
inline hooks::window_procedure::function_t window_procedure_original = nullptr;
inline hooks::draw_scene_object::function_t draw_scene_object_original = nullptr;
inline hooks::level_shutdown::function_t level_shutdown_original = nullptr;
inline hooks::relative_mouse_mode::function_t relative_mouse_mode_original = nullptr;
inline hooks::override_view::function_t override_view_original = nullptr;
inline hooks::frame_stage_notify::function_t frame_stage_notify_original = nullptr;
inline hooks::smoke_voxel_draw::function_t smoke_voxel_draw_original = nullptr;
inline hooks::create_move::function_t create_move_original = nullptr;
inline hooks::run_command::function_t run_command_original = nullptr;
inline hooks::set_function_bool::function_t set_function_bool_original = nullptr;
inline hooks::set_function_vector::function_t set_function_vector_original = nullptr;
inline hooks::debug_info::function_t debug_info_original = nullptr;
inline hooks::get_fov::function_t get_fov_original = nullptr;
inline hooks::get_fov2::function_t get_fov2_original = nullptr;
inline hooks::render_scope::function_t render_scope_original = nullptr;
inline hooks::draw_crosshair::function_t draw_crosshair_original = nullptr;
inline hooks::send_move_internal::function_t send_move_internal_original = nullptr;
inline hooks::on_render_start::function_t on_render_start_original = nullptr;
inline hooks::calc_viewmodel_view::function_t calc_viewmodel_view_original = nullptr;
inline hooks::setup_view::function_t setup_view_original = nullptr;
inline hooks::skybox_draw_array::function_t skybox_draw_array_original = nullptr;
inline hooks::base_draw::function_t base_draw_original = nullptr;
inline hooks::ambient_occlusion_draw_array::function_t ambient_occlusion_draw_array_original = nullptr;
inline hooks::world_render::function_t world_render_original = nullptr;
inline hooks::aggregate_draw::function_t aggregate_draw_original = nullptr;
inline hooks::swap_chain_create::function_t swap_chain_create_original = nullptr;
inline hooks::grenade_tracer::function_t grenade_tracer_original = nullptr;
inline hooks::draw_processing::function_t draw_processing_original = nullptr;
inline hooks::post_processing::function_t post_processing_original = nullptr;
inline hooks::show_legs::function_t show_legs_original = nullptr;
inline hooks::set_model::function_t set_model_original = nullptr;
inline hooks::is_loadout_allowed::function_t is_loadout_allowed_original = nullptr;
inline hooks::recview_message::function_t recview_message_original = nullptr;
inline hooks::verify_input::function_t verify_input_original = nullptr;
inline hooks::run_simulation::function_t run_simulation_original = nullptr;

extern void __fastcall input_history(c_input_message* input_message, csgo_input_history_entry* history, bool has_attack, std::uint64_t a4, std::uint64_t a5, std::uint64_t a6);

inline decltype(&input_history) original_input_history;