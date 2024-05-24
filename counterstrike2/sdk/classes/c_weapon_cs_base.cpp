#include "../sdk.hpp"

void c_weapon_cs_base::get_spread_pattern(unsigned short item_index, int bullets, int recoil_index, float* r3, float* r4)
{
	static auto pattern1 = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "66 89 54 24 10 55 48" );
	static auto pattern2 = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 8B 05 ?? ?? ?? ?? 48 8D 3C CD 00 00 00 00 48 03 D7 48 8D 4C 24 30 FF D0 84 C0 74 12 66 3B DE 74 4A" ).get_absolute_address(3,0);

	pattern1.as<void(__fastcall*)(std::uintptr_t*, unsigned short, std::uintptr_t*, int, float*, float*)>()( pattern2.as<std::uintptr_t*>(), item_index, nullptr, bullets * recoil_index, r3, r4);
}

vector c_weapon_cs_base::calculate_spread(unsigned int index)
{
	auto weapon_data = get_weapon_data();

	if (!weapon_data)
		return {};

	auto weapon_base = get_weapon_base();

	if (!weapon_base)
		return {};

	auto econ_item_view = get_econ_view_item();

	if (!econ_item_view)
		return {};

	int recoil_index = weapon_base->recoil_index();
	int bullets = weapon_data->bullets();
	int item_index = econ_item_view->item_index();
	float accuracy = get_accuracy();
	float spread = get_spread();

	g_utils->random_seed(index + 1);

	float r1 = g_utils->random_float(0.0f, 1.0f);
	float r2 = g_utils->random_float(0.0f, 6.2831855f);

	float r3{};
	float r4{};

	if (g_cs2->weapon_accuracy_shotgun_spread_patterns->GetValue<bool>())
	{
		get_spread_pattern(item_index, bullets, recoil_index, &r3, &r4);
	}
	else
	{
		r3 = r1;
		r4 = r2;
	}

	if (item_index == weapon_revolver)
	{
		r1 = 1.f - (r1 * r1);
		r3 = 1.f - (r3 * r3);
	}
	else if (item_index == weapon_negev && recoil_index < 3)
	{
		for (int i{ 3 }; i > recoil_index; --i) {
			r1 *= r1;
			r3 *= r3;
		}

		r1 = 1.f - r1;
		r3 = 1.f - r3;
	}

	// get needed sine / cosine values.
	float c1 = std::cosf(r2);
	float c2 = std::cosf(r4);
	float s1 = std::sinf(r2);
	float s2 = std::sinf(r4);

	float acc = r1 * accuracy;
	float sp = r3 * spread;

	return {
		(c1 * acc) + (c2 * sp),
		(s1 * acc) + (s2 * sp),
		0.f
	};
}