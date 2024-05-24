#include "misc.h"
#include "../../utilities/dx11_helper/dx11_helper.hpp"
#include "../../renderer/render_manager.h"
#include "../../gui/gui.h"

void c_misc::notify()
{
	render_size size_block = render_size(220, 50);
	for (int i{}; i < m_notify.size(); i++)
	{
		m_notify[i].time_to_de -= 0.010f;
		auto& anim = m_notify[i].animation;

		auto position = render_position(g_render->get_screen_size().x, (g_render->get_screen_size().y - 10 - size_block.y) - ((10 + size_block.y) * i));

		anim.run(m_notify[i].time_to_de > 0.f, 0.2f);

		g_render->push_override_alpha(anim.base);

		position -= render_position((10 + size_block.x) * anim.base, 0);

		g_render->rect_filled(position, size_block, render_color(16, 16, 16), c_render_manager::render_flags_::blur, 3.f, render_rounding_flags_::ROUND_RECT_TOP);
		g_render->rect_filled(position, size_block, render_color(16, 16, 16, 180), 0, 3.f, render_rounding_flags_::ROUND_RECT_TOP);
		g_render->add_texture(position + render_position(14, 11), render_size(50, 23), g_gui->m_texture[1]);
		g_render->add_text(m_notify[i].title, position + render_position(82, 8), render_color::white(), g_render->get_font(1), 13.f);


		g_render->pop_override_alpha();
	}
	m_notify.erase(std::remove_if(m_notify.begin(), m_notify.end(), [&](const auto x) {
		return x.time_to_de < 0.f && x.animation.base <= 0.f;
		}), m_notify.end());
}