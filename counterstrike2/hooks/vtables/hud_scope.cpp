// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

//40 53 57 41 56 48 83 EC 20 4C 8B F1
__int64 hooks::render_scope::hook(std::uintptr_t* csgo_hudscope)
{
	g_cs2->local_player = Interfaces::entity_list->get_split_screen_view_player(0);

	//xref scope--hidden
	if (!g_cs2->local_player)
		return render_scope_original(csgo_hudscope);

	if (!g_cs2->local_player->is_alive())
		return render_scope_original(csgo_hudscope);

	//if(!g_user->IsActive(xorstr_("misc_remove_scope")))
	//	return render_scope_original(csgo_hudscope);

	auto ret = render_scope_original(csgo_hudscope);
	return ret;
}