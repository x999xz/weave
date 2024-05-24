#pragma once

#include <cstdint>

class internal_metadata
{
public:
	intptr_t ptr_ = 0;
	intptr_t kUnknownFieldsTagMask = 1;
	intptr_t kPtrTagMask = kUnknownFieldsTagMask; 
};