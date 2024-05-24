#include "loader.h"
#include "../core.hpp"
#include "../utilities/cloud/user.h"

void c_loader::Setup() {
	g_cs2->username = "srcboss";
	g_cs2->token = token;
	//g_user->SetUsername(g_cs2->username);

#if defined(_DEV) || defined(_DEBUG) || defined(_DebugDev)
	g_cs2->build = xorstr_("dev");
#elif defined(_ALPHAB)
	g_cs2->build = xorstr_("alpha");
#else
	g_cs2->build = xorstr_("stable");
#endif
}