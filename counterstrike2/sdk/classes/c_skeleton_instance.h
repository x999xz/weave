#pragma once

class c_cs_player_pawn;

class c_skeleton_instance
{
public:
	__forceinline c_model_state& m_modelState() {
		return *reinterpret_cast<c_model_state*>(reinterpret_cast<std::uint64_t>(this) + 0x160 );
	};

	c_model* get_model()
	{
		auto ptr = *reinterpret_cast<void**>((uintptr_t)this + 0x200);

		if (!ptr)
			return nullptr;

		return *reinterpret_cast<c_model**>(ptr);
	}

	std::uint32_t get_bone_count()
	{
		return *reinterpret_cast<std::uint32_t*>(std::uintptr_t(this) + 0x1BC);
	}

	std::uint32_t get_mask()
	{
		return *reinterpret_cast<std::uint32_t*>(std::uintptr_t(this) + 0x1D8);
	}

	c_cs_player_pawn* get_owner_pawn()
	{
		return *reinterpret_cast<c_cs_player_pawn**>(std::uintptr_t(this) + 0x290);
	}

	void calc_world_space_bones(int bone_mask);
};