#pragma once
#include "../sdk.hpp"

class c_network_messages
{
public:
	c_network_serialize_pb* find_or_create_net_message(int index, void* protobuf_binding)
	{
		return CALL_VIRTUAL(c_network_serialize_pb*, 2, this, index, protobuf_binding, 48, 0, 1, 0);
	}
};