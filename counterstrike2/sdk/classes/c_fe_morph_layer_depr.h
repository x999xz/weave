#pragma once

#include "../sdk.hpp"

struct c_fe_morph_layer_depr
{
public:
	c_utl_string m_Name; // 0x0	
	uint32_t m_nNameHash; // 0x8	
private:
	[[maybe_unused]] uint8_t __pad000c[0x4]; // 0xc
public:
	c_utl_vector< unsigned short > m_Nodes; // 0x10	
	c_utl_vector< vector > m_InitPos; // 0x28	
	c_utl_vector< float > m_Gravity; // 0x40	
	c_utl_vector< float > m_GoalStrength; // 0x58	
	c_utl_vector< float > m_GoalDamping; // 0x70	
	uint32_t m_nFlags; // 0x88	
};