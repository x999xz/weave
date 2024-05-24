#pragma once

class i_engine_client
{
public:
	bool is_in_game()
	{
		// find string de_aztec -> v1 parameter function
		return CALL_VIRTUAL(bool, 35, this);
	}

	bool is_connected()
	{
		// +1 in IsInGame function
		return CALL_VIRTUAL(bool, 36, this);
	}

	bool is_pause()
	{
		return CALL_VIRTUAL(bool, 11, this);
	}

	int get_last_time_stamp()
	{
		return CALL_VIRTUAL(int, 28, this);
	}

	void get_screen_size(std::int32_t& width, std::int32_t& height)
	{
		CALL_VIRTUAL(void, 48, this, width, height);
	}

	void client_cmd_unrestricted(const char* cmd)
	{
		//xref: buy vesthelm
		return CALL_VIRTUAL(void, 43, this, 0, cmd, 1);
	}
};