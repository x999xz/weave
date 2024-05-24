#pragma once

#include "../sdk.hpp"

class c_game_scene_node;

class c_main_class_information
{
public:
	const char* designer_class;
	const char* class_;
	const char* name_class;
	void* unk;
	c_main_class_information* next_class;
};

class c_second_class_information
{
public:
	char pad[0x28];
	c_main_class_information* main_class_information;
};

class c_unkown_information
{
public:
	char pad[0x8];
	c_second_class_information* second_class_information;
	char pad2[0x10];
	const char* first_name;
	char pad3[0x10];
	int number;
};

class c_base_entity
{
public:
	int health() {
		return *(int*)(std::uintptr_t(this) + 0x334);
	}
	__forceinline int life_state() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x338 );
	};
	__forceinline int eflags() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x354 );
	};
	__forceinline int team_num() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x3CB );
	};
	__forceinline int flags() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x3D4 );
	};
	__forceinline float speed() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x3C4 );
	};
	__forceinline vector velocity() {
		return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0x3E8 );
	};
	__forceinline vector abs_velocity() {
		return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0x3D8 );
	};
	__forceinline movetype_t move_type() {
		return *reinterpret_cast<movetype_t*>(reinterpret_cast<std::uint64_t>(this) + 0x42D );
	};
	__forceinline movetype_t actual_move_type() {
		return *reinterpret_cast<movetype_t*>(reinterpret_cast<std::uint64_t>(this) + 0x42E );
	};
	__forceinline c_game_scene_node* game_scene_node() {
		return *reinterpret_cast<c_game_scene_node**>(reinterpret_cast<std::uint64_t>(this) + 0x318);
	};
	__forceinline c_collision_property* collision_property() {
		return *reinterpret_cast<c_collision_property**>(reinterpret_cast<std::uint64_t>(this) + 0x328 );
	};
	__forceinline c_handle owner_handle() {
		return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x428 );
	};
	__forceinline c_handle ground_entity() {
		return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x438 );
	};
	__forceinline float sim_time() {
		return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x398 );
	};
	__forceinline std::uint64_t& subclass_id() {
		return *reinterpret_cast< std::uint64_t* >( reinterpret_cast< std::uint64_t >( this ) + 0x360 );// g_pSchemaOffset->m_nSubclassID);
	};
public:
	bool is_alive()
	{
		return health() > 0;
	}

	bool is_base_player_weapon()
	{
		return CALL_VIRTUAL(bool, 150, this);
	}
public:
	c_skeleton_instance* get_skeleton()
	{
		return *reinterpret_cast<c_skeleton_instance**>(reinterpret_cast<std::uintptr_t>(this) + 0x318);
	}

	c_body_component_base_anim_graph* get_body_base_anim_graph()
	{
		return *reinterpret_cast<c_body_component_base_anim_graph**>(std::uintptr_t(this) + 0x38);
	}

	void set_model(const char* name);
	void update_subclass();

	const char* get_class_name()
	{
		c_unkown_information* info = get_class_information();

		if (!info->second_class_information || !info->second_class_information->main_class_information)
			return "";

		return info->second_class_information->main_class_information->name_class;
	}

	bool find_class(std::uint64_t name)
	{
		c_unkown_information* info = get_class_information();

		if (!info->second_class_information || !info->second_class_information->main_class_information)
			return false;

		for (auto _class = info->second_class_information->main_class_information; _class->next_class != nullptr; _class = _class->next_class)
		{
			if (HASH_RT(_class->name_class) == name)
				return true;
		}

		return false;
	}

	c_unkown_information* get_class_information() {
		return *(c_unkown_information**)(std::uintptr_t(this) + 0x10);
	}

	bool is_player() {
		return find_class(HASH("C_CSPlayerPawn"));
	}

	bool is_controller() {
		return find_class(HASH("CCSPlayerController"));
	}
};