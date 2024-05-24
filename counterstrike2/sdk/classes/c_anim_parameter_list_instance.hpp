#pragma once

#include "../sdk.hpp"

class c_anim_parameter_list_instance
{
public:
	c_anim_parameter_manager_updater* get_animation_parameter_manager_updater()
	{
		return *reinterpret_cast<c_anim_parameter_manager_updater**>(std::uintptr_t(this) + 0x40);
	}

	c_anim_update_context_builder* get_animation_update_context_builder()
	{
		return *reinterpret_cast<c_anim_update_context_builder**>(std::uintptr_t(this) + 0x48);
	}
};