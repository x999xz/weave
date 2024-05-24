#pragma once
#include <cstdint>
#include <memory>

class color_channel;

class c_channel_system
{
public:
	void init();
private:
	std::uintptr_t* create_channel(const char* str, color_channel clr);
public:
	bool is_enable(std::uintptr_t* channel);
	void add_log(std::uintptr_t* channel, const char* txt);
public:
	std::uintptr_t* weave_channel;
};

inline auto g_channel_system = std::make_unique<c_channel_system>();