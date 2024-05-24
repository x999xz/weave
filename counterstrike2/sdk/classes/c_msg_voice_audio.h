#pragma once
#include "../sdk.hpp"

class c_msg_voice_audio
{
public:
	static c_msg_voice_audio* create();
public:
	char pad[0x10];
	int has_bits;
	char pad3[0x14];
	std::uint32_t format;
	char pad2[0x4];
	std::uint64_t voice_data;
	std::int64_t sequence_bytes;
	std::uint32_t section_number;
	std::uint32_t sample_rate;
	std::uint32_t uncompressed_sample_offset;
	std::uint32_t num_packets;
	int size_packet_offsets;
	int max_size_packet_offsets;
	std::uintptr_t* packet_offsets;
	float voice_level;
};