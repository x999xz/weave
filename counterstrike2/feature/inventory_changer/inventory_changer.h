#pragma once

#include "../../utilities/utilities.hpp"
#include "../../sdk/sdk.hpp"
#include "../../sdk/math/vector.hpp"
#include "../../sdk/math/math.hpp"

class c_inventory_changer
{
public:
	void on_frame_stage_notify(int stage);
	void on_set_model(c_base_model_entity* entity, const char*& model);
	void create_image();
	bool force_update = false;
private:
	void update_knife(int stage);
	void update_glove(int stage);
	void update_skins();
	void update_agent();
	int glove_update_frames = -1;
	std::uint64_t hash_agent;
};

inline auto g_inventory_changer = std::make_unique<c_inventory_changer>();