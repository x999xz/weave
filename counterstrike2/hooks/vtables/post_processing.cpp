// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void hooks::draw_processing::hook(std::uintptr_t* a1, int a2, name_vfx* a3, std::uintptr_t* a4, std::uintptr_t* a5, std::uintptr_t* a6, int a7, unsigned int a8, int a9, char a10)
{
	g_cs2->m_latest_hook = LoggerHack::DrawProcessing;
	if (!strcmp(a3->name1, xorstr_("QuarterResUnthresholded")) && !strcmp(a3->name2, xorstr_("QuarterResUnthresholdedBlurred")) && g_user->IsActive(xorstr_("misc_remove_post_processing"), xorstr_("misc_disable_light"), 4))
		return;

	return draw_processing_original(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

void __fastcall hooks::post_processing::hook(std::uintptr_t* a1, scene_view* a2, char a3, std::uintptr_t* a4, std::uintptr_t* a5, unsigned int a6, char a7)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "66 0F 6E CA 4C 8D 1D ?? ?? ?? ?? 66 0F 70 C9 00 4D" );

	auto post_processing_settings_ = pattern.as<post_processing_settings * (__fastcall*)(std::uintptr_t*, unsigned int, std::uintptr_t*)>()(a2->unk_->get_penis(), 0xDEFF7E36, 0);

	if (post_processing_settings_ && post_processing_settings_->shadow && g_user->IsActive(xorstr_("misc_remove_post_processing"), xorstr_("misc_disable_light"), 4))
		post_processing_settings_->shadow = false;

	return post_processing_original(a1, a2, a3, a4, a5, a6, a7);
}