// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

c_msg_voice_audio* c_msg_voice_audio::create()
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 48 89 74 24 18 57 48 83 EC 20 33 F6 48 8B F9 48 85 C9 75 2B 8D 4F 58" );
	return pattern.as<c_msg_voice_audio * (__fastcall*)(void*)>()(nullptr);
}