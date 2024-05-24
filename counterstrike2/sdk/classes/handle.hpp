#pragma once

#include <cstdint>

class c_handle
{
public:
	c_handle();
	c_handle(const c_handle& other);
	c_handle(unsigned long value);
	c_handle(int iEntry, int iSerialNumber);

	inline int get_index()
	{
		return handler & 0x7FFF;
	}

	inline unsigned long get_handle()
	{
		return handler;
	}

	inline bool is_valid()
	{
		if (handler <= 0 || handler == 0xffffffff)
			return false;

		return true;
	}

protected:
	std::uint32_t handler;
};

inline c_handle::c_handle()
{
	handler = -1;
}

inline c_handle::c_handle(const c_handle& other)
{
	handler = other.handler;
}

inline c_handle::c_handle(unsigned long value)
{
	handler = value;
}