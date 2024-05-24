#pragma once

#include "../../sdk/classes/user_cmd.hpp"
#include "../../sdk/interfaces/i_csgo_input.hpp"
#include "../../sdk/sdk.hpp"
#include "../../sdk/math/vector.hpp"

#include "../../sdk/math/math.hpp"

#include "rage_enums.h"

class c_hitbox_data
{
public:
	const auto get_hitbox() { return m_index; } // пенисовая функция получение индекса хитбокса
private:
	int m_index = -1;
	e_hitbox_type m_type = -1;
	float m_shape_radius = 0.f;
	vector m_shape_min = vector();
	vector m_shape_max = vector();
};