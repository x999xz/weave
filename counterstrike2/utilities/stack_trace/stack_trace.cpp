// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "stack_trace.h"

std::string c_stack_trace::dump_trace()
{
	std::string dump = "stacktrace:\n";

	for (int i{}; i < max_trace; i++)
	{
		std::string name = trace_[i];
		dump += name + "\n";
	}

	return dump;
}