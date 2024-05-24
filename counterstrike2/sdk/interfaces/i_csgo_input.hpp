#pragma once

#include "../../signatures.hpp"

#include "../math/vector.hpp"
#include "../classes/user_cmd.hpp"
#include "../../utilities/utilities.hpp"

enum csgo_input_vtable
{
	MOUSE_INPUT = 10
};

class c_input_message
{
public:
    int32_t render_tick_count; //0x0000
    float render_fraction; //0x0004
    int32_t player_tick_count; //0x0008
    float player_fraction; //0x000C
    vector angle; //0x0010
    vector position; //0x001C
    char pad_0028[40]; //0x0028
    int32_t N000005D8; //0x0050
    char pad_0054[4]; //0x0054
    int32_t N000005D9; //0x0058
    int32_t N000005E5; //0x005C
}; //Size: 0x0060

class c_input_message_pb
{
public:
    c_input_message history[4];
};

class c_input_messages
{
public:
    int64_t size;
    c_input_message_pb* pb; //0x0000
}; //Size: 0x01E0

class subtick_button
{
public:
    int64_t button; //0x0000
    float forward; //0x0008
    float side; //0x000C
};

class subtick_button_pb
{
public:
    char pad[0x158];
    vector angle;
};

class subtick_buttons
{
public:
    int64_t size;
    subtick_button_pb* pb;
};

class i_csgo_input
{
public:
    char pad_0000[592]; //0x0000
    c_user_cmd cmd_array[150]; //0x0250
    char pad_5200[1]; //0x5200
    bool can_thirdperson; //0x5201
    char pad_5202[6]; //0x5202
    vector camera_angle; //0x5208
    char pad_5214[16]; //0x5214
    int32_t sequence; //0x5224
    int32_t prev_sequence; //0x5228
    char pad_522C[64]; //0x522C
    int32_t subtick_count; //0x526C
    char pad_5270[288]; //0x5270
    vector view_angle; //0x5390
    char pad_539C[140]; //0x539C
    subtick_buttons subtick_cache; //0x542C
    char pad_543C[168]; //0x543C
    c_input_messages input_message; //0x54E4
    char pad_54F4[312]; //0x54F4

public:
    c_user_cmd* get_user_cmd(int sequence)
    {
        return &cmd_array[sequence % 150];
    }
};