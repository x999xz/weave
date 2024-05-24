#pragma once

#include "../sdk.hpp"

class c_base_entity;

class c_base_model_entity : public c_base_entity
{
public:
    __forceinline color_t render_color() {
        return *reinterpret_cast<color_t*>(reinterpret_cast<std::uint64_t>(this) + 0xA81 );
    };
    __forceinline vector view_offset() {
        return *reinterpret_cast<vector*>(reinterpret_cast<std::uint64_t>(this) + 0xC58 );
    };
    __forceinline c_client_alpha_property* client_alpha_property() {
        return *reinterpret_cast<c_client_alpha_property**>(reinterpret_cast<std::uint64_t>(this) + 0xC88 );
    };
public:
    bool is_view_model() { return CALL_VIRTUAL(bool, 241, this); }
};