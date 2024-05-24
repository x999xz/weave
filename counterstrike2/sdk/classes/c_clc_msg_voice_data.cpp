// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

c_clc_msg_voice_data* c_clc_msg_voice_data::create()
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_engine2( ), "40 53 48 83 EC 20 48 8B 05 ?? ?? ?? ?? 33 DB 48 8B 08 8D 53 30 48 8B 01 FF 50 ?? 48 85 C0 74 25" );
	return pattern.as<c_clc_msg_voice_data * (__fastcall*)()>()();
}