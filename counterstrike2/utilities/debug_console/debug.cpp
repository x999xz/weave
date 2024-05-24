// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "debug.hpp"

#include <Windows.h>
#include <cstdio>

debug g_debug = debug();

void debug::initialize(const char* console_title)
{
#if defined(_DEBUG) || defined(_DebugDev) 
	AllocConsole();

	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(0)), "conin$", "r", static_cast<_iobuf*>(__acrt_iob_func(0)));
	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(1)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(1)));
	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(2)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(2)));

	SetConsoleTitle(console_title);
#endif
}

void debug::release()
{
#if defined(_DEBUG) || defined(_DebugDev) 
	//fclose(static_cast<_iobuf*>(__acrt_iob_func(0)));
	//fclose(static_cast<_iobuf*>(__acrt_iob_func(1)));
	//fclose(static_cast<_iobuf*>(__acrt_iob_func(2)));

	//FreeConsole();
#endif
}

void debug::log(const char* message...)
{
#if defined(_DEBUG) || defined(_DebugDev) 
	printf(message);
#endif
}
