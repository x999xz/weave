#pragma once
#include "virtual.hpp"

class c_network_game_client;

class i_network_game_service
{
	enum
	{
		unk = 23,
		send_voice_ = 48
	};
public:
	c_network_game_client* get_network_game_client()
	{
		return *(c_network_game_client**)(std::uintptr_t(this) + 0xB8);
	}
public:
	std::uintptr_t* get_unk()
	{
		return CALL_VIRTUAL(std::uintptr_t*, unk, this);
	}
	template<typename T>
	void send_voice(c_network_serialize_pb* message_handle, T* message)
	{
		CALL_VIRTUAL(void, send_voice_, this, 0, message_handle, message, -1);
	}
};