// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "visuals.hpp"

#include <tinyformat/tinyformat.h>

class CMapInfo
{
public:
	char pad[0x4B4];
	float bomb_radius;
};

float get_damage_bombe(c_planted* c4)
{
	//static auto sign = g_utils->pattern_scan((uintptr_t)GetModuleHandle("server.dll"), "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 0A F3 0F 10 B0 B4 04 00 00").add(3).relative_address();

	//CMapInfo* map_info = sign.cast<CMapInfo*>();

	float radius = g_cs2->bomb_radius.at(g_cs2->map) * 3.5f;

	auto vec_to_target = reinterpret_cast<c_cs_player_pawn*>(c4)->game_scene_node()->abs_origin() - g_cs2->local_player->game_scene_node()->abs_origin();

	float fGaussianFalloff = exp(vec_to_target.length_sqr() * (-1.5 / ((radius * 0.33333334f) * radius)));

	return fGaussianFalloff * g_cs2->bomb_radius.at(g_cs2->map);
}

void c_visuals::run_c4_esp(c_planted* c4)
{
	box_t box = { };

	//auto handle = c_handle(c4->handle_bomb_defuser());

	//defuser_bomb_pawn = Interfaces::entity_list->get_entity(handle.get_index());
	//damage = get_damage_bombe(c4);
	//timer = c4->blow() - Interfaces::globals->global_storage.curtime;

	if (timer > 0.f)
	{
		//if (get_bounding_box((c_cs_player_pawn*)c4, box))
		//{
		//	if (defuser_bomb_pawn)
		//	{
		//		float def_left = c4->defuse_count_down() - Interfaces::globals->current_time;
		//		ImGui::GetBackgroundDrawList()->AddText(ImVec2(box.x + box.w / 2, box.y), ImColor(255, 255, 255, 255), tfm::format("bomb (%.2fs) (%.2f) (defuse left: %.2f)", timer, damage, def_left).c_str());
		//	}
		//	else
		//	{
		//		ImGui::GetBackgroundDrawList()->AddText(ImVec2(box.x + box.w / 2, box.y), ImColor(255, 255, 255, 255), tfm::format("bomb (%.2fs) (%.2f)", timer, damage).c_str());
		//	}
		//}
	}
}