#pragma once
#include "../sdk.hpp"

class c_svc_msg_voice_data
{
public:
	char pad[0x18];
	c_msg_voice_audio* audio;
	std::uint64_t xuid;
	std::int32_t unk;
	char pad2[11];
	std::int32_t client;
};