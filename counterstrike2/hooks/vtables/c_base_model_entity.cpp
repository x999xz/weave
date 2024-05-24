// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"
#include "../../feature/inventory_changer/inventory_changer.h"

void hooks::set_model::hook(c_base_model_entity* entity, const char* model)
{
    g_cs2->m_latest_hook = LoggerHack::SetModel;
    g_inventory_changer->on_set_model(entity, model);
    return set_model_original(entity, model);
}