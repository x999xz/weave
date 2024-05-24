#pragma once

#include <cstdint>

class c_global_storage
{
public:
	char pad_0000[8]; //0x0000
	float interval_per_ticks; //0x0008
	float curtime; //0x000C
	float curtime2; //0x0010
	char pad_0014[4]; //0x0014
	float fraction; //0x0018
	bool N00000CD9; //0x001C
	char pad_001D[3]; //0x001D
	int64_t tick_count; //0x0020
	c_net_chan* net_channel; //0x0028
};

class c_global_vars
{
public:
	float realtime; //0x0000
	int32_t frame_count; //0x0004
	float interval_per_ticks; //0x0008
	float interval_per_ticks2; //0x000C
	int32_t max_client; //0x0010
	bool N00000CE3; //0x0014
	char pad_0015[3]; //0x0015
	bool prediction; //0x0018
	char pad_0019[7]; //0x0019
	c_global_storage global_storage; //0x0020
};