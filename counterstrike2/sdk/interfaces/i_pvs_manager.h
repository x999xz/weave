#pragma once

class c_pvs_manager {
public:
	void set_pvs(bool state)
	{
		CALL_VIRTUAL(void, 7, this, state);
	}
};