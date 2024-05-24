#pragma once

#ifndef H_CRASH_HANDLER
#define H_CRASH_HANDLER

#include <Windows.h>

class crash_handler
{
public:
	static long __stdcall exception_handler(EXCEPTION_POINTERS* ex);
};

#endif

