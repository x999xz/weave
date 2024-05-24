// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

c_cs_player_pawn* c_cs_player_controller::get_player_pawn()
{
    if (!handle_player_pawn().is_valid())
        return nullptr;

    int index = handle_player_pawn().get_index();
    return Interfaces::entity_list->get_entity(index);
}

c_cs_player_pawn* c_cs_player_controller::get_observer_pawn()
{
    if (!handle_observer_pawn().is_valid())
        return nullptr;

    int index = handle_observer_pawn().get_index();
    return Interfaces::entity_list->get_entity(index);
}