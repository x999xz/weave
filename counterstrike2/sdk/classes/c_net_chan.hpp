#pragma once

#include "../sdk.hpp"

class c_net_chan
{
public:
	void send_net_msg(void* message_handle, void* message_data, int unk)
	{
		// xref: SetSignonState
		CALL_VIRTUAL(void, 68, this, message_handle, message_data, unk);
	}

	float get_network_latency()
	{
		// xref: StartLagcompensation
		return CALL_VIRTUAL(float, 10, this);
	}

	float get_engine_latency()
	{
		// xref: StartLagcompensation
		return CALL_VIRTUAL(float, 11, this);
	}

	float get_avg_latency(int type)
	{
		// xref: %4.0f ms : %s\n
		return CALL_VIRTUAL(float, 11, this, type);
	}
};