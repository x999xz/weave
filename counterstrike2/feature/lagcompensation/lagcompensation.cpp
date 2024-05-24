// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "lagcompensation.hpp"
#include "../utilities/cloud/user.h"

void c_lagcompensation::run()
{
    for (int i{}; i <= 64; i++)
    {
        auto controller = Interfaces::entity_list->get_controller(i);

        if (!controller)
            continue;

        if (!controller->find_class(HASH("CCSPlayerController")))
            continue;

        auto player = controller->get_player_pawn();

        if (!player)
            continue;

        if (!player->is_alive())
            continue;

        if (!player->is_enemy())
            continue;

        auto skeleton = player->get_skeleton();

        if (!skeleton)
            continue;

        skeleton->calc_world_space_bones(bone_flags::FLAG_ALL_BONE_FLAGS);

        if (m_animation.find(g_cs2->get_handle_entity(player)) != m_animation.end())
        {
            //for (auto it = m_animation[g_cs2->get_handle_entity(player)].m_lag_records_.rbegin(); it != m_animation[g_cs2->get_handle_entity(player)].m_lag_records_.rend();)
            //{
            //    if (!it->record_of_bounds())
            //    {
            //        it = decltype(it){m_animation[g_cs2->get_handle_entity(player)].m_lag_records_.erase(std::next(it).base())};
            //        continue;
            //    }

            //    it = next(it);
            //}

            if (m_animation[g_cs2->get_handle_entity(player)].m_lag_records_.size() > 32)
                m_animation[g_cs2->get_handle_entity(player)].m_lag_records_.pop_back();
        }

        auto& lag_ = m_animation[g_cs2->get_handle_entity(player)];

        auto& record = lag_.m_lag_records_.emplace_front();

        record.setup(player);

        lag_.latest_record = record;
        lag_.oldest_record = lag_.m_lag_records_.back();
    }
}

struct data_info
{
    std::uint64_t tick;
    float time;
    char pad[0x24];
};
float c_lagcompensation::get_delta_time(int tick_entity)
{
    int tick_count = Interfaces::globals->global_storage.tick_count;
    float maxunlag_val = std::min(g_cs2->sv_maxunlag->GetValue<float>(), 0.2f);

    float mod_value = fmodf(maxunlag_val, 0.015625);
    float unlag_difference = maxunlag_val - mod_value;
    float mod_ticks = mod_value * 64.0;
    int unlag_ticks = (int)(float)((float)(unlag_difference * 64.0) + 0.5);

    data_info info{};
    info.tick = tick_entity;
    info.time = tick_entity * 0.015625f;

    int v20{};
    float v19{}, v21{};

    if (mod_ticks < (float)(1.0 - 0.0099999998))
    {
        v20 = tick_count - unlag_ticks;
        if (mod_ticks > 0.0099999998)
        {
            v19 = -mod_ticks;
            v21 = v19;
            if (v19 < 0.0f)
                v19 = v19 + 1.0f;
        }
        else
        {
            v19 = 0.0f;
            v21 = 0.0;
        }
    }
    else // high ping 100+
    {
        v19 = 0.0f;
        v20 = tick_count - (unlag_ticks + 1);
        v21 = 0.0;
    }

    auto v22 = v20 - 1;

    data_info v40{};

    v40.time = v19;
    if (v21 >= 0.0)
        v22 = v20;
    v40.tick = v22;
    if (v19 < (float)(1.0 - 0.0099999998))
    {
        if (v19 <= 0.0099999998)
        {
            v40.time = 0.0;
        }
    }
    else
    {
        v40.tick = v22 + 1;
        v40.time = 0.0;
    }

    auto tick = v40.tick;
    auto v24 = (float)info.tick;
    auto v38 = v40;
    int new_tick{};
    data_info v39{};

    if ((float)((float)(v24 + info.time) * 0.015625) <= 0.0)
    {

        auto cmd_tick_count = tick_entity;
        v40.tick = cmd_tick_count;
        v40.time = 0.0;
        new_tick = v40.tick;
        tick = v38.tick;
        v39 = v40;
    }
    else
    {
        new_tick = info.tick;
        v39 = info;
    }

    int v32{};
    float v30{};

    if (tick <= new_tick && (tick < new_tick || v39.time > v38.time))
    {
        auto v33 = new_tick - tick;
        v30 = v39.time - v38.time;
        if ((float)(v39.time - v38.time) < 0.0)
            v30 = v30 + 1.0;
        v32 = v33 - 1;
        if ((float)(v39.time - v38.time) >= 0.0)
            v32 = v33;
        if (v30 >= (float)(1.0 - 0.0099999998))
        {
            ++v32;
            goto LABEL_48;
        }
    LABEL_47:
        if (v30 > 0.0099999998)
            goto LABEL_49;
        goto LABEL_48;
    }
    v30 = v38.time - v39.time;
    int v31 = tick - new_tick;
    if ((float)(v38.time - v39.time) < 0.0)
        v30 = v30 + 1.0;
    v32 = v31 - 1;
    if ((float)(v38.time - v39.time) >= 0.0)
        v32 = v31;
    if (v30 < (float)(1.0 - 0.0099999998))
        goto LABEL_47;
    ++v32;
LABEL_48:
    v30 = 0.0;
LABEL_49:
    auto delta_time = (float)((float)v32 + v30) * 0.015625;

    return delta_time;
}

