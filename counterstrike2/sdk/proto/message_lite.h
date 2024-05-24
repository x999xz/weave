#pragma once

class message_lite
{
public:
	bool serialize_partial_to_array(std::uintptr_t* data, int size);
	void parse_partial_to_array(const void* data, int size);
	std::uintptr_t* merge(void* to, std::uintptr_t* hyeta);
public:
	internal_metadata _internal_metadata_;
};