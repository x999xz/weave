// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../gui.h"

void c_gui::tabs()
{
	auto position = get_position();

	int padding_x = 0;

	render_position all_text_size{};

	for (int i = 1; i < m_tabs.size(); i++)
	{
		all_text_size += g_render->get_font(4)->calc_text_size(14.f, FLT_MAX, FLT_MAX, m_tabs[i].name_.c_str()).x + 14;
	}

	all_text_size -= 14;

	int index_tab = 0;
	
	render_color no_active(107, 107, 107);
	render_color active(221, 221, 221);


	for (auto& tab : m_tabs)
	{
		render_color color = helper.animation_color(no_active, active, tab.animation.base);

		if (tab.is_home_)
		{
			//g_render->add_text(tab.name_, position + render_position(35, 20), color, g_render->get_font(4), 14);
			//auto calc_text = g_render->get_font(4)->calc_text_size(14.f, FLT_MAX, FLT_MAX, tab.name_.c_str());
			//if (helper.is_hovered(m_mouse_pos_, rect_(position + render_position(35, 20), calc_text)) && has_pressed(VK_LBUTTON) && active_tab != index_tab)
			//{
			//	anim_active_id = index_tab;
			//}
		}
		else
		{
			auto calc_text = g_render->get_font(4)->calc_text_size(14.f, FLT_MAX, FLT_MAX, tab.name_.c_str());
			g_render->add_text(tab.name_, position + render_position(window_size.x / 2,0) - render_position(all_text_size.x / 2, 0) + render_position(padding_x, 19), color, g_render->get_font(4), 14);

			tab.animation.run(helper.is_hovered(m_mouse_pos_, rect_(position + render_position(window_size.x / 2, 0) - render_position(all_text_size.x * 0.5f, 0) + render_position(padding_x, 19), calc_text)) || active_tab == index_tab || anim_active_id == index_tab);
			
			if (helper.is_hovered(m_mouse_pos_, rect_(position + render_position(window_size.x / 2, 0) - render_position(all_text_size.x * 0.5f, 0) + render_position(padding_x, 19), calc_text)) && has_pressed(VK_LBUTTON) && active_tab != index_tab && active_id == -1 && !has_popup_open_)
			{
				anim_active_id = index_tab;
			}
			
			padding_x += calc_text.x + 14;
		}

		index_tab++;
	}
}