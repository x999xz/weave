// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

void c_player_movement_services::try_player_move(__int64 unk_target, vector position, float* unk_penis)
{
    using function_t = void(__fastcall*)(c_player_movement_services*, __int64, vector, float*);
    g_cs2->m_patterns[FNV32("try_player_move")].as<function_t>()(this, unk_target, position, unk_penis);
}

void c_player_movement_services::set_prediction_command(c_user_cmd* cmd) {
    CALL_VIRTUAL(void, 33, this, cmd);
}

void c_player_movement_services::reset_prediction_command() {
    CALL_VIRTUAL(void, 34, this);
}