#include "grenade_prediction_.hpp"

std::pair<vector,vector> c_grenade_prediction_::throw_grenade(c_base_cs_grenade* grenade, vector angle)
{
    vector ang_throw = angle;

    if (ang_throw.x <= 90.f)
    {
        if (ang_throw.x < -90.f)
            ang_throw.x += 360.f;
    }
    else
    {
        ang_throw.x -= 360.f;
    }

    ang_throw.x -= (90.0 - fabs(ang_throw.x)) * 0.11111111;

    float throw_velocity = std::clamp(grenade->get_weapon_data()->throw_velocity() * 0.89f, 15.f, 750.f);
    float throw_strength = std::clamp(grenade->m_flThrowStrength(), 0.5f, 1.0f);
    float vel = throw_velocity * ((throw_strength * 0.69999999) + 0.30000001);

    vector forward{};

    math::angle_vectors(ang_throw, forward);

    float throw_ = (throw_strength * 12.f) - 12.f;

    vector end_pos = (forward * 22.f) + vector(g_cs2->eye_position.x, g_cs2->eye_position.y, g_cs2->eye_position.z + throw_);

    c_ray ray{};
    c_trace_filter filter(0x2000C3001, nullptr, nullptr, 4);
    c_game_trace trace;
    Interfaces::trace->trace_shape(&ray, g_cs2->eye_position, end_pos, &filter, &trace);

    return { trace.end_pos - forward * 6.f,  forward * vel + g_cs2->local_player->velocity() * 1.25f };
}

void c_grenade_prediction_::physics_push_entity(vector push) {

    if (!m_owner->collision_property() || !(m_owner->collision_property()->collision_function_mask() & 3) || !m_owner->collision_property()->solid_type())
        return;

    c_trace_filter filter(0x0, m_owner, nullptr, 4);
    c_game_trace trace;
    c_ray ray{};

    Interfaces::trace->trace_shape(&ray, m_origin, m_origin + push, &filter, &trace);

    if (trace.fraction > 0.f)
        m_origin = trace.end_pos;

    if (!trace.entity)
        return;
}