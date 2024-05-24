#pragma once

class c_utl_buffer
{
public:
	c_utl_buffer();
	void ensure(int size);
public:
	std::uintptr_t* aye;
	char pad[0x30];
};