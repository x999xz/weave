// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../ragebot/ragebot.hpp"

class c_trace_info
{
public:
	float unk;
	float distance;
	float damage;
	std::uint32_t penetration_count;
	std::uint32_t handle;
	std::uint32_t handle2;
};

class c_trace_data
{
public:
	char pad[0x8];
	void* penis;
	char pad5[0x1810];
	int size;
	c_trace_info* trace_info;
	char pad2[0x8];
	void* unk;
	char pad4[184];
	vector start;
	vector end;
	char pad3[0x50];
};

class c_info_bullet
{
public:
	int damage;
	float penetration;
	float range_modifier;
	float range;
	int penetration_count;
	bool failed;
};

void init_trace_data(c_trace_data* trace_data, vector& start, vector& end, c_trace_filter* filter, int& pen_count)
{
	add_trace(__PRETTY_FUNCTION__);

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 40 F2" );
	return pattern.as<void(__fastcall*)(c_trace_data*, vector, vector, c_trace_filter*, int)>()(trace_data, start, end, filter, pen_count);
}

void get_trace(c_trace_data* trace_data, c_game_trace* trace, c_trace_info* trace_info)
{
	add_trace(__PRETTY_FUNCTION__);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "41 0F B7 40 ?? F3 41 0F 10 10" );

	return pattern.as<void(__fastcall*)(c_trace_data*, c_game_trace*, c_trace_info*)>()(trace_data, trace, trace_info);
}

void run_trace(c_trace_data* trace_data,
	float damage,
	float penetration,
	float range_modifier,
	unsigned int penetration_count,
	unsigned int teamnum,
	int* sv_showimpacts_penetration)
{
	add_trace(__PRETTY_FUNCTION__);

	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "4C 8B DC 53 55 41" );
	return pattern.as<void(__fastcall*)(c_trace_data * trace_data, float damage, float penetration, float range_modifier, unsigned int penetration_count, unsigned int teamnum, int* sv_showimpacts_penetration)>()(trace_data, damage, penetration, range_modifier, penetration_count, 0, nullptr);
}

bool c_firebullet_cs2::run(c_cs_player_pawn* entity, vector& start, vector& end, float& damage, int& hitbox)
{
	add_trace(__PRETTY_FUNCTION__);
	auto weapon = g_cs2->local_player->get_weapon_active();

	if (!weapon)
		return false;

	auto weapon_data = weapon->get_weapon_data();

	if (!weapon_data)
		return false;

	c_trace_filter filter(0x1C3003, g_cs2->local_player, nullptr, 4);
	int penetration_count = 4;

	trace_data = (c_trace_data*)Interfaces::m_mem_alloc->Alloc(sizeof(c_trace_data));

	ZeroMemory(trace_data, sizeof(c_trace_data));
	init_trace_data(trace_data, start, end, &filter, penetration_count);

	bool ret = false;

	if (trace_data->trace_info)
	{

		run_trace(trace_data, weapon_data->damage(), weapon_data->penetration(), weapon_data->range_modifier(), 4, 0, nullptr);

		for (int i = 0; i < trace_data->size; i++)
		{
			trace_data->trace_info[i].unk = 0.f;
			auto trace_info = trace_data->trace_info[i];

			c_game_trace trace{};
			get_trace(trace_data, &trace, &trace_info);

			if (entity)
			{
				if (trace.entity == entity)
				{
					damage = trace_info.damage;
					g_firebullet->scale_damage(trace.trace_model->m_nGroupId, trace.entity, weapon_data, damage);
					hitbox = trace.trace_model->m_nHitBoxIndex;
					ret = true;
					break;
				}
			}
			else
			{
				g_cs2->can_penetration = trace_info.penetration_count != 4 && trace_info.penetration_count != 0;
			}
		}
	}

	if (trace_data) {
		if (trace_data->penis)
			Interfaces::m_mem_alloc->Free(trace_data->penis);
		if (trace_data->unk)
			Interfaces::m_mem_alloc->Free(trace_data->unk);
		if (trace_data->trace_info)
			Interfaces::m_mem_alloc->Free(trace_data->trace_info);

		Interfaces::m_mem_alloc->Free(trace_data);
	}

	return ret;
}