#pragma once
#include <cstdint>

class c_memalloc
{
public:
	std::uintptr_t* Alloc(int size);
	void Free(void* ptr);
};