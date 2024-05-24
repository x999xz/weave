#pragma once

#include <cstdint>
#include <array>
#include <memory>

typedef union
{
	float  m128_f32[4];
	unsigned char m128_u32[4];
} fltx4;

#include "schema_offset.h"
#include "schema_system/schema_system.hpp"

#include "../utilities/hash.h"

#include "proto/proto.h"

#include "interfaces/virtual.hpp"

#include "math/color_t.hpp"
#include "math/vector.hpp"
#include "math/vector_2d.hpp"
#include "math/vector_4d.hpp"
#include "math/v_matrix.hpp"

#include "classes/c_utl_memory.h"
#include "classes/c_utl_memory_fixed_growable.h"
#include "classes/c_utl_vector.hpp"
#include "classes/c_utl_vector_fixed_glowable.h"
#include "classes/c_utl_binary_block.h"
#include "classes/c_utl_string.h"
#include "classes/c_utl_symbol_large.h"
#include "classes/c_utl_map.hpp"
#include "classes/c_utl_buffer.h"
#include "classes/c_buffer_string.h"

#include "classes/c_four_vectors.h"
#include "classes/c_four_vectors_2d.h"
#include "classes/c_four_quaternions.h"
#include "classes/c_quaternion_storage.h"
#include "classes/c_rn_plane.h"
#include "classes/c_transform.h"

#include "classes/c_fe_anim_stray_radius.h"
#include "classes/c_fe_axial_edge_bend.h"
#include "classes/c_fe_box_rigid.h"
#include "classes/c_fe_collision_plane.h"
#include "classes/c_fe_ctrl_offset.h"
#include "classes/c_fe_ctrl_os_offset.h"
#include "classes/c_fe_ctrl_soft_offset.h"
#include "classes/c_fe_effect_desc.h"
#include "classes/c_fe_fit_matrix.h"
#include "classes/c_fe_fit_weight.h"
#include "classes/c_fe_follow_node.h"
#include "classes/c_fe_jiggle_bone.h"
#include "classes/c_fe_indexed_jiggle_bone.h"
#include "classes/c_fe_kelager_bend2.h"
#include "classes/c_fe_morph_layer_depr.h"
#include "classes/c_fe_node_base.h"
#include "classes/c_fe_node_integrator.h"
#include "classes/c_fe_node_reverse_offset.h"
#include "classes/c_fe_node_wind_base.h"
#include "classes/c_fe_quad.h"
#include "classes/c_fe_rigid_collider_indices.h"
#include "classes/c_fe_rod_constraint.h"
#include "classes/c_fe_simd_anim_stray_radius.h"
#include "classes/c_fe_simd_node_base.h"
#include "classes/c_fe_simd_quad_t.h"
#include "classes/c_fe_simd_rod_constraint.h"
#include "classes/c_fe_simd_rod_constraint_anim.h"
#include "classes/c_fe_simd_spring_integrator.h"
#include "classes/c_fe_simd_tri.h"
#include "classes/c_fe_sphere_rigid.h"
#include "classes/c_fe_tapered_capsule_rigid.h"
#include "classes/c_fe_tapered_capsule_stretch.h"
#include "classes/c_fe_tree_children.h"
#include "classes/c_fe_tri.h"
#include "classes/c_fe_twist_constraint.h"
#include "classes/c_fe_vertex_map_desc.h"
#include "classes/c_fe_world_collision_params.h"

#include "classes/c_protobuff_binding.h"
#include "classes/c_network_serializer_pb.h"
#include "classes/c_msg_voice_audio.h"
#include "classes/c_svc_msg_voice_data.h"
#include "classes/c_clc_msg_voice_data.h"

#include "classes/c_particle_snapshot.h"

#include "classes/enums.hpp"

#include "classes/handle.hpp"

#include "classes/c_net_chan.hpp"
#include "classes/global_vars.hpp"
#include "classes/c_network_game_client.hpp"

