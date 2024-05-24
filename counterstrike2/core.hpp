#pragma once

class vector_2d;

#include "utilities/utilities.hpp"
#include "sdk/sdk.hpp"
#include "sdk/math/math.hpp"
#include "sdk/classes/c_game_particle_manager_system.hpp"
#include "sdk/classes/c_particle_manager.h"
#include "sdk/classes/c_network_serializer_pb.h"

struct seed
{
	float r1;
	float r2;
	float r3;
	float r4;
};

class c_module_system
{
public:
	std::uintptr_t get_client();
	std::uintptr_t get_server();
	std::uintptr_t get_panorama();
	std::uintptr_t get_engine2();
	std::uintptr_t get_tier0();
	std::uintptr_t get_materialsystem2();
	std::uintptr_t get_resourcesystem();
	std::uintptr_t get_schemasystem();
	std::uintptr_t get_steam_api64();
	std::uintptr_t get_gameoverlayrenderer64();
	std::uintptr_t get_scenesystem();
	std::uintptr_t get_render_system();
	std::uintptr_t get_world_render();
	std::uintptr_t get_sdl3();
	std::uintptr_t get_animationsystem();
	std::uintptr_t get_input_system();
	std::uintptr_t get_file_system();
	std::uintptr_t get_network_system();
	std::uintptr_t get_particles();
	std::uintptr_t get_localize();
};

class tracer_info
{
public:
	unsigned int effect_index = -1;
	vector* positions = nullptr;
	float* times = nullptr;
	strong_handle<c_particle_snapshot> handle_snapshot_particle{};
	particle_data particle_data_;
};

struct grenade_warning_
{
	bool draw;
	float time;
};

class messages {
public:
	std::string username;
	std::string message;
	bool sticky;
	uint64_t unixtime;
};

struct LoggerHack {
	enum InitilizationStage {
		Memory,
		LoaderData,
		LoadNetworkBalancer,
		TLSConnect,
		CreateThread,
		RenderInitilization,
		ProcessingAuth,
		SendAuthServer,
		ProcessingGetConfigs,
		SendGetConfigsServer,
		RecvAuthServer,
		RecvGetConfigsServer,
		SendPatternServer,
		RecvPatternServer,
		Module,
		ProcAddress,
		SendGetInterfaceServer,
		RecvGetInterfaceServer,
		Interfaces,
		Chams,
		Cvars,
		Other,
		ChannelSystem,
		SendGetSchemaServer,
		RecvGetSchemaServer,
		Schema,
		SendGetResourceServer,
		RecvGetResourceServer,
		Hooks,
		CreateImage
	};
	enum Hooks {
		CreateMove,
		Present,
		ResizeBuffer,
		ShouldGrenadeCrosshair,
		RunSimulation,
		GetCvarValue,
		AnimationFix,
		CalculationViewBob,
		RenderScope,
		VerifyInput,
		SetupView,
		CalcViewmodelView,
		OnRenderStart,
		DrawCrosshair,
		SetFunctionBool,
		SetFunctionVector,
		GetFOV,
		GETFOV2,
		SmokeVortexDraw,
		FrameStageNotify,
		LevelInit,
		LevelShutdown,
		OverrideView,
		DrawSceneObject,
		RelativeModeMouse,
		SendMoveInternal,
		GrenadeTrace,
		DrawProcessing,
		ShowLegs,
		SetModel,
		IsLoadoutAllowed,
		RecviewMessage,
		PanoramaImage,
		InputHistory
	};
};

class cs2
{
public:
	cs2() {};
	static void initilization_memory();
	void initilization_module();
	std::uintptr_t* find_hud(const char* str);
	unsigned int get_handle_entity(c_cs_player_pawn* entity);
	int get_colision_entity(c_cs_player_pawn* entity);
	std::uint64_t get_hash_function(const char*, std::int32_t seed, std::uint32_t seed2, std::uint32_t seed3);
	std::uint64_t get_hash_function2(const char*, std::int32_t seed);
	c_cs_player_pawn* get_localplayer();
	void on_rapidfire();
	int get_weapon_group();
	void set_flags_weave();
	void rapidfire();
	void auto_pistols();
public:
	c_user_cmd* m_current_command;
	vector eye_position{};
	c_cs_player_pawn* local_player = nullptr;
	bool random_calling = false;
	bool should_register = false;
	bool prediction = false;
	bool logged = false;
	vector_2d screen;
	vector_2d spread;

	std::uintptr_t* base_handle;

	int prediction_tick;

	std::vector<messages> messages;
	std::unordered_map<int, float> animation_lerp;
	std::unordered_map<int, float> animation_alpha;
	bool m_open_chat = false;
	std::unordered_map<int, bool> m_popup_message;
	std::unordered_map<int, vector> m_popup_position;
	bool on_round = false;

	c_network_serialize_pb* voice_data = nullptr;
	c_clc_msg_voice_data* voice_message = nullptr;

	bool did_shoot;

	vector store_angle;
	vector angle;
	vector store_cheat_impact;
	vector rapid_angle;
	bool force_rapid = false;
	int rapid_tick{};

	std::array<seed, 255> seeds;
	std::array<float, 16> world_screen;
	bool generation_seed = true;
	bool next_update = false;

	c_module_system m_module_system;

	std::unordered_map<std::uint64_t, bool> weave_users;

	std::vector<c_server_class_info> m_server_classes;

	bool m_initilization{};
	int m_initilization_stage{};
	int m_latest_hook;
	int m_current_group{};
	bool m_should_rapid{};
	float max_time{};
	float start_time{};
	float cycle_time{};
	int rapid_fire_shoots{};
	int index_id;
	int next_tick_add_shoot{};

	vector store_position[150];

	bool m_disable_light;

	vector current_angle{};

	std::string token_transfer{};
	std::string token;
	int days_left{};
	std::string username;
	std::string build;
	std::string update_log_data;
	std::string update_log_;
	bool should_quit{};
	std::uint64_t glove[5]{};
	std::string select_path_mdl_model{};
	std::vector<uint8_t> avatar_data;
	bool RelativeLastValue = false;
	bool m_should_clear_notice;
	std::string map;

	unsigned int index_effect = -1;
	float last_create_time = 0.f;
	strong_handle<c_particle_snapshot> handle_snapshot_particle{};
	particle_data particle_data_{};

	std::vector<vector> positions{};
	std::vector<float> times{};

	std::vector<tracer_info> bullets{};

	std::unordered_map<unsigned long, grenade_warning_> grenade_warning{};
	int count{};

	float field_of_view;

	bool can_penetration = false;

	std::unordered_map<std::uint32_t, std::uint64_t> m_modules{}; // [hash[name], module]
	std::unordered_map<std::uint32_t, c_address> m_patterns{};
	std::unordered_map<std::string, float> bomb_radius{};
public:
	convar* mp_teammates_are_enemies;
	convar* mp_damage_scale_ct_body;
	convar* mp_damage_scale_ct_head;
	convar* mp_damage_scale_t_body;
	convar* mp_damage_scale_t_head;
	convar* sv_penetration_type;
	convar* sv_clip_penetration_traces_to_players;
	convar* weapon_accuracy_shotgun_spread_patterns;
	convar* sv_autobunnyhopping;
	convar* sv_grenade_trajectory_prac_trailtime;
	convar* sv_maxunlag;
	convar* sv_friction;
	convar* sv_accelerate;
	convar* sv_airaccelerate;
};

inline auto g_cs2 = std::make_unique<cs2>();