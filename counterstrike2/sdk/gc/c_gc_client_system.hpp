#pragma once

class c_gc_client;

class c_gc_client_system
{
public:
	c_gc_client* gc_client()
	{
		return (c_gc_client*)(this + 0xB8);
	}
};