#include "gc/c_gc_client_shared_object_type_cache.hpp"
#include "gc/c_gc_client_shared_object_cache.hpp"
#include "gc/c_gc_client.hpp"
#include "gc/c_gc_client_system.hpp"

#include "classes/c_econ_item_attribute_definition.h"
#include "classes/c_econ_item_def.hpp"
#include "classes/c_econ_scheme.hpp"
#include "classes/c_econ_item.hpp"

#include "classes/c_csgo_hud_chat.h"

#include "classes/c_cs_player_inventory.hpp"

#include "interfaces/interfaces.hpp"

#include "classes/c_shoot_position_history_entry_t.h"

#include "service/action_tracking.hpp"
#include "service/bullet.hpp"
#include "service/camera.hpp"
#include "service/item.hpp"
#include "service/movement.hpp"
#include "service/observer.hpp"
#include "service/weapon.hpp"
#include "service/ping.hpp"
#include "service/viewmodel.hpp"
#include "service/inventory_service.h"

#include "classes/user_cmd.hpp"

#include "classes/c_view_setup.hpp"
#include "classes/c_view_render.h"
#include "classes/c_render_game_system.hpp"
#include "classes/c_client_mode.hpp"

#include "classes/c_resource_binding.h"
#include "classes/c_strong_handle.h"

#include "classes/c_hitbox.hpp"
#include "classes/c_drawcalls.hpp"
#include "classes/c_attachments.hpp"
#include "classes/c_bones.hpp"
#include "classes/c_rendermesh.hpp"
#include "classes/c_phys_fe_model_desc.h"
#include "classes/c_physmodel.hpp"
#include "classes/c_perm_model_ext_part.h"
#include "classes/c_perm_model_info.h"
#include "classes/c_perm_model_data.h"
#include "classes/c_model.hpp"

#include "classes/c_bone_data.h"
#include "classes/c_model_state.h"

#include "classes/c_skeleton_instance.h"

#include "classes/c_scene_animatable_object.h"

#include "classes/c_anim_demo_manager.hpp"
#include "classes/c_anim_graph_settings_manager.hpp"
#include "classes/c_anim_tag_manager.hpp"

#include "classes/c_anim_skeleton.hpp"
#include "classes/c_animation_graph_visualization_manager.hpp"
#include "classes/c_anim_update.hpp"
#include "classes/c_anim_parameter_manager_updater.hpp"
#include "classes/c_anim_parameter_list_instance.hpp"

#include "classes/c_base_anim_graph_controller.hpp"
#include "classes/c_body_component_base_anim_graph.hpp"
#include "classes/c_csgo_player_anim_graph_state.hpp"
#include "classes/c_anim_component_manager_instance.hpp"
#include "classes/c_animation_graph_instance.hpp"

#include "classes/c_client_alpha_property.hpp"
#include "classes/c_collision_property.hpp"
#include "classes/c_game_scene_node.hpp"
#include "classes/c_base_entity.hpp"
#include "classes/c_base_model_entity.hpp"

#include "classes/c_base_player_controller.hpp"
#include "classes/c_cs_player_controller.hpp"

#include "classes/c_weapon_cs_base_v_data.hpp"
#include "classes/c_econ_item_view.hpp"
#include "classes/c_attribute_container.hpp"
#include "classes/c_econ_entity.hpp"
#include "classes/c_base_player_weapon.hpp"
#include "classes/c_weapon_cs_base.hpp"

#include "classes/c_base_grenade.h"
#include "classes/c_base_cs_grenade_projectile.h"

#include "classes/c_base_cs_grenade.h"
#include "classes/c_base_player_pawn.hpp"
#include "classes/c_csgo_viewmodel.hpp"
#include "classes/c_cs_player_pawn_base.hpp"
#include "classes/c_cs_player_pawn.hpp"
#include "classes/c_planted.hpp"
#include "classes/c_player_ping.hpp"
#include "classes/game_event_listener.hpp"
#include "classes/game_event_manager.hpp"

#include "classes/c_cs_game_rules.h"

#include "sdl/sdl.hpp"

#include "../core.hpp"