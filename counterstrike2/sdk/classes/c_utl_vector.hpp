#pragma once

#include "../sdk.hpp"

template< class T, class A = int>
class c_utl_vector
{
public:
	int get_size() { return size; }
	T get_element(int i) { return data[i]; }
protected:
	int64_t size;
	T* data;
};