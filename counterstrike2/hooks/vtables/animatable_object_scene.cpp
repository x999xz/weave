// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

void hooks::draw_scene_object::hook(void* animtable_scene_object, void* dx11, c_scene_data* scene_data, int unknown_bool, void* scene_view, void* scene_layer, void* unknown_pointer, void* unknown)
{
    g_cs2->m_latest_hook = LoggerHack::DrawSceneObject;
    add_trace(__PRETTY_FUNCTION__);

    g_cs2->local_player = Interfaces::entity_list->get_split_screen_view_player(0);
    //g_cs2->local_player = g_cs2->get_localplayer();

    if(!Interfaces::engine->is_in_game() || !Interfaces::engine->is_connected())
     return draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);

    if (!g_cs2->local_player)
        return draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);

    if (!scene_data->scene_animatable_object || !scene_data->scene_animatable_object->skeleton_instance || !scene_data->scene_animatable_object->skeleton_instance->get_owner_pawn())
        return draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);

    auto player = scene_data->scene_animatable_object->skeleton_instance->get_owner_pawn();
    
  if (HASH_RT(player->get_class_name()) == HASH("C_CSPlayerPawn"))
    {
        if (player->is_enemy())
        {
            if (player->is_alive() && !player->has_gun_immunity())
            {
                bool is_original = !g_visuals->chams_invisible && !g_visuals->chams_visible;

                if (is_original)
                    return draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);

                if (g_visuals->chams_invisible)
                {
                    scene_data->material = g_chams->get_material(g_visuals->chams_type, true);
                    Interfaces::material_system->SetColor(scene_data, color_t(g_visuals->chams_invisible_clr));
                    draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);
                }

                if (g_visuals->chams_visible)
                {
                    scene_data->material = g_chams->get_material(g_visuals->chams_type, false);
                    Interfaces::material_system->SetColor(scene_data, color_t(g_visuals->chams_visible_clr));
                    
                    draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);
                }
            }
            else
            {
                //scene_data->material = g_chams->get_material(0, false);
                //Interfaces::material_system->SetColor(scene_data, color_t(255, 0, 0));

                draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);
            }
        }
        else
            return draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);
    }
    else if (scene_data->scene_animatable_object->skeleton_instance->get_owner_pawn()->is_attachment())
    {
        if (g_visuals->attachment_chams && Interfaces::csgo_input->can_thirdperson)
        {
            scene_data->material = g_chams->get_material(1, false);
            Interfaces::material_system->SetColor(scene_data, color_t(g_visuals->attachment_chams_clr));
        }

        draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);
    }
    else
    {
        return draw_scene_object_original(animtable_scene_object, dx11, scene_data, unknown_bool, scene_view, scene_layer, unknown_pointer, unknown);
    }
}