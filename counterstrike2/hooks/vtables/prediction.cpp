// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void hooks::run_command::hook(c_player_movement_services* movement, c_user_cmd* cmd)
{
	return run_command_original(movement, cmd);
}

int __fastcall hooks::run_simulation::hook(__int64 prediction, __int64* container_unk, unsigned int bool_value, unsigned int tick, c_user_cmd* usercmd)
{
	g_cs2->m_latest_hook = LoggerHack::RunSimulation;
	return run_simulation_original(prediction, container_unk, bool_value, tick, usercmd);
}