#pragma once

#include "../sdk.hpp"

class c_view_setup
{
public:
	char pad00[0x4D8];
	float fov;
	float fov_viewmodel;
	vector origin;
	char pad02[0xC];
	vector angle;
};