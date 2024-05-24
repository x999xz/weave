#pragma once

#include "../interfaces/virtual.hpp"

class c_particle_snapshot
{
public:
	void draw(int count, void* data)
	{
		CALL_VIRTUAL(void, 1, this, count, data);
	}
};