c_animation_table* c_lagcompensation::get_animation(c_cs_player_pawn* player_pawn)
{
    if (m_animation.find(g_cs2->get_handle_entity(player_pawn)) == m_animation.end())
        return nullptr;

    return &m_animation[g_cs2->get_handle_entity(player_pawn)];
}

void c_lagrecord::setup(c_cs_player_pawn* player_pawn)
{
    if (!player_pawn || !player_pawn->get_skeleton())
        return;

    m_simtime_ = player_pawn->sim_time();
    origin_ = player_pawn->game_scene_node()->abs_origin();
    bone_count = player_pawn->get_skeleton()->get_bone_count();
    memcpy(matrix_, player_pawn->get_skeleton()->m_modelState().get_bone_data(), bone_count * sizeof(c_bone_data));
}

void c_lagrecord::apply(c_cs_player_pawn* player_pawn, bool extrapolation)
{
    if (!player_pawn || !player_pawn->get_skeleton() || !player_pawn->get_skeleton()->m_modelState().get_bone_data())
        return;

    memcpy(backup_matrix_, player_pawn->get_skeleton()->m_modelState().get_bone_data(), player_pawn->get_skeleton()->get_bone_count() * sizeof(c_bone_data));

    memcpy(player_pawn->get_skeleton()->m_modelState().get_bone_data(), matrix_, player_pawn->get_skeleton()->get_bone_count() * sizeof(c_bone_data));

    //if (extrapolation)
    //{
    //    for (int i{}; i < 128; i++) {
    //        player_pawn->get_skeleton()->m_modelState().get_bone_data()[i].pos += ((0.017f * player_pawn->velocity()) * ((Interfaces::m_network_game_service->get_network_game_client()->get_net_channel2()->get_network_latency() * 64.f) + 0.5f));
    //    }
    //}
}

void c_lagrecord::restore(c_cs_player_pawn* player_pawn)
{
    memcpy(player_pawn->get_skeleton()->m_modelState().get_bone_data(), backup_matrix_, player_pawn->get_skeleton()->get_bone_count() * sizeof(c_bone_data));
}

bool c_lagrecord::record_of_bounds()
{
    float max_unlag = std::min(g_cs2->sv_maxunlag->GetValue<float>(), 0.2f);

    float level[3];
    level[0] = max_unlag / 3.f;
    level[1] = max_unlag / 2.f;
    level[2] = max_unlag;

    float delta_time = g_lagcompensation->get_delta_time(get_sim_time() * 64.f) + (Interfaces::m_network_game_service->get_network_game_client()->get_net_channel2()->get_network_latency() * 0.5f) + Interfaces::m_network_game_service->get_network_game_client()->get_net_channel2()->get_engine_latency();

    return std::fabsf(delta_time) < level[g_lagcompensation->level];
}