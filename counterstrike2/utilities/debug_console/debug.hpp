#pragma once

class debug
{
public:
	void initialize(const char* console_title);
	void release();

	void log(const char* message...);
};

extern debug g_debug;