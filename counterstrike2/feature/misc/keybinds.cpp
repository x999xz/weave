// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "misc.h"
#include "../../utilities/hotkey_system/hotkey_system.h"

void c_misc::keybinds()
{
	//if (!g_config->get_config<bool>("misc_keybind"))
	//	return;

	//std::vector<std::pair<std::string, std::string>> active_binds{};

	//for (auto it : g_hotkey->hotkeys_)
	//{
	//	auto name = it.first;

	//	auto hotkey_list = it.second;

	//	for (auto hotkey : hotkey_list)
	//	{
	//		if (!hotkey.enabled || !hotkey.visible)
	//			continue;

	//		std::string type_ = hotkey.mode == 0 ? "hold" : "toggle";

	//		active_binds.push_back({ name, type_ });
	//	}
	//}


	//ImGui::SetNextWindowSize(ImVec2(170, 30 + (30 * active_binds.size())), ImGuiCond_Always);
	//ImGui::Begin("##weave_keybinds", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);

	//auto pos = ImGui::GetWindowPos() + ImGui::GetCursorPos();

	//auto buf = g_gui->draw_manager->get_buffer(g_gui->buffer_idx);

	//buf->set_blur(50, 1);
	//util::draw::rectangle_filled_rounded(buf, { pos.x,pos.y }, { pos.x + 170.f,pos.y + 30 }, 10.f, util::draw::color(255, 255, 255, 255), ROUND_RECT_TOP);
	//buf->set_blur(0);

	//ImGui::GetWindowDrawList()->AddRectFilled(pos, pos + ImVec2(170, 30), ImColor(43, 43, 43, 50), 10.f, ImDrawFlags_RoundCornersTop);
	//ImGui::GetWindowDrawList()->AddText(g_gui->get_inter_16(), g_gui->get_inter_16()->FontSize, pos + ImVec2((170 * 0.5f) - (g_gui->get_inter_16()->CalcTextSizeA(g_gui->get_inter_16()->FontSize, FLT_MAX, FLT_MAX, "Keybinds").x * 0.5f), 5), ImColor(1.f, 1.f, 1.f, 1.f), "Keybinds");

	//buf->set_blur(50, 1);
	//util::draw::rectangle_filled_rounded(buf, { pos.x,pos.y + 29 }, { pos.x + 170.f,pos.y + ImGui::GetWindowSize().y }, 10.f, util::draw::color(255, 255, 255, 80), ROUND_RECT_BOT);
	//buf->set_blur(0);

	//for (int i{}; i < active_binds.size(); i++)
	//{
	//	auto pos_ = pos + ImVec2(5, 35 + (30 * i));

	//	ImGui::GetWindowDrawList()->AddText(pos_ + ImVec2(10, 0), ImColor(1.f, 1.f, 1.f, 1.f), active_binds[i].first.c_str());
	//	ImGui::GetWindowDrawList()->AddText(pos_ + ImVec2(158 - ImGui::CalcTextSize(active_binds[i].second.c_str()).x, 0), ImColor(1.f, 1.f, 1.f, 1.f), active_binds[i].second.c_str());
	//}

	//ImGui::End();
}