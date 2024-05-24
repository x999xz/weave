#include "../feature.hpp"

void c_misc::on_post() {
	g_misc->grenade_prediction();
	g_misc->buybot();
	g_misc->penetration_crosshair();
}