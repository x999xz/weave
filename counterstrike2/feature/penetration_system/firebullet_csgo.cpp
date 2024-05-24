// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../ragebot/ragebot.hpp"

void filter_init(c_trace_filter* filter, c_cs_player_pawn* entity1, c_cs_player_pawn* entity2)
{
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B F1 49 8B F8" );

    pattern.as<void(__fastcall*)(c_trace_filter*, c_cs_player_pawn*, c_cs_player_pawn*)>()(filter, entity1, entity2);
}

float c_firebullet::get_hitgroup_damage_multiplier(c_cs_player_pawn* player, float head_shot_mult, int hit_group)
{
    float mult = 1.F;

    auto head_scale = player->team_num() == 3 ? g_cs2->mp_damage_scale_ct_head->GetValue<float>() : g_cs2->mp_damage_scale_t_head->GetValue<float>();
    auto body_scale = player->team_num() == 3 ? g_cs2->mp_damage_scale_ct_body->GetValue<float>() : g_cs2->mp_damage_scale_t_body->GetValue<float>();

    switch (hit_group)
    {
    case 1:
        mult = head_shot_mult * head_scale;
        break;
    case 3:
        mult = 1.25F * body_scale;
        break;
    case 6:
    case 7:
        mult = 0.75F * body_scale;
        break;
    default:
        mult *= body_scale;
    }
    return mult;
}

void c_firebullet::scale_damage(int hit_group, c_cs_player_pawn* player, c_weapon_cs_base_v_data* wpn_data, float& damage)
{
    if (!player || !player->find_class(HASH("C_CSPlayerPawn")))
        return;

    damage *= get_hitgroup_damage_multiplier(player, wpn_data ? wpn_data->headshot_multiplier() : 4.f, hit_group);

    if (player->armor_value() > 0 && wpn_data)
    {
        if (hit_group == 1)
        {
            if (player->item_services() && player->item_services()->m_has_helmet())
            {
                damage *= (wpn_data->armor_ratio() * 0.5f);
            }
        }
        else
        {
            damage *= (wpn_data->armor_ratio() * 0.5f);
        }
    }
}

bool c_firebullet::trace_to_exit(vector start, vector dir, vector& end, c_game_trace& enter_trace, c_game_trace& exit_trace, float step_size, float max_distance)
{
    if (!max_distance)
        return false;

    float distance = 0.f;
    int start_contents = 0;
    int current_contents = 0;

    c_trace_filter filter(0x1C3003, g_cs2->local_player, nullptr, 4);
    c_trace_filter filter2(0x1C3001, g_cs2->local_player, nullptr, 4);

    vector new_end{};

    c_ray ray{};

    while (1)
    {
        if (distance >= max_distance)
            break;

        distance += step_size;

        end = start + (dir * distance);

        new_end = end - (dir * step_size);

        if (!start_contents)
            start_contents = Interfaces::trace->point_contents(end, 0x1C3003, 7);

        current_contents = Interfaces::trace->point_contents(end, 0x1C3003, 7);

        if (!(current_contents & 0x1C3001) || (current_contents & 2) && start_contents != current_contents)
        {
            auto t = filter.flags & 201;
            filter.flags = t | 0x49;
            filter.skip_handle1 = g_cs2->get_handle_entity(g_cs2->local_player);
            filter.skip_owner_handle1 = g_cs2->get_handle_entity(Interfaces::entity_list->get_entity(g_cs2->local_player->owner_handle().get_index()));
            filter.collision1 = g_cs2->get_colision_entity(g_cs2->local_player);


            Interfaces::trace->trace_shape(&ray, end, new_end, &filter, &exit_trace);

            if (g_cs2->sv_clip_penetration_traces_to_players && g_cs2->sv_clip_penetration_traces_to_players->GetValue<bool>())
                clip_trace_to_players(end, new_end, -60.f, exit_trace.entity, filter, exit_trace);

            if (exit_trace.start_solid && exit_trace.trace_model)
            {
                filter2.flags = filter2.flags & 0x80 | 0x49;
                filter_init(&filter2, g_cs2->local_player, exit_trace.entity);

                Interfaces::trace->trace_shape(&ray, end, start, &filter2, &exit_trace);

                if (exit_trace.DidHit() && !exit_trace.start_solid)
                {
                    end = exit_trace.end_pos;
                    return true;
                }
            }
            else if (exit_trace.DidHit() && !exit_trace.start_solid && (!(exit_trace.flags & 0x800) || (enter_trace.flags & 0x800)))
            {
                vector normal = exit_trace.normal;
                if (normal.dot(dir) <= 1.f)
                {
                    end -= dir * (step_size * exit_trace.fraction);
                    return true;
                }
            }
        }

    }

    return false;
}

