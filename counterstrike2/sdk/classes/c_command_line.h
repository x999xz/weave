#pragma once

#include "../interfaces/virtual.hpp"

class c_command_line
{
public:
	bool find(const char* str)
	{
		return CALL_VIRTUAL(bool, 4, this, str);
	}
};