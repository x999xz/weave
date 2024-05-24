// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

//48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 66 0F 6E CA 41
void hooks::set_function_bool::hook(__int128* a1, unsigned int hash_function, std::uint32_t value)
{
	g_cs2->m_latest_hook = LoggerHack::SetFunctionBool;
	unsigned int toolsVisMode = g_cs2->get_hash_function(xorstr_("toolsVisMode"), 0x3141592A, 0x5BD1E995, 0xD0F88CBA);

	if (toolsVisMode == hash_function && g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0))
	{
		int world_changer = g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0) == 4 ? 17 : g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0) == 5 ? 21 : g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0) == 6 ? 22 : g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0) == 7 ? 24 : g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0) == 8 ? 46 : g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0) == 2 ? 47 : g_user->IsActive(xorstr_("misc_world_changer"), xorstr_("misc_world_changer"), 0);
		return set_function_bool_original(a1, hash_function, world_changer);
	}

	unsigned int direction_light = g_cs2->get_hash_function2(xorstr_("directLighting"), 0x31415928);
	unsigned int pen = 1540483477 * ((1540483477 * ((0x5BD1E995 * direction_light) ^ 0xD61945A5)) ^ ((1540483477 * ((0x5BD1E995 * direction_light) ^ 0xD61945A5)) >> 13));
	unsigned int pen2 = pen ^ (pen >> 15);

	if (pen2 == hash_function && g_user->IsActive(xorstr_("misc_disable_light"), xorstr_("misc_disable_light"), 0))
		return set_function_bool_original(a1, hash_function, 0);

	return set_function_bool_original(a1, hash_function, value);
}

void hooks::set_function_vector::hook(__int128* a1, unsigned int hash_function, vector_4d* value)
{
	g_cs2->m_latest_hook = LoggerHack::SetFunctionVector;
	int hash = g_cs2->get_hash_function2(xorstr_("DofRanges"), 0x3141592F);
	unsigned int hash2 = (0x5BD1E995 * (hash ^ 0x73)) ^ ((0x5BD1E995 * (hash ^ 0x73u)) >> 13);
	unsigned int hash3 = (1540483477 * hash2) ^ ((1540483477 * hash2) >> 15);

	if (g_user->IsActive(xorstr_("misc_blur"), xorstr_("misc_blur"), 0))
	{
		vector_4d new_value;
		new_value.y = 0.f;
		new_value.x = -100.f;
		new_value.w = 2000.f;
		new_value.z = 180.f;

		set_function_vector_original(a1, hash3, &new_value);
	}

	return set_function_vector_original(a1, hash_function, value);
}

void hooks::debug_info::hook(int a1, std::uintptr_t* a2)
{
	*(int*)(std::uintptr_t(a2) + 0x188) = 0;
	return debug_info_original(a1, a2);
}