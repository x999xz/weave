// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

c_cs_player_controller* c_game_event_helper::get_player_controller()
{
    if (!event)
        return nullptr;

    int controller_id{};

    c_buffer buffer;
    buffer.name = "userid";

    event->get_controller_id(controller_id, &buffer);

    if (controller_id == -1)
        return nullptr;

    return Interfaces::entity_list->get_controller(controller_id + 1);
}

c_cs_player_controller* c_game_event_helper::get_attacker_controller()
{
    if (!event)
        return nullptr;

    int controller_id{};

    c_buffer buffer;
    buffer.name = "attacker";

    event->get_controller_id(controller_id, &buffer);

    if (controller_id == -1)
        return nullptr;

    return Interfaces::entity_list->get_controller(controller_id + 1);
}

int c_game_event_helper::get_damage()
{
    if (!event)
        return -1;

    return event->get_int2("dmg_health", false);
}

int c_game_event_helper::get_health()
{
    if (!event)
        return -1;

    c_buffer buffer;
    buffer.name = "health";

    return event->get_int(&buffer);
}

int c_game_event::get_int2(const char* name, bool unk)
{
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 56 48 83 EC 30 48 8B 01 41 8B F0 4C 8B F1 41 B0 01 48 8D 4C 24 20 48 8B DA 48 8B 78" );
    return pattern.as<int(__thiscall*)(void*, const char*, bool)>()(this, name, unk);
}

float c_game_event::get_float2(const char* name, bool unk)
{
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B 01 48 8B F1 0F 29 74 24 30 48 8D 4C 24 20 41" );
    return pattern.as<float(__thiscall*)(void*, const char*, bool)>()(this, name, unk);
}
