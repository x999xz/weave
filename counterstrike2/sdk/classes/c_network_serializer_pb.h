#pragma once
#include "../sdk.hpp"

class c_network_serialize_pb
{
public:
	void* vtable;
	const char* unscopedName;
	uint32_t categoryMask;
	int unk;
	c_protobuff_binding* protobufBinding;
	const char* groupName;
	int16_t messageID;
	uint8_t groupID;
	uint8_t defaultBufferType;
	char _pad[28];
};