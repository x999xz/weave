// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

c_utl_buffer::c_utl_buffer()
{
	g_cs2->m_patterns[FNV32("contruct_utl_buffer")].as<c_utl_buffer* (__fastcall*)(c_utl_buffer*, int, int, bool)>()(this, 0, 0, false);
}

void c_utl_buffer::ensure(int size)
{
	g_cs2->m_patterns[FNV32("ensure_capacity_utl_buffer")].as<void(__fastcall*)(c_utl_buffer*, int)>()(this, size);
}