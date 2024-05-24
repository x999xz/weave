#pragma once

#include "../sdk.hpp"

class c_perm_model_info
{
public:
	uint32_t m_nFlags; // 0x0	
	vector m_vHullMin; // 0x4	
	vector m_vHullMax; // 0x10	
	vector m_vViewMin; // 0x1c	
	vector m_vViewMax; // 0x28	
	float m_flMass; // 0x34	
	vector m_vEyePosition; // 0x38	
	float m_flMaxEyeDeflection; // 0x44	
	c_utl_string m_sSurfaceProperty; // 0x48	
	//c_utl_string m_keyValueText; // 0x50
} __attribute((packet));