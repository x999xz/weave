#pragma once

#include "../sdk.hpp"

class c_networked_sequence_operation
{
public:
	int sequence() {
		return *(int*)(std::uintptr_t(this) + 0x14B0);
	}
	float prev_cycle() {
		return *(float*)(std::uintptr_t(this) + 0xC);
	}
	float cycle() {
		return *(float*)(std::uintptr_t(this) + 0x10 );
	}
	int weight() {
		return *(int*)(std::uintptr_t(this) + 0x14 );
	}
	bool sequence_change_networked() {
		return *(bool*)(std::uintptr_t(this) + 0x1C );
	}
	bool discontinuity() {
		return *(bool*)(std::uintptr_t(this) + 0x1D);
	}
	float prev_cycle_from_discontinuity() {
		return *(float*)(std::uintptr_t(this) + 0x20 );
	}
	float prev_cycle_for_anim_event_detection() {
		return *(float*)(std::uintptr_t(this) + 0x24 );
	}
};

class c_anim_graph_networked_variables
{

};

class c_base_anim_graph_controller
{
public:
	__forceinline c_networked_sequence_operation base_layer() {
		return *reinterpret_cast<c_networked_sequence_operation*>(reinterpret_cast<std::uint64_t>(this) + g_pSchemaOffset->m_baseLayer); // din pula
	};
	__forceinline bool sequence_finished() {
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint64_t>(this) + 0x14A8 );
	};
};