#pragma once

#include "../sdk.hpp"

class c_animation_graph_instance
{
public:
	c_anim_component_manager_instance* get_animation_manager()
	{
		using function_t = c_anim_component_manager_instance*(__thiscall*)(void*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[53](this);
	}

	c_anim_tag_manager* get_animation_tag_manager()
	{
		using function_t = c_anim_tag_manager * (__thiscall*)(void*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[51](this);
	}

	c_anim_parameter_list_instance* get_animation_parameter_list()
	{
		using function_t = c_anim_parameter_list_instance *(__thiscall*)(void*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[47](this);
	}

	c_anim_graph_settings_manager* get_animation_graph_settings_manager()
	{
		using function_t = c_anim_graph_settings_manager * (__thiscall*)(void*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[45](this);
	}

	c_anim_demo_manager* get_animation_demo_manager()
	{
		using function_t = c_anim_demo_manager * (__thiscall*)(void*);
		return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[54](this);
	}
};