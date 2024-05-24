// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

std::uintptr_t* c_memalloc::Alloc(int size)
{
	return CALL_VIRTUAL(std::uintptr_t*, 1, this, size);
}

void c_memalloc::Free(void* ptr)
{
	CALL_VIRTUAL(void, 3, this, ptr);
}