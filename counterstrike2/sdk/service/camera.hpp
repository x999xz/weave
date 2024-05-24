#pragma once

#include "../sdk.hpp"

class C_fogplayerparams_t
{
public:
    //SCHEMA(C_fogplayerparams_t, m_hCtrl, m_hCtrl, c_handle);
};

class c_player_camera_services
{
public:
    //SCHEMA(CCSPlayerBase_CameraServices, m_iFOV, m_fov, int);
    //SCHEMA(CCSPlayerBase_CameraServices, m_iFOVStart, m_fov_start, int);
    //SCHEMA(CCSPlayerBase_CameraServices, m_hZoomOwner, m_handle_zoom_owner, c_handle);
    //SCHEMA(CPlayer_CameraServices, m_hTonemapController, m_handle_tonemap_controller, unsigned long);
    //SCHEMA(CPlayer_CameraServices, m_CurrentFog, m_current_fog, int);
    //SCHEMA(CPlayer_CameraServices, m_hOldFogController, m_handle_old_fog_controller, unsigned long);
    //SCHEMA(CPlayer_CameraServices, m_bOverrideFogColor, m_boverride_fog_color, bool);
    //SCHEMA(CPlayer_CameraServices, m_OverrideFogColor, m_override_fog_color, color_t);
    //SCHEMA(CPlayer_CameraServices, m_bOverrideFogStartEnd, m_boverride_fog_start_end, bool);
    //SCHEMA(CPlayer_CameraServices, m_fOverrideFogStart, m_override_fog_start, float);
    //SCHEMA(CPlayer_CameraServices, m_fOverrideFogEnd, m_override_fog_end, float);
    //SCHEMA_(CPlayer_CameraServices, m_PlayerFog, m_player_fog, C_fogplayerparams_t);
};

class c_cs_player_camera_services : public c_player_camera_services
{
public:
    __forceinline float m_last_shot_fov() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x224 );
    };
    __forceinline float m_death_cam_tilt() {
        return *reinterpret_cast<float*>(reinterpret_cast<std::uint64_t>(this) + 0x228 );
    };
    __forceinline c_handle handle_view_entity() {
        return *reinterpret_cast<c_handle*>(reinterpret_cast<std::uint64_t>(this) + 0x9C );
    };
    __forceinline c_utl_vector<c_handle> m_PostProcessingVolumes() {
    return *reinterpret_cast<c_utl_vector<c_handle>*>(reinterpret_cast<std::uint64_t>(this) + 0x120 );
};
public:
    float get_fov()
    {
        return CALL_VIRTUAL(float, 26, this);
    }
};