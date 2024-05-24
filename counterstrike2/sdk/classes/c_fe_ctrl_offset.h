#pragma once

#include "../sdk.hpp"

struct c_fe_ctrl_offset
{
public:
	vector vOffset; // 0x0	
	uint16_t nCtrlParent; // 0xc	
	uint16_t nCtrlChild; // 0xe	
};