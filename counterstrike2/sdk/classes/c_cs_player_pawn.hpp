#pragma once

#include "../sdk.hpp"

class c_schema_class_info
{
public:
	char pad[0x8];
	c_utl_symbol_large m_name;
};

class c_cs_player_pawn_base;

class player_info
{
public:
    char pad[0x3C8];
    std::uint32_t flags;
};


class c_cs_player_pawn : public c_cs_player_pawn_base
{
public: // virtual
    bool is_weapon()
    {
        using function_t = bool(__thiscall*)(void*);
        return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[150](this);
    }
public: // service
    __forceinline c_cs_player_bullet_services* bullet_services() {
        return *reinterpret_cast<c_cs_player_bullet_services**>(reinterpret_cast<std::uint64_t>(this) + 0x1470 );
    };
    __forceinline c_utl_vector<vector> aim_punch_cache() {
        return *reinterpret_cast<c_utl_vector<vector>*>(reinterpret_cast<std::uint64_t>(this) + 0x14F8 );
    };
public: // functions

    c_csgo_player_anim_graph_state get_csgo_anim_state()
    {
        return *reinterpret_cast<c_csgo_player_anim_graph_state*>(this + 0x1E58);
    }

    __forceinline float& flash_duration() {
        return *(float*)(std::uintptr_t(this) + 0x1364 );
    }

    c_animation_graph_instance* get_animation_graph()
    {
        using function_t = c_animation_graph_instance *(__thiscall*)(void*);
        return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[110](this);
    }

    float speed_move()
    {
        return *(float*)(std::uintptr_t(this) + 0x3D8);
    }

    vector& get_eye_angle()
	{
        //xref: C_CSPlayerPawn::HandleTaserAnimation -> UpdateAnimation aaaaaaaaa mamky ebal анимации калл меняйте нахуй
        std::uintptr_t test;
        auto ret = CALL_VIRTUAL(std::uintptr_t*, 161, this, &test);
        return *reinterpret_cast<vector*>(ret);
	}

    void update_animation()
    {
        __int64 a2{};
        __int64 a3{};
        CALL_VIRTUAL(void, 221, this, a2, a3);
    }

    void get_bone_position(std::uint32_t bone_index, vector& position, vector& rotation);

    vector_2d world_space_center();

    bool is_enemy(c_cs_player_pawn* local = nullptr);

    c_weapon_cs_base* get_weapon_active();
    c_cs_player_controller* get_controller();
    bool has_c4();
    bool is_smoke_view();
    bool is_attachment();
    int get_bone_index(const char* name);
    int get_lerp_tick(int player_tick_count);
    
};