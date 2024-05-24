#pragma once

#include "../interfaces/virtual.hpp"

class c_application
{
public:
	bool is_developer()
	{
		return CALL_VIRTUAL(bool, 24, this);
	}
};