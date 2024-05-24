#pragma once

#include "../sdk.hpp"

class c_fe_ctrl_soft_offset
{
public:
	uint16_t nCtrlParent; // 0x0	
	uint16_t nCtrlChild; // 0x2	
	vector vOffset; // 0x4	
	float flAlpha; // 0x10	
};