#pragma once

#include "../sdk.hpp"

class c_transform
{
public:
	vector position;
	vector_4d rotate;
public:
	matrix3x4_t to_matrix();
};