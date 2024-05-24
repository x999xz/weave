#pragma once

#include "../sdk.hpp"

class c_model;

class c_perm_model_ext_part
{
public:
	c_transform m_Transform; // 0x0	
	c_utl_string m_Name; // 0x20	
	int32_t m_nParent; // 0x28	
private:
	[[maybe_unused]] uint8_t __pad002c[0x4]; // 0x2c
public:
	strong_handle< c_model > m_refModel; // 0x30	
};