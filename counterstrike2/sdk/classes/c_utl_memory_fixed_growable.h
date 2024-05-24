#pragma once

#include "../sdk.hpp"

template< class T, size_t MAX_SIZE, class i = int >
class c_utl_memory_fixed_growable : public c_utl_memory< T, i >
{
public:
	typedef c_utl_memory< T, i > BaseClass;

public:
	c_utl_memory_fixed_growable(int nGrowSize = 0, int nInitSize = MAX_SIZE) : BaseClass(m_pFixedMemory, MAX_SIZE)
	{
		Assert(nInitSize == 0 || nInitSize == MAX_SIZE);
		m_nMallocGrowSize = nGrowSize;
	}
private:
	int m_nMallocGrowSize;
	T m_pFixedMemory[MAX_SIZE];
};