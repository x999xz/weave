#pragma once

#include <deque>

#include "../../sdk/sdk.hpp"

class c_bone
{
public:
    void copy();
    void set();
protected:
    c_bone_data matrix_[128];
};

class c_lagrecord
{
private:
    float m_simtime_;
public:
    c_bone_data matrix_[128];
private:
    c_bone_data backup_matrix_[128];
    int bone_count;
    vector origin_;
public:
    void setup(c_cs_player_pawn* player_pawn);
    void apply(c_cs_player_pawn* player_pawn, bool extrapolation = false);
    void restore(c_cs_player_pawn* player_pawn);
    bool record_of_bounds();
public:
    float get_sim_time() { return m_simtime_; }
};

class c_animation_table
{
public:
    std::deque<c_lagrecord> m_lag_records_{};
    c_lagrecord latest_record{};
    c_lagrecord oldest_record{};
};

class c_lagcompensation
{
public:
    void run();
public:
    float get_delta_time(int tick_entity);
public:
    c_animation_table* get_animation(c_cs_player_pawn* player_pawn);
private:
    std::unordered_map<unsigned long, c_animation_table> m_animation{};
public:
    int level;
};

inline auto g_lagcompensation = std::make_unique<c_lagcompensation>();