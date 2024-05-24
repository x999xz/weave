#pragma once

#include <cstdint>
#include "../math/vector.hpp"
#include "../../utilities/utilities.hpp"

class c_game_event;
class c_cs_player_controller;

class c_buffer
{
public:
    char pad[0x8];
    const char* name;
};

class c_game_event_helper
{
public:
    c_game_event_helper(c_game_event* event) : event{ std::move(event) } {};
public:
    c_cs_player_controller* get_player_controller();
    c_cs_player_controller* get_attacker_controller();
    int get_damage();
    int get_health();

protected:
    c_game_event* event;
};

class c_game_event {
public:
    virtual ~c_game_event() = 0;
    virtual const char* get_name() const = 0;

    virtual void unk1() = 0;
    virtual void unk2() = 0;
    virtual void unk3() = 0;
    virtual void unk4() = 0;

    virtual bool get_bool(const char* key_name = nullptr, bool default_value = false) = 0;
    virtual int get_int(c_buffer* key_name = nullptr, bool default_value = false) = 0;
    virtual uint64_t get_uint64(const char* key_name = nullptr, uint64_t default_value = 0) = 0;
    virtual float get_float(const char* key_name = nullptr, float default_value = 0.f) = 0;
    virtual const char* get_string(const char* key_name = nullptr, const char* default_value = "") = 0;
    virtual void unk5() = 0;
    virtual void unk6() = 0;
    virtual void unk7() = 0;
    virtual void unk8() = 0;
    virtual void get_controller_id(int& controller_id, c_buffer* buffer = nullptr) = 0;
public:
    c_game_event_helper get_event_helper()
    {
        c_game_event_helper event_helper(this);
        return event_helper;
    }

    int get_int2(const char* name, bool unk);
    float get_float2(const char* name, bool unk);
};

class i_game_event_listener {
public:
    virtual ~i_game_event_listener() {}
    virtual void fire_game_event(c_game_event* event) = 0;
};