// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "misc.h"
#include "../utilities/cloud/user.h"

void c_misc::bullet_impact()
{
	if (!g_cs2->local_player || !g_cs2->local_player->is_alive())
		return;

	auto bullet_service = g_cs2->local_player->bullet_services();

	if (!bullet_service)
		return;

	if (!g_user->IsActive(xorstr_("misc_client_impact"), xorstr_("misc_client_impact"), 0))
		return;

	for (auto i = bullet_service->m_bullet_data().get_size(); i > last_count_bullet; --i)
	{
		auto memory = bullet_service->m_bullet_data().get_element(i - 1);
		Interfaces::client->get_scene_debug_overlay()->add_box(memory.position, vector(-2, -2, -2), vector(2, 2, 2), vector(), color_t(255, 0, 0, 127));
	}

	if (bullet_service->m_bullet_data().get_size() != last_count_bullet)
		last_count_bullet = bullet_service->m_bullet_data().get_size();
}