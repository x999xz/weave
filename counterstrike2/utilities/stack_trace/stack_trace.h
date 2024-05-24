#pragma once

#include <string>
#include <memory>
#include "../xorstr.h"

class c_stack_trace
{
	enum
	{
		max_trace = 15
	};
public:
	const char* trace_[max_trace];
	int sequence_number_ = 0;
public:
	void add_trace(const char* trace_name) { trace_[sequence_number_ % max_trace] = trace_name; ++sequence_number_; }
	std::string dump_trace();
};

inline auto g_stack_trace = std::make_unique<c_stack_trace>();

#ifndef _RELEASE
#define add_trace(trace_name) //g_stack_trace->add_trace(xorstr_(trace_name));
#else 
#define add_trace(trace_name) 
#endif
