#pragma once

#include "../sdk.hpp"

class c_cs_player_viewmodel_services
{
public:
	__forceinline c_handle view_model() {
		return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x40 );
	};
};