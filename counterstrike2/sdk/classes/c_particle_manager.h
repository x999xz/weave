#pragma once

#include "../sdk.hpp"
#include "../interfaces/virtual.hpp"

class c_particle_manager
{
public:
	void create_snapshot(strong_handle<c_particle_snapshot>* out_particle_snapshot)
	{
		CALL_VIRTUAL(void, 43, this, out_particle_snapshot);
	}

	void draw(strong_handle<c_particle_snapshot>* particle_snapshot, int count, void* data)
	{
		CALL_VIRTUAL(void, 44, this, particle_snapshot, count, data);
	}
};