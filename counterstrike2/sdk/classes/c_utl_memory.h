#pragma once

#include <assert.h>

template <class T, class I = int>
class c_utl_memory {
public:
    template< class A, class B> friend class c_utl_vector;
    T& operator[](I i)
    {
        return m_pMemory[i];
    }

    T* m_pMemory;
    int m_nAllocationCount;
    int m_nGrowSize;
};