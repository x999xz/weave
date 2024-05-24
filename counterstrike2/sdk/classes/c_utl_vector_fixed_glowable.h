#pragma once

#include "../sdk.hpp"

template< class T, size_t max_size >
class c_utl_vector_fixed_glowable : public c_utl_vector< T, c_utl_memory_fixed_growable<T, max_size > >
{
public:
	typedef c_utl_vector< T, c_utl_memory_fixed_growable<T, max_size > > base_class;

public:
	// constructor, destructor
	explicit c_utl_vector_fixed_glowable(int growSize = 0) : base_class(growSize, max_size) {}

};