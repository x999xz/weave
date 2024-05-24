#pragma once

#include "../sdk.hpp"

struct c_fe_effect_desc
{
public:
	c_utl_string sName; // 0x0	
	uint32_t nNameHash; // 0x8	
	int32_t nType; // 0xc	
	char pad[0x10];
};