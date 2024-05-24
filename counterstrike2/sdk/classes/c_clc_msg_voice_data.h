#pragma once
#include "../sdk.hpp"

class c_clc_msg_voice_data
{
public:
	static c_clc_msg_voice_data* create();
public:
	char pad[0x10];
	int m_has_bits;
	char pad2[0x4];
	c_msg_voice_audio* audio;
	std::uint64_t xuid;
	int tick;
};