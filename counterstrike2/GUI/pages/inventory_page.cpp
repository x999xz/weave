#include "../GUI.h"
#include "../../utilities/fnv.h"
#include "../../sdk/vtex/VTexParser.h"
#include "../sdk/sdk.hpp"
#include <codecvt>

render_color get_color_skin(int rarity)
{
	switch (rarity)
	{
	case 1:
		return render_color(177, 196, 217);
		break;
	case 2:
		return render_color(95, 153, 217);
		break;
	case 3:
		return render_color(76, 106, 255);
		break;
	case 4:
		return render_color(137, 72, 255);
		break;
	case 5:
		return render_color(211, 45, 230);
		break;
	case 6:
		return render_color(235, 76, 76);
		break;
	}

	return render_color::white();
}

void init_skin_image(gui_skins& skin)
{
	if (skin.type != type_glove) {
		for (auto& it : g_gui->item_weapons[skin.item_def])
		{
			if (!it.path_image.data())
				continue;

			auto vtex = VTexParser::Load(it.path_image.c_str());

			if (vtex.data.empty())
				continue;

			it.texture_id = g_render->create_texture_rgba(vtex.data, vtex.w, vtex.h);
			it.is_initilization = true;
		}
	}
	else {
		for (auto& it : g_gui->item_glove)
		{
			if (!it.path_image.data())
				continue;

			auto vtex = VTexParser::Load(it.path_image.c_str());

			if (vtex.data.empty())
				continue;

			it.texture_id = g_render->create_texture_rgba(vtex.data, vtex.w, vtex.h);
			it.is_initilization = true;
		}
	}
}

void init_skin()
{
	for (auto& it : g_gui->skin_added)
	{
		if (!it.path_image.data())
			return;

		if (it.is_initilization)
			continue;

		auto vtex = VTexParser::Load(it.path_image.c_str());

		if (vtex.data.empty())
			continue;

		it.texture_id = g_render->create_texture_rgba(vtex.data, vtex.w, vtex.h);
		it.is_initilization = true;
	}
}

void init_stickers_image()
{
	for (auto& it : g_gui->item_stickers)
	{
		if (!it.path_image.data())
			return;

		auto vtex = VTexParser::Load(it.path_image.c_str());

		if (vtex.data.empty())
			continue;

		it.texture_id = g_render->create_texture_rgba(vtex.data, vtex.w, vtex.h);
		it.is_initilization = true;
	}
}

