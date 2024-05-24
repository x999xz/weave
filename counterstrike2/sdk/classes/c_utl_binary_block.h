#pragma once

#include "../sdk.hpp"

class c_utl_binary_block
{
public:
	c_utl_memory<unsigned char> m_Memory;
	int m_nActualLength;
};