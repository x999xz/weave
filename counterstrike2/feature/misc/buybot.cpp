#include "misc.h"
#include "../utilities/cloud/user.h"

void c_misc::buybot() {
	if (!g_cs2->on_round)
		return;


	if (g_user->IsActive(xorstr_("misc_buybot"), xorstr_("misc_buybot"), 0)) {
		if (g_user->IsActive(xorstr_("misc_buybot_armor"), xorstr_("misc_buybot_zeus"), 1))
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy taser"));

		if (g_user->IsActive(xorstr_("misc_buybot_zeus"), xorstr_("misc_buybot_zeus"), 0))
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy vesthelm"));

		if (g_user->IsActive(xorstr_("misc_buybot_grenades"), xorstr_("misc_buybot_zeus"), 2))
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy hegrenade; buy smokegrenade; buy molotov;"));

		int primary = g_user->IsActive(xorstr_("misc_buybot_primary"), xorstr_("misc_buybot_primary"), 0);
		int secondary = g_user->IsActive(xorstr_("misc_buybot_secondary"), xorstr_("misc_buybot_secondary"), 0);

		switch (primary) {
		case 1:
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy ssg08"));
			break;
		case 2:
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy awp"));
			break;
		case 3:
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy g3sg1; buy scar20"));
			break;
		}

		switch (secondary) {
		case 1:
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy deagle"));
			break;
		case 2:
			Interfaces::engine->client_cmd_unrestricted(xorstr_("buy fiveseven; buy tec9"));
			break;
		}
	}

	g_cs2->on_round = false;
}