void c_gui::inventory_page() {
	if (inventory_tab == 0)
	{
		render_position padding{};
		if (m_scrollbar.find(FNV32("items_added")) == m_scrollbar.end())
			m_scrollbar.try_emplace(FNV32("items_added"));

		begin_group(xorstr_("Items List"), render_size(740, 396), false);

		int i{};
		auto position = get_position() + render_position(10, 10);
		g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));
		g_render->rect_filled(position, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);
		g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
		g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

		g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
		g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));

		auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, xorstr_("Add Item"));
		g_render->add_text(xorstr_("Add Item"), position + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12);
		g_render->pop_limit();

		if (is_hovered_pressed(rect_(position, render_size(100, 100))) && has_pressed(VK_LBUTTON))
		{
			m_scrollbar[FNV32("item_default")] = {};
			inventory_tab = 1;
		}

		i++;
		padding.x += 122;

		bool is_remove = false;
		int remove_id = 0;

		for (auto skin : skin_added)
		{
			if (!skin.is_initilization)
			{
				std::thread thread(init_skin);
				thread.detach();
			}
			g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), get_position() + render_size(window_size.x, window_size.y - 109));
			position = get_position() - render_position(0, m_scrollbar[FNV32("items_added")].lerp_value) + render_position(10, 10);

			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

			g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
			g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
			g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

			g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
			g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
			g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));

			if (skin.is_initilization)
			{
				g_render->set_limit(position + padding + render_position(13, 10), render_size(75, 56));
				g_render->add_texture(position + padding + render_position(13, 10), render_size(75, 56), skin.texture_id);
				g_render->pop_limit();
			}

			g_render->set_limit(position + padding + render_position(10, 67), render_size(80, 33));
			g_render->add_text(skin.name, position + padding + render_position(10, 67), render_color::white(), g_render->get_font(0), 12.f);
			g_render->add_text(skin.paint_name, position + padding + render_position(10, 84), render_color(86, 86, 87), g_render->get_font(0), 12.f);
			g_render->pop_limit();

			g_render->pop_limit();

			auto backup_cursor = m_cursor_pos_;

			m_cursor_pos_ += padding;
			if (begin_popup(std::format("delete_item_{}", i), { render_size(100, 100) }, render_size(90, 40), VK_RBUTTON))
			{
				g_render->rect_filled(get_position() + render_position(10, 10), render_size(70, 20), render_color(render_color(40, 40, 40)), 0, 5.f);
				auto x = get_position() + render_position(10, 10) + (render_size(70, 20) * 0.5f);
				x -= g_render->get_font(0)->calc_text_size(11.f, FLT_MAX, FLT_MAX, "Delete") * 0.5f;
				g_render->add_text("Delete", x, render_color::white(), g_render->get_font(0), 11.f);

				if (is_hovered_pressed(rect_(get_position() + render_position(10, 10), render_size(70, 20))) && has_pressed(VK_LBUTTON))
				{
					is_remove = true;
					remove_id = i - 1;
					m_popup.find(std::hash<std::string>()(std::format("delete_item_{}", i)))->second.is_open_ = false;
				}
			}

			end_popup();

			m_cursor_pos_ = backup_cursor;

			if ((i % 6) == 5)
			{
				padding.x = 0;
				padding.y += 122;
			}
			else
			{
				padding.x += 122;
			}
			i++;
		}

		if (is_remove)
		{
			auto skin = skin_added[remove_id];
			auto soc_data = Interfaces::m_cs_inventory_manager->get_local_inventory()->get_soc_data_for_item(skin.id);
			Interfaces::m_cs_inventory_manager->get_local_inventory()->remove_econ_item(soc_data);
			skin_added.erase(skin_added.begin() + remove_id);
		}

		end_group();
	}
	else if (inventory_tab == 1)
	{
		render_position padding{};

		if (m_scrollbar.find(FNV32("item_default")) == m_scrollbar.end())
			m_scrollbar.try_emplace(FNV32("item_default"));

		begin_group(xorstr_("Weapon List"), render_size(740, 396), false);

		int i{};
		auto position = get_position() - render_position(0, m_scrollbar[FNV32("item_default")].lerp_value) + render_position(10, 10);
		g_render->set_limit(get_position(), render_size(window_size.x, window_size.y - 120));
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

		g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
		g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

		g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
		g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));


		auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, xorstr_("<- Back"));
		g_render->add_text(xorstr_("<- Back"), position + padding + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12.f);

		if (is_hovered_pressed(rect_(position, render_size(100, 100))) && has_pressed(VK_LBUTTON))
		{
			inventory_tab = 0;
		}

		i++;
		padding.x += 122;

		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

		g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, render_color::white());
		g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(render_color::white(), render_color(13, 13, 14), render_color::white(), render_color(13, 13, 14)), 0);
		g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), render_color::white(), render_color(13, 13, 14));

		g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color::white());
		g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color::white(), render_color(13, 13, 14), render_color::white()), 0);
		g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), render_color::white(), render_color(13, 13, 14));

		g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
		g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), item_knife_default[0].texture_id);
		g_render->pop_limit();

		g_render->add_text(xorstr_("Knife"), position + padding + render_position(10, 80), render_color::white(), g_render->get_font(0), 12.f);


		if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
		{
			m_scrollbar[FNV32("knife_default")] = {};
			inventory_tab = 3;
		}

		i++;
		padding.x += 122;

		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

		g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, render_color::white());
		g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(render_color::white(), render_color(13, 13, 14), render_color::white(), render_color(13, 13, 14)), 0);
		g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), render_color::white(), render_color(13, 13, 14));

		g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color::white());
		g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color::white(), render_color(13, 13, 14), render_color::white()), 0);
		g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), render_color::white(), render_color(13, 13, 14));

		g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
		g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), item_agent[2].texture_id);
		g_render->pop_limit();

		g_render->add_text(xorstr_("Agent"), position + padding + render_position(10, 80), render_color::white(), g_render->get_font(0), 12.f);


		if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
		{
			m_scrollbar[FNV32("agent")] = {};
			inventory_tab = 2;
		}

		i++;
		padding.x += 122;

		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

		g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, render_color::white());
		g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(render_color::white(), render_color(13, 13, 14), render_color::white(), render_color(13, 13, 14)), 0);
		g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), render_color::white(), render_color(13, 13, 14));

		g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color::white());
		g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color::white(), render_color(13, 13, 14), render_color::white()), 0);
		g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), render_color::white(), render_color(13, 13, 14));

		g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
		g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), item_glove[1].texture_id);
		g_render->pop_limit();

		g_render->add_text(xorstr_("Glove"), position + padding + render_position(10, 80), render_color::white(), g_render->get_font(0), 12.f);


		if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
		{
			m_scrollbar[FNV32("glove")] = {};
			inventory_tab = 7;
		}

		i++;
		padding.x += 122;

		g_render->pop_limit();

		float max_size = std::ceil(float(item_default.size() + i) / 6.f) * 122;
		max_size -= (122 * 3);
		max_size = std::max(0.f, max_size);

		for (auto skin : item_default)
		{
			auto rect = rect_(position + padding, render_size(100, 100));

			bool has_not_visible = rect.max.y < get_position().y - 11 || rect.min.y > get_position().y + window_size.y - 120;

			if (rect.min.y > get_position().y + window_size.y - 120)
				break;

			if (!has_not_visible)
			{

				g_render->set_limit(get_position(), render_size(window_size.x, window_size.y - 120));

				if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
				{
					m_scrollbar[FNV32("skin_weapon")] = {};
					inventory_tab = 4;
					skins_item_def = skin.item_def;
				}

				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

				g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
				g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

				g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
				g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));

				//g_render->rect_filled(position + padding + render_position(0, 75), render_size(95, 20), render_color(20, 20, 20), 0, 10.f, render_rounding_flags_::ROUND_RECT_BOT);

				g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
				g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), skin.texture_id);
				g_render->pop_limit();

				g_render->set_limit(position + padding + render_position(10, 67), render_size(90, 33));
				g_render->add_text(skin.name, position + padding + render_position(10, 80), render_color::white(), g_render->get_font(0), 12.f);
				g_render->pop_limit();

				g_render->pop_limit();
			}

			if ((i % 6) == 5)
			{
				padding.x = 0;
				padding.y += 122;
			}
			else
			{
				padding.x += 122;
			}
			i++;
		}

		if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == FNV32("Menu"))
		{
			m_scrollbar[FNV32("item_default")].value += 122 * -g_input_system->get_scroll();
			m_scrollbar[FNV32("item_default")].value = std::max(0.f, m_scrollbar[FNV32("item_default")].value);
			m_scrollbar[FNV32("item_default")].value = std::clamp(m_scrollbar[FNV32("item_default")].value, 0.f, max_size);
			g_input_system->reset_scrolling();
		}

		m_scrollbar[FNV32("item_default")].update();

		end_group();
	}
	else if (inventory_tab == 2)
	{
		render_position padding{};
		int i = 1;

		if (m_scrollbar.find(FNV32("agent")) == m_scrollbar.end())
			m_scrollbar.try_emplace(FNV32("agent"));

		begin_group("Agent List", render_size(740, 396), false);

		auto position = get_position() - render_position(0, m_scrollbar[FNV32("agent")].lerp_value) + render_position(10,10);
		g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

		g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
		g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

		g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
		g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));


		auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, "<- Back");
		g_render->add_text("<- Back", position + padding + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12.f);
		g_render->pop_limit();

		if (is_hovered_pressed(rect_(position + padding, render_size(95, 95))) && has_pressed(VK_LBUTTON))
		{
			inventory_tab = 0;
		}

		padding.x += 122;

		float max_size = std::ceil(float(item_agent.size() + i) / 6.f) * 122;
		max_size -= (122 * 3);
		max_size = std::max(0.f, max_size);

		for (auto skin : item_agent)
		{
			auto rect = rect_(position + padding, render_size(100, 100));

			bool has_not_visible = rect.max.y < get_position().y - 11 || rect.min.y > get_position().y + window_size.y - 120;

			if (rect.min.y > get_position().y + window_size.y - 120)
				break;

			if (!has_not_visible)
			{
				g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));

				if (is_hovered_pressed(rect) && has_pressed(VK_LBUTTON))
				{
					inventory_tab = 0;

					c_econ_item new_econ_item = c_econ_item();
					auto pItem = new_econ_item.create_instance();
					if (pItem) {
						auto pInventory = Interfaces::m_cs_inventory_manager->get_local_inventory();

						auto highestIDs = pInventory->get_highest_id();

						pItem->id = highestIDs.first + 1;
						pItem->account_id = uint32_t(pInventory->get_owner().m_id);
						pItem->def_index = skin.item_def;
						pItem->rarity = skin.rarity;

						pInventory->add_econ_item(pItem);
					}
					auto added_item = skin;
					skin.id = pItem->id;
					skin_added.push_back(skin);
				}

				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

				g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
				g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

				g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
				g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));

				g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
				g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), skin.texture_id);
				g_render->pop_limit();

				g_render->set_limit(position + padding + render_position(0, 80), render_size(95, 20));
				g_render->add_text(skin.name, position + padding + render_position((95 * 0.5f) - g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, skin.name.c_str()).x / 2, 80), render_color::white(), g_render->get_font(0), 11.f);
				g_render->pop_limit();

				g_render->pop_limit();
			}

			if ((i % 6) == 5)
			{
				padding.x = 0;
				padding.y += 122;
			}
			else
			{
				padding.x += 122;
			}
			i++;
		}

		if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == FNV32("Menu"))
		{
			m_scrollbar[FNV32("agent")].value += 122 * -g_input_system->get_scroll();
			m_scrollbar[FNV32("agent")].value = std::max(0.f, m_scrollbar[FNV32("agent")].value);
			m_scrollbar[FNV32("agent")].value = std::clamp(m_scrollbar[FNV32("agent")].value, 0.f, max_size);
			g_input_system->reset_scrolling();
		}

		m_scrollbar[FNV32("agent")].update();
	}
	else if (inventory_tab == 3)
	{
		if (skins_item_def == -1)
		{
			render_position padding{};
			int i = 1;

			if (m_scrollbar.find(FNV32("knife_default")) == m_scrollbar.end())
				m_scrollbar.try_emplace(FNV32("knife_default"));

			begin_group("Knife List", render_size(740, 396), false);

			auto position = get_position() - render_position(0, m_scrollbar[FNV32("knife_default")].lerp_value) + render_position(10,10);
			g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

			g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
			g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

			g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
			g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));


			auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, "<- Back");
			g_render->add_text("<- Back", position + padding + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12.f);
			g_render->pop_limit();

			if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
			{
				inventory_tab = 0;
			}

			padding.x += 122;

			float max_size = std::ceil(float(item_knife_default.size() + i) / 6.f) * 122;
			max_size -= (122 * 3);
			max_size = std::max(0.f, max_size);

			for (auto skin : item_knife_default)
			{
				auto rect = rect_(position + padding, render_size(100, 100));

				bool has_not_visible = rect.max.y < get_position().y - 11 || rect.min.y > get_position().y + window_size.y - 120;

				if (rect.min.y > get_position().y + window_size.y - 120)
					break;

				if (!has_not_visible)
				{

					g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));

					if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
					{
						skins_item_def = skin.item_def;
						m_scrollbar[FNV32("knife_skin")] = {};
					}

					g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
					g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

					g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
					g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
					g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

					g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
					g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
					g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));


					g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
					g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), skin.texture_id);
					g_render->pop_limit();

					g_render->set_limit(position + padding + render_position(0, 80), render_size(95, 20));
					g_render->add_text(skin.name, position + padding + render_position((95 * 0.5f) - g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, skin.name.c_str()).x / 2, 80), render_color::white(), g_render->get_font(0), 11.f);
					g_render->pop_limit();
					g_render->pop_limit();

				}

				if ((i % 6) == 5)
				{
					padding.x = 0;
					padding.y += 122;
				}
				else
				{
					padding.x += 122;
				}
				i++;
			}

			if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == FNV32("Menu"))
			{
				m_scrollbar[FNV32("knife_default")].value += 122 * -g_input_system->get_scroll();
				m_scrollbar[FNV32("knife_default")].value = std::max(0.f, m_scrollbar[FNV32("knife_default")].value);
				m_scrollbar[FNV32("knife_default")].value = std::clamp(m_scrollbar[FNV32("knife_default")].value, 0.f, max_size);
				g_input_system->reset_scrolling();
			}

			m_scrollbar[FNV32("knife_default")].update();

			end_group();
		}
		else
		{
			render_position padding{};
			int i = 1;

			if (m_scrollbar.find(FNV32("knife_skin")) == m_scrollbar.end())
				m_scrollbar.try_emplace(FNV32("knife_skin"));

			begin_group(xorstr_("Skin List"), render_size(740, 396), false);

			auto position = get_position() - render_position(0, m_scrollbar[FNV32("knife_skin")].lerp_value) + render_position(10,10);
			g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

			g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
			g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

			g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
			g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));


			auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, xorstr_("<- Back"));
			g_render->add_text(xorstr_("<- Back"), position + padding + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12.f);
			g_render->pop_limit();

			if (is_hovered_pressed(rect_(position + padding, render_size(95, 95))) && has_pressed(VK_LBUTTON))
			{
				inventory_tab = 0;
				skins_item_def = -1;
				return;
			}

			padding.x += 122;

			g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

			g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
			g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

			g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
			g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));

			auto item = std::find_if(item_knife_default.begin(), item_knife_default.end(), [this](auto x) {
				return x.item_def == skins_item_def;
				});
			if (item != item_knife_default.end())
			{
				g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), item->texture_id);
				g_render->set_limit(position + padding + render_position(0, 80), render_size(95, 20));
				g_render->add_text(item->name, position + padding + render_position((95 * 0.5f) - g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, item->name.c_str()).x / 2, 80), render_color::white(), g_render->get_font(0), 11.f);
				g_render->pop_limit();
			}
			g_render->pop_limit();

			if (is_hovered_pressed(rect_(position + padding, render_size(95, 95))) && has_pressed(VK_LBUTTON))
			{
				for (auto& sticker : current_stickers)
				{
					sticker.item_def = -1;
				}
				current_sticker = -1;
				inventory_tab = 5;
				current_skin = *item;
			}

			padding.x += 122;

			float max_size = std::ceil(float(item_weapons[skins_item_def].size() + i) / 6.f) * 122;
			max_size -= (122 * 3);
			max_size = std::max(0.f, max_size);

			for (auto& skin : item_weapons[skins_item_def])
			{
				const uint64_t skinKey = Helper_GetAlternateIconKeyForWeaponPaintWearItem(skin.item_def, skin.paint_id, 0);

				if (skin.skin_key != skinKey)
					continue;

				if (!skin.is_initilization && saved_item_def != skin.item_def)
				{
					saved_item_def = skin.item_def;
					std::thread thread(init_skin_image, std::ref(skin));
					thread.detach();
				}

				auto rect = rect_(position + padding, render_size(100, 100));

				bool has_not_visible = rect.max.y < get_position().y - 11 || rect.min.y > get_position().y + window_size.y - 120;

				if (rect.min.y > get_position().y + window_size.y - 120)
					break;

				if (!has_not_visible)
				{

					g_render->set_limit(get_position() - render_position(0, 11) + render_position(10,10), render_size(window_size.x, window_size.y - 109));

					if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
					{
						for (auto& sticker : current_stickers)
						{
							sticker.item_def = -1;
						}
						current_sticker = -1;
						inventory_tab = 5;
						current_skin = skin;
					}

					g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
					g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

					g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
					g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
					g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

					g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
					g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
					g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));

					g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
					if (skin.is_initilization)
						g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), skin.texture_id);
					g_render->pop_limit();

					g_render->set_limit(position + padding + render_position(0, 80), render_size(95, 20));
					g_render->add_text(skin.paint_name, position + padding + render_position((95 * 0.5f) - g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, skin.paint_name.c_str()).x / 2, 80), render_color::white(), g_render->get_font(0), 11.f);
					g_render->pop_limit();

					g_render->pop_limit();

				}

				if ((i % 6) == 5)
				{
					padding.x = 0;
					padding.y += 122;
				}
				else
				{
					padding.x += 122;
				}
				i++;
			}

			if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == FNV32("Menu"))
			{
				m_scrollbar[FNV32("knife_skin")].value += 122 * -g_input_system->get_scroll();
				m_scrollbar[FNV32("knife_skin")].value = std::max(0.f, m_scrollbar[FNV32("knife_skin")].value);
				m_scrollbar[FNV32("knife_skin")].value = std::clamp(m_scrollbar[FNV32("knife_skin")].value, 0.f, max_size);
				g_input_system->reset_scrolling();
			}

			m_scrollbar[FNV32("knife_skin")].update();

			end_group();
		}
	}
	else if (inventory_tab == 4)
	{
		if (skins_item_def != -1)
		{
			render_position padding{};
			int i = 1;

			if (m_scrollbar.find(FNV32("skin_weapon")) == m_scrollbar.end())
				m_scrollbar.try_emplace(FNV32("skin_weapon"));

			begin_group(xorstr_("Skin List"), render_size(740, 396), false);

			auto position = get_position() - render_position(0, m_scrollbar[FNV32("skin_weapon")].lerp_value) + render_position(10,10);
			g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
			g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

			g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
			g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

			g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
			g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
			g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));


			auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, xorstr_("<- Back"));
			g_render->add_text(xorstr_("<- Back"), position + padding + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12.f);
			g_render->pop_limit();

			if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
			{
				inventory_tab = 0;
				skins_item_def = -1;
			}

			padding.x += 122;

			float max_size = std::ceil(float(item_weapons[skins_item_def].size() + i) / 6.f) * 122;
			max_size -= (122 * 3);
			max_size = std::max(0.f, max_size);

			for (auto& skin : item_weapons[skins_item_def])
			{
				if (!skin.is_initilization && saved_item_def != skin.item_def)
				{
					saved_item_def = skin.item_def;
					std::thread thread(init_skin_image, std::ref(skin));
					thread.detach();
				}

				const uint64_t skinKey = Helper_GetAlternateIconKeyForWeaponPaintWearItem(skin.item_def, skin.paint_id, 0);

				if (skin.skin_key != skinKey)
					continue;

				auto rect = rect_(position + padding, render_size(100, 100));

				bool has_not_visible = rect.max.y < get_position().y - 11 || rect.min.y > get_position().y + window_size.y - 120;

				if (rect.min.y > get_position().y + window_size.y - 120)
					break;

				if (!has_not_visible)
				{

					g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));

					if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
					{
						for (auto& sticker : current_stickers)
						{
							sticker.item_def = -1;
						}
						current_sticker = -1;
						inventory_tab = 5;
						current_skin = skin;
					}

					g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
					g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

					g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
					g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
					g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

					g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
					g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
					g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));

					g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
					if (skin.texture_id != -1)
						g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), skin.texture_id);
					g_render->pop_limit();

					g_render->set_limit(position + padding + render_position(0, 80), render_size(95, 20));
					g_render->add_text(skin.paint_name, position + padding + render_position(10, 80), render_color::white(), g_render->get_font(0), 11.f);
					g_render->pop_limit();

					g_render->pop_limit();
				}

				if ((i % 6) == 5)
				{
					padding.x = 0;
					padding.y += 122;
				}
				else
				{
					padding.x += 122;
				}
				i++;
			}

			if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == FNV32("Menu"))
			{
				m_scrollbar[FNV32("skin_weapon")].value += 122 * -g_input_system->get_scroll();
				m_scrollbar[FNV32("skin_weapon")].value = std::max(0.f, m_scrollbar[FNV32("skin_weapon")].value);
				m_scrollbar[FNV32("skin_weapon")].value = std::clamp(m_scrollbar[FNV32("skin_weapon")].value, 0.f, max_size);
				g_input_system->reset_scrolling();
			}

			m_scrollbar[FNV32("skin_weapon")].update();

			end_group();
		}
	}
	else if (inventory_tab == 5)
	{

		if (skins_item_def != -1)
		{
			render_position padding{};
			int i = 1;

			set_cursor_pos(get_cursor_pos() + render_position(10, 0));

			begin_group("Skin Settings", render_size(310, 250));

			if (current_skin.type != type_glove) {
				slider("Stattrack", "Stattrack", stattrack, 0, 1337);
				slider("Paint Seed", "Paint Seed", paint_seed, 0, 1000);
			}
			slider("Paint Wear", "Paint Wear", paint_wear, 0, 100);

			auto pos = get_position() + padding_element;
			g_render->add_text("CustomName", pos + render_position(5, 3), render_color::white(), g_render->get_font(0), 11.f);
			g_render->rect_filled(pos + render_position(122, 0), render_size(160, 20), render_color(20, 20, 20), 0, 5);
			g_render->add_text(get_string_input(input_skin), pos + render_position(120, 3), render_color::white(), g_render->get_font(0), 11.f);

			if (is_hovered_pressed(rect_(pos + render_position(122, 0), render_size(120, 20))))
			{
				if (has_pressed(VK_LBUTTON))
					is_active_input_skin = true;
			}
			else if (is_active_input_skin)
			{
				if (has_pressed(VK_LBUTTON))
					is_active_input_skin = false;
			}

			end_group();

			begin_group("Skin Preview", render_size(420, 234));

			auto position = get_position() + render_position(10, 10);

			g_render->add_texture(position + padding + render_position(15, 10), render_size(230 * 0.9f, 177 * 0.9f), current_skin.texture_id);

			g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(current_skin.rarity));
			g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(current_skin.rarity), render_color(13, 13, 14), get_color_skin(current_skin.rarity), render_color(13, 13, 14)), 0);
			g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(current_skin.rarity), render_color(13, 13, 14));

			g_render->arc_line(position + padding + render_position(230 - 21, 177 - 11), 0, 90, 10, get_color_skin(current_skin.rarity));
			g_render->rect_filled_multi(position + padding + render_position(229, 147), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(current_skin.rarity), render_color(13, 13, 14), get_color_skin(current_skin.rarity)), 0);
			g_render->line(position + padding + render_position(220, 176), position + padding + render_position(220, 176) + render_size(-30, 1), get_color_skin(current_skin.rarity), render_color(13, 13, 14));

			padding.x += 255;

			int padding_y = 0;
			if (current_skin.type != type_item::type_knife && current_skin.type != type_glove)
			{
				for (int i{}; i < 5; i++)
				{
					if (current_stickers[i].item_def != -1) {
						g_render->add_texture(position + padding + render_position(5, 5 + padding_y), render_size(23, 23), current_stickers[i].texture_id);
						g_render->arc_line(position + padding + render_position(20, 10 + padding_y), 180, 90, 10, get_color_skin(current_stickers[i].rarity));
						g_render->rect_filled_multi(position + padding + render_position(0, 8 + padding_y), render_size(2, 10), render_color_multi(get_color_skin(current_stickers[i].rarity), render_color(13, 13, 14), get_color_skin(current_stickers[i].rarity), render_color(13, 13, 14)), 0);
						g_render->line(position + padding + render_position(10, 0 + padding_y), position + padding + render_position(10, 0 + padding_y) + render_size(6, 0), get_color_skin(current_stickers[i].rarity), render_color(13, 13, 14));

						g_render->arc_line(position + padding + render_position(33 - 21, 33 - 11 + padding_y), 0, 90, 10, get_color_skin(current_stickers[i].rarity));
						g_render->rect_filled_multi(position + padding + render_position(32, 20 + padding_y), render_size(1, 5), render_color_multi(render_color(13, 13, 14), get_color_skin(current_stickers[i].rarity), render_color(13, 13, 14), get_color_skin(current_stickers[i].rarity)), 0);
						g_render->line(position + padding + render_position(23, 32 + padding_y), position + padding + render_position(23, 32 + padding_y) + render_size(-7, 1), get_color_skin(current_stickers[i].rarity), render_color(13, 13, 14));

					}
					else {
						g_render->rect_filled(position + padding + render_position(0, 0 + padding_y), render_size(33, 33), render_color(86, 86, 87), 0, 10.f);
					}

					if (is_hovered_pressed(rect_(position + padding + render_position(0, 0 + padding_y), render_size(70, 70))) && has_pressed(VK_LBUTTON))
					{
						current_sticker = i;
						inventory_tab = 6;
						m_scrollbar[FNV32("stickers")] = {};
					}

					padding_y += 36;
				}
			}

			bool is_shift = has_hold(VK_SHIFT);

			for (int i{}; i < 256; i++)
			{
				if (i == VK_SHIFT)
					continue;

				if (i == VK_INSERT)
					continue;

				if (i == VK_LBUTTON)
					continue;

				if (!has_pressed(i))
					continue;

				if (!is_active_input_skin)
					continue;

				if (i == VK_BACK)
				{
					if (!input_skin.empty())
						input_skin.pop_back();
					continue;
				}

				if (input_skin.size() > 16)
					continue;

				input_skin += input_character_queue;
			}

			end_group();


			//set_cursor_pos(render_position(400, 65));


			g_render->rect_filled(position + padding + render_position(43, 52), render_size(112, 30), render_color(255, 139, 59), 0, 10.f);
			g_render->add_text("Add to inventory", position + padding + render_position(43, 52) + (render_size(112, 30) / 2) - (g_render->get_font(0)->calc_text_size(11, FLT_MAX,FLT_MAX,"Add to inventory") / 2), render_color::black(), g_render->get_font(0), 11);

			if (is_hovered_pressed(rect_(position + padding + render_position(43, 52), render_size(112, 30))) && has_pressed(VK_LBUTTON))
			{
				c_econ_item new_econ_item = c_econ_item();
				auto pItem = new_econ_item.create_instance();
				if (pItem) {
					auto pInventory = Interfaces::m_cs_inventory_manager->get_local_inventory();

					auto highestIDs = pInventory->get_highest_id();

					pItem->id = highestIDs.first + 1;
					pItem->account_id = uint32_t(pInventory->get_owner().m_id);
					pItem->def_index = current_skin.item_def;
					pItem->rarity = current_skin.rarity;

					float percent = float(paint_wear) / 100.f;

					pItem->set_stat_trak(stattrack);
					pItem->set_paint_kit(current_skin.paint_id);
					pItem->set_paint_seed(paint_seed);
					pItem->set_paint_wear(percent);
					for (int i{}; i < 5; i++)
					{
						if (current_stickers[i].item_def == -1)
							continue;

						pItem->set_sticker(i, current_stickers[i].item_def);
					}

					if (!input_skin.empty())
						pItem->set_custom_name(get_string_input(input_skin).c_str());

					pInventory->add_econ_item(pItem);
				}

				auto added_item = current_skin;
				added_item.paint_seed = paint_seed;
				added_item.paint_wear = paint_wear;
				added_item.stattrak = stattrack;

				for (int i{}; i < 5; i++)
				{
					added_item.stickers[i] = current_stickers[i].item_def;
				}

				if (!input_skin.empty())
					added_item.custom_name = get_string_input(input_skin);

				added_item.id = pItem->id;

				skin_added.push_back(added_item);
				inventory_tab = 0;
				skins_item_def = -1;
				paint_wear = 0;
				paint_seed = 0;
				input_skin.clear();
			}

			padding.y += 40;

			g_render->rect_filled(position + padding + render_position(43, 52), render_size(112, 30), render_color(255, 139, 59, 0), 0, 10.f);
			g_render->add_text("Cancel", position + padding + render_position(43, 52) + (render_size(112, 30) / 2) - (g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, "Cancel") / 2), render_color(255, 139, 59), g_render->get_font(0), 11);

			if (is_hovered_pressed(rect_(position + padding + render_position(43, 52), render_size(112, 30))) && has_pressed(VK_LBUTTON))
			{
				inventory_tab = 0;
			}
		}
	}
	else if (inventory_tab == 6)
	{
		render_position padding{};
		int i = 1;

		if (m_scrollbar.find(FNV32("stickers")) == m_scrollbar.end())
			m_scrollbar.try_emplace(FNV32("stickers"));

		begin_group("Sticker List", render_size(740, 396), false);

		auto position = get_position() - render_position(0, m_scrollbar[FNV32("stickers")].lerp_value) + render_position(10, 10);
		g_render->set_limit(get_position() - render_position(0, 11), render_size(window_size.x, window_size.y - 109));
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

		g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
		g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

		g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
		g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));


		auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, "<- Back");
		g_render->add_text("<- Back", position + padding + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12.f);
		g_render->pop_limit();

		if (is_hovered_pressed(rect_(position + padding, render_size(95, 95))) && has_pressed(VK_LBUTTON))
		{
			inventory_tab = 5;
			m_scrollbar[FNV32("stickers")].value = 0;
		}

		padding.x += 122;

		for (auto skin : item_stickers)
		{
			if (skin.type != type_item::type_sticker)
				continue;

			if (!skin.is_initilization && saved_item_def != 999)
			{
				saved_item_def = 999;
				std::thread thread(init_stickers_image);
				thread.detach();
			}

			auto rect = rect_(position + padding, render_size(100, 100));
			auto rect_visible = rect_(get_position(), { window_size.x, window_size.y - 120 });

			bool has_not_visible = rect.max.y < get_position().y - 11 || rect.min.y > get_position().y + window_size.y - 120;

			if (rect.min.y > get_position().y + window_size.y - 120)
				break;

			if (!has_not_visible)
			{
				g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));

				if (is_hovered_pressed(rect) && is_hovered_pressed(rect_visible) && has_pressed(VK_LBUTTON))
				{
					inventory_tab = 5;
					m_scrollbar[FNV32("stickers")].value = 0;
					current_stickers[current_sticker] = skin;
				}

				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

				g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
				g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

				g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
				g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));


				if (skin.texture_id != -1)
				{
					g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
					g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), skin.texture_id);
					g_render->pop_limit();
				}

				g_render->set_limit(position + padding + render_position(0, 80), render_size(95, 20));
				g_render->add_text(skin.name, position + padding + render_position((95 * 0.5f) - g_render->get_font(0)->calc_text_size(11, FLT_MAX, FLT_MAX, skin.name.c_str()).x / 2, 80), render_color::white(), g_render->get_font(0), 11.f);
				g_render->pop_limit();

				g_render->pop_limit();
			}

			if ((i % 6) == 5)
			{
				padding.x = 0;
				padding.y += 122;
			}
			else
			{
				padding.x += 122;
			}
			i++;
		}

		float max_size = int(item_stickers.size() + i / 6) * 122;
		max_size -= (122 * 3);
		max_size = std::max(0.f, max_size);

		if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == FNV32("Menu"))
		{
			m_scrollbar[FNV32("stickers")].value += 105 * -g_input_system->get_scroll();
			m_scrollbar[FNV32("stickers")].value = std::max(0.f, m_scrollbar[FNV32("stickers")].value);
			m_scrollbar[FNV32("stickers")].value = std::clamp(m_scrollbar[FNV32("stickers")].value, 0.f, max_size);
			g_input_system->reset_scrolling();
		}

		m_scrollbar[FNV32("stickers")].update();

		end_group();
	}
	else if (inventory_tab == 7) {
		render_position padding{};
		int i = 1;

		if (m_scrollbar.find(FNV32("glove")) == m_scrollbar.end())
			m_scrollbar.try_emplace(FNV32("glove"));

		begin_group(xorstr_("Skin List"), render_size(740, 396), false);

		auto position = get_position() - render_position(0, m_scrollbar[FNV32("glove")].lerp_value) + render_position(10, 10);
		g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
		g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

		g_render->arc_line(position + render_position(20, 10), 180, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(0, 8), render_size(2, 30), render_color_multi(render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14)), 0);
		g_render->line(position + render_position(10, 0), position + render_position(10, 0) + render_size(20, 0), render_color(255, 139, 59), render_color(13, 13, 14));

		g_render->arc_line(position + render_position(100 - 21, 100 - 11), 0, 90, 10, render_color(255, 139, 59));
		g_render->rect_filled_multi(position + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), render_color(255, 139, 59), render_color(13, 13, 14), render_color(255, 139, 59)), 0);
		g_render->line(position + render_position(90, 99), position + render_position(90, 99) + render_size(-30, 1), render_color(255, 139, 59), render_color(13, 13, 14));


		auto calc_text = g_render->get_font(0)->calc_text_size(12.f, FLT_MAX, FLT_MAX, xorstr_("<- Back"));
		g_render->add_text(xorstr_("<- Back"), position + padding + render_position(50, 50) - (calc_text / 2), render_color(221, 221, 221), g_render->get_font(0), 12.f);
		g_render->pop_limit();

		if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
		{
			inventory_tab = 0;
			skins_item_def = -1;
		}

		padding.x += 122;

		float max_size = std::ceil(float(item_glove.size() + i) / 6.f) * 122;
		max_size -= (122 * 3);
		max_size = std::max(0.f, max_size);

		for (auto& skin : item_glove)
		{
			if (!skin.is_initilization && saved_item_def != skin.item_def)
			{
				saved_item_def = skin.item_def;
				std::thread thread(init_skin_image, std::ref(skin));
				thread.detach();
			}

			const uint64_t skinKey = Helper_GetAlternateIconKeyForWeaponPaintWearItem(skin.item_def, skin.paint_id, 0);

			if (skin.skin_key != skinKey)
				continue;

			auto rect = rect_(position + padding, render_size(100, 100));

			bool has_not_visible = rect.max.y < get_position().y - 11 || rect.min.y > get_position().y + window_size.y - 120;

			if (rect.min.y > get_position().y + window_size.y - 120)
				break;

			if (!has_not_visible)
			{

				g_render->set_limit(get_position() - render_position(0, 11) + render_position(10, 10), render_size(window_size.x, window_size.y - 109));

				if (is_hovered_pressed(rect_(position + padding, render_size(100, 100))) && has_pressed(VK_LBUTTON))
				{
					for (auto& sticker : current_stickers)
					{
						sticker.item_def = -1;
					}
					current_sticker = -1;
					inventory_tab = 5;
					skins_item_def = skin.item_def;
					current_skin = skin;
				}

				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14, 0), 0, 0.f);
				g_render->rect_filled(position + padding, render_size(100, 100), render_color(13, 13, 14), 0, 10.f);

				g_render->arc_line(position + padding + render_position(20, 10), 180, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(0, 8), render_size(2, 30), render_color_multi(get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14)), 0);
				g_render->line(position + padding + render_position(10, 0), position + padding + render_position(10, 0) + render_size(20, 0), get_color_skin(skin.rarity), render_color(13, 13, 14));

				g_render->arc_line(position + padding + render_position(100 - 21, 100 - 11), 0, 90, 10, get_color_skin(skin.rarity));
				g_render->rect_filled_multi(position + padding + render_position(99, 70), render_size(1, 20), render_color_multi(render_color(13, 13, 14), get_color_skin(skin.rarity), render_color(13, 13, 14), get_color_skin(skin.rarity)), 0);
				g_render->line(position + padding + render_position(90, 99), position + padding + render_position(90, 99) + render_size(-30, 1), get_color_skin(skin.rarity), render_color(13, 13, 14));

				g_render->set_limit(position + padding + render_position(10, 10), render_size(80, 65));
				if (skin.texture_id != -1)
					g_render->add_texture(position + padding + render_position(10, 10), render_size(80, 65), skin.texture_id);
				g_render->pop_limit();

				g_render->set_limit(position + padding + render_position(0, 80), render_size(95, 20));
				g_render->add_text(skin.paint_name, position + padding + render_position(10, 80), render_color::white(), g_render->get_font(0), 11.f);
				g_render->pop_limit();

				g_render->pop_limit();
			}

			if ((i % 6) == 5)
			{
				padding.x = 0;
				padding.y += 122;
			}
			else
			{
				padding.x += 122;
			}
			i++;
		}

		if (g_input_system->get_scroll() != 0 && g_gui->m_hovered_window == FNV32("Menu"))
		{
			m_scrollbar[FNV32("glove")].value += 122 * -g_input_system->get_scroll();
			m_scrollbar[FNV32("glove")].value = std::max(0.f, m_scrollbar[FNV32("glove")].value);
			m_scrollbar[FNV32("glove")].value = std::clamp(m_scrollbar[FNV32("glove")].value, 0.f, max_size);
			g_input_system->reset_scrolling();
		}

		m_scrollbar[FNV32("glove")].update();

		end_group();
	}
}