#pragma once
#include "../sdk.hpp"

class CCSPlayerController_InventoryServices
{
public:
	__forceinline int m_nPersonaDataPublicLevel() {
		return *reinterpret_cast<int*>(reinterpret_cast<std::uint64_t>(this) + 0x5C );
	};
};