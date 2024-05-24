// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"
#include "../../hooks/hooks.hpp"

c_weapon_cs_base* c_cs_player_pawn::get_weapon_active()
{
    auto service = weapon_services();

    if (!service)
        return nullptr;

    auto handle = service->m_hactive_weapon();

    if (!handle.is_valid())
        return nullptr;

    auto weapon = reinterpret_cast<c_weapon_cs_base*>(Interfaces::entity_list->get_entity(handle.get_index()));

    if (!weapon)
        return nullptr;

    if (!weapon->find_class(HASH("C_CSWeaponBase")))
        return nullptr;

    return weapon;
}

c_cs_player_controller* c_cs_player_pawn::get_controller()
{
    if (!handle_controller().is_valid())
        return nullptr;

    int index = handle_controller().get_index();
    return Interfaces::entity_list->get_controller(index);
}

void c_cs_player_pawn::get_bone_position(std::uint32_t bone_index, vector& position, vector& rotation)
{
    using function_t = std::int64_t(__fastcall*)(c_cs_player_pawn*, std::uint32_t, vector*, vector*);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4D 8B F1" );
    pattern.as<function_t>()(this, bone_index, &position, &rotation);
}

vector_2d c_cs_player_pawn::world_space_center()
{
    auto sign = g_utils->get_virtual(this, 72);
    vector out;
    auto ret = reinterpret_cast<vector(__thiscall*)(c_cs_player_pawn*, vector*)>(sign)(this, &out);
    return {};
}

bool c_cs_player_pawn::is_enemy(c_cs_player_pawn* local)
{
    auto local_player = local;

    if (!local)
        local_player = g_cs2->local_player;

    if (!local_player)
        return false;

    if (this == local_player)
        return false;

    if (g_cs2->mp_teammates_are_enemies->GetValue<bool>())
        return true;

    if (team_num() == local_player->team_num())
        return false;

    return true;
}

bool c_cs_player_pawn::has_c4()
{
    return this->weapon_services() && this->weapon_services()->weapon_owns_this_type("weapon_c4");
}

bool c_cs_player_pawn::is_smoke_view()
{
    if (!collision_property())
        return false;

    //48 83 EC 28 45 33 C0 E8

    auto obb_min = collision_property()->mins();
    auto obb_max = collision_property()->maxs();
    auto obb_center = (obb_max + obb_min) / 2;
    auto obb_position = obb_center + game_scene_node()->abs_origin();

    auto eye_position = get_eye_angle();

    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 83 EC 28 45 33 C0 E8" );

    return pattern.as<bool(__fastcall*)(vector&, vector&)>()(eye_position, obb_position);
}

bool c_cs_player_pawn::is_attachment()
{
    if (game_scene_node()->parent())
    {
        auto owner = game_scene_node()->parent()->owner();
        if (game_scene_node()->parent()->owner() && game_scene_node()->parent()->owner() == g_cs2->local_player)
        {
            return true;
        }
    }

    return false;
}

int c_cs_player_pawn::get_bone_index(const char* name)
{
    using function_t = int(__fastcall*)(void*, const char*);
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "E8 ?? ?? ?? ?? 33 DB 89 47 08" ).get_absolute_address(1,0);
    return pattern.as<function_t>()(this, name);
}

int c_cs_player_pawn::get_lerp_tick(int player_tick_count)
{
    unsigned int tick = -1, tick2 = -1, tick3 = -1;
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 56 48 83 EC 70 48" );
    pattern.as<void(__fastcall*)(c_game_scene_node*, unsigned int*, unsigned int*, unsigned int*, int*)>()(game_scene_node(), &tick, &tick2, &tick3, &player_tick_count);
    return tick;
}