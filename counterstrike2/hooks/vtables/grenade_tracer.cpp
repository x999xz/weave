#include "../hooks.hpp"
#include "../../sdk/classes/c_grenade_trace.h"

void bombandir2(void* ptr)
{
	//remove entity
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 83 EC 28 4C 8B C1 48 85 C9 0F" );
	pattern.as<void(__fastcall*)(void* ptr)>()(ptr);
}

void get_time2(float& time, int group)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 18 48 89 6C 24 20 57 48 83 EC 20 48 8B 3D" );
	pattern.as<void(__fastcall*)(float&, int)>()(time, group);
}


bool valid_throw2(c_cs_player_pawn* pawn, float value)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 30 48 8B 41 10 48 8B D9 0F 29 74 24 20 48 8D 4C 24 50" );
	return pattern.as<bool(__fastcall*)(void* ptr, float)>()(pawn, value);
}

//40 57 48 83 EC 40 48 8B F9 BA
void hooks::grenade_tracer::hook(c_base_cs_grenade* grenade)
{
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 20 48 8B 01 48 8B DA FF 90 ?? ?? ?? ?? 48 85 C0 74 0D" );
	static auto pattern2 = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B C4 48 89 50 10 55 41 56 48" );
	static auto pattern3 = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B C4 48 89 58 18 48 89 50 10 55" );

	g_cs2->m_latest_hook = LoggerHack::GrenadeTrace;
	bool in_attack = pattern.as<bool(__fastcall*)(c_base_cs_grenade*, int)>()(grenade, 1);
	bool in_attack2 = pattern.as<bool(__fastcall*)(c_base_cs_grenade*, int)>()(grenade, 2048);
	auto base_entity = (c_base_entity*)grenade;

	if(!base_entity || !base_entity->owner_handle().is_valid() || !g_user->IsActive(xorstr_("misc_grenade_prediction"), xorstr_("misc_grenade_prediction"),0))
		return grenade_tracer_original(grenade);

	auto handle = g_cs2->get_handle_entity((c_cs_player_pawn*)grenade);

	if (grenade->redraw())
	{
		g_misc->grenade_prediction_m.lock();
		g_misc->lines.clear();
		g_misc->grenade_prediction_m.unlock();
	}
	else
	{
		auto owner = Interfaces::entity_list->get_entity(base_entity->owner_handle().get_index());
		if (owner)
		{

			auto type = grenade->unk_penis();
			auto grenade_trace = pattern2.as<c_grenade_trace * (__fastcall*)(int, c_base_cs_grenade*, float)>()(type, grenade, 30.f);

			if (grenade_trace)
			{
				pattern3.as<void(__fastcall*)(c_grenade_trace*, vector&, vector&)>()(grenade_trace, g_misc->direction_grenade[0], g_misc->direction_grenade[1]);

				auto penis = (c_grenade_trace*)grenade_trace;

				g_misc->grenade_prediction_m.lock();
				g_misc->lines.clear();

				for (int i = 0; i < penis->size; i++)
				{
					auto value = penis->data[i];

					if (!value.size)
						continue;

					if (!value.data)
						continue;

					for (int j{}; j < value.size; j++)
					{
						vector screen{};

						if (!math::world_to_screen(value.data[j], screen))
							continue;

						g_misc->lines.push_back(vector(screen.x, screen.y, 0.f));
					}
				}
				g_misc->grenade_prediction_m.unlock();

				bombandir2(grenade_trace);
			}
		}
	}
	return grenade_tracer_original(grenade);
}