bool c_firebullet::handle_bullet_penetration(vector& start, vector& dir, vector& end, int& penetration_count, float penetration, float& current_damage, bool hit_grate, int enter_material, float penetration_modifier_enter, c_game_trace& trace)
{

    bool bFailedPenetrate = 0;
    bool bIsNodraw = (trace.flags & 0x800) != 0;
    bool hit_grate2 = (trace.contents & 0x2000) != 0;

    c_game_trace exit_trace{};


    if (!penetration_count && !hit_grate2 && !bIsNodraw && enter_material != 89 && enter_material != 71)
        return true;

    if (penetration <= 0.0f || penetration_count <= 0)
        return true;

    if (!trace_to_exit(trace.end_pos, dir, end, trace, exit_trace, 4.f, 90.f))
    {
        if (!(Interfaces::trace->point_contents(trace.end_pos, 0x1C3001, 7) & 0x1C3001))
            return true;
    }

    auto exit_surfaces = exit_trace.get_surfaces_data();

    if (!exit_surfaces)
        return true;

    float damage_lost_percent = 0.16f;
    float penetration_modifier = 1.f;

    if (hit_grate2 || bIsNodraw)
    {
        penetration_modifier = 1.f;
    }
    else if (enter_material == 89 || enter_material == 71)
    {
        penetration_modifier = 3.f;
        damage_lost_percent = 0.050000001f;
    }
    else
    {
        auto exit_pen_modifier = exit_surfaces->penetration_modifier;
        penetration_modifier = (exit_pen_modifier + penetration_modifier_enter) * 0.5f;
    }

    auto exit_material = exit_surfaces->material;

    if (exit_material == enter_material)
    {
        if (((enter_material - 85) & 65533) != 0)
        {
            if (enter_material == 76)
                penetration_modifier = 2.0;
        }
        else
        {
            penetration_modifier = 3.0;
        }
    }

    auto trace_dist = (exit_trace.end_pos - trace.end_pos).length_sqr();
    auto pen_mod = fmaxf(1.0 / penetration_modifier, 0.0);
    auto total_lost_damage = ((trace_dist * pen_mod) / 24)
        + (damage_lost_percent * current_damage)
        + (fmaxf(3.54 / penetration, 0.0) * pen_mod * 2.8);

    if (total_lost_damage > 0)
        current_damage -= fmaxf(total_lost_damage, 0.f);

    if (current_damage < 1)
        return true;

    start = exit_trace.end_pos;

    --penetration_count;
    return false;
}

float distance_to_ray(vector center, vector start, vector end)
{
    auto direction = end - start;
    auto center_direction = center - start;
    auto length = direction.normalize();
    auto center_direction_dot = center_direction.dot(direction);

    float result = 0.f;

    if (center_direction_dot >= 0.f)
    {
        if (center_direction_dot <= length)
        {
            result = (center - (direction * center_direction_dot + start)).length();
        }
        else
        {
            auto delta_center_end = center - end;
            result = -delta_center_end.length();
        }
    }
    else
    {
        result = -center_direction.length();
    }

    return result;
}

void c_firebullet::clip_trace_to_players(vector start, vector end, float min, c_cs_player_pawn* player, c_trace_filter& filter, c_game_trace& trace)
{
    if (!player)
        return;

    if (!player->collision_property())
        return;

    auto obb_min = player->collision_property()->mins();
    auto obb_max = player->collision_property()->maxs();
    auto obb_center = (obb_max + obb_min) / 2;
    auto obb_position = obb_center + player->game_scene_node()->abs_origin();

    auto range = distance_to_ray(obb_position, start, end);

    if (range >= min && range <= 60.f)
    {
        c_ray ray{};
        c_game_trace player_trace{};
        Interfaces::trace->clip_ray_to_entity(&ray, start, end, player, &filter, &player_trace);

        if (trace.fraction > player_trace.fraction)
            trace = player_trace;
    }
}

bool c_firebullet::fire_bullet(vector& start, vector& point, bool& visible, float& currentDamage, c_cs_player_pawn* player, int hitbox_index)
{
    auto weapon = g_cs2->local_player->get_weapon_active();

    if (!weapon)
        return false;

    auto weapon_data = weapon->get_weapon_data();

    if (!weapon_data)
        return false;

    currentDamage = weapon_data->damage();

    c_ray ray{};

    c_game_trace enter_trace{};

    vector end{}, direction{};

    direction = (point - start).normalized();
    float current_distantion = 0.f;
    c_trace_filter filter(0x1C300B, g_cs2->local_player, nullptr, 3);
    float range = weapon_data->range();
    float range_modifier = weapon_data->range_modifier();
    auto penetration = weapon_data->penetration();
    int penetration_count = 4;
    auto start_position = start;
    vector penetration_end{};

    while (currentDamage >= 1.0f)
    {
        end = start_position + direction * (range - current_distantion);

        filter.flags = filter.flags & 0x80 | 0x49;
        filter.flags |= 2;

        Interfaces::trace->trace_shape(&ray, start_position, end, &filter, &enter_trace);

        clip_trace_to_players(start_position, (direction * 40.f) + end, 0.f, player, filter, enter_trace);

        if (enter_trace.fraction == 1.f)
            break;

        current_distantion += enter_trace.fraction * (range - current_distantion);
        currentDamage *= pow(weapon_data->range_modifier(), current_distantion / 500.0f);

        if (enter_trace.entity == player && enter_trace.trace_model && enter_trace.trace_model->m_nHitBoxIndex == hitbox_index) {
            scale_damage(enter_trace.trace_model->m_nGroupId, enter_trace.entity, weapon_data, currentDamage);
            return true;
        }

        if (!enter_trace.get_surfaces_data())
            break;

        float penetration_modifier = enter_trace.get_surfaces_data()->penetration_modifier;

        if ((current_distantion > 3000.f && penetration > 0) ||
            penetration_modifier < 0.1)
            break;

        if (handle_bullet_penetration(start_position, direction, penetration_end, penetration_count, penetration, currentDamage, true, enter_trace.get_surfaces_data()->material, penetration_modifier, enter_trace))
            break;

        visible = false;
    }

    return false;
}
