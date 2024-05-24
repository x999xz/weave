#pragma once

#include "../sdk.hpp"

class c_fe_fit_matrix
{
public:
	c_transform bone; // 0x0	
	vector vCenter; // 0x20	
	uint16_t nEnd; // 0x2c	
	uint16_t nNode; // 0x2e	
	uint16_t nBeginDynamic; // 0x30	
};