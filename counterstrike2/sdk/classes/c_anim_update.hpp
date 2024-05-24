#pragma once

#include "../sdk.hpp"

class c_anim_update_shared_data
{
public:

};

class c_anim_update_instance_data
{
public:

};

class c_anim_update_context_builder
{
public:
	c_anim_update_shared_data* get_animation_update_shared_data()
	{
		return *reinterpret_cast<c_anim_update_shared_data**>(std::uintptr_t(this) + 0x18);
	}

	c_anim_update_instance_data* get_animation_update_data()
	{
		return *reinterpret_cast<c_anim_update_instance_data**>(std::uintptr_t(this) + 0x20);
	}

	c_animation_graph_visualization_manager* get_animation_graph_visualization_manager()
	{
		return *reinterpret_cast<c_animation_graph_visualization_manager**>(std::uintptr_t(this) + 0x28);
	}

	c_anim_skeleton* get_animation_skeleton()
	{
		return *reinterpret_cast<c_anim_skeleton**>(std::uintptr_t(this) + 0x30);
	}
};