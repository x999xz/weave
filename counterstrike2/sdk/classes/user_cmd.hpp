#pragma once

#include <cstdint>
#include "../math/vector.hpp"
#include "../proto/proto.h"


enum InputBitMask_t
{
    IN_NONE = 0x0,
    IN_ALL = 0xffffffffffffffff,
    IN_ATTACK = 0x1,
    IN_JUMP = 0x2,
    IN_DUCK = 0x4,
    IN_FORWARD = 0x8,
    IN_BACK = 0x10,
    IN_USE = 0x20,
    IN_TURNLEFT = 0x80,
    IN_TURNRIGHT = 0x100,
    IN_MOVELEFT = 0x200,
    IN_MOVERIGHT = 0x400,
    IN_ATTACK2 = 0x800,
    IN_RELOAD = 0x2000,
    IN_SPEED = 0x10000,
    IN_JOYAUTOSPRINT = 0x20000,
    IN_FIRST_MOD_SPECIFIC_BIT = 0x100000000,
    IN_USEORRELOAD = 0x100000000,
    IN_SCORE = 0x200000000,
    IN_ZOOM = 0x400000000,
    IN_LOOK_AT_WEAPON = 0x800000000
};

enum EInButtonState : uint8_t
{
    IN_BUTTON_UP = 0,
    IN_BUTTON_DOWN,
    IN_BUTTON_DOWN_UP,
    IN_BUTTON_UP_DOWN,
    IN_BUTTON_UP_DOWN_UP,
    IN_BUTTON_DOWN_UP_DOWN,
    IN_BUTTON_DOWN_UP_DOWN_UP,
    IN_BUTTON_UP_DOWN_UP_DOWN,
    IN_BUTTON_STATE_COUNT
};

enum EButtonType : uint8_t
{
    HOLD,
    PRESSED,
    UNPRESSED
};

class c_cmd_qangle {
public:
    char pad_001[0x18];
    vector angles;
};

class c_cmd_buttons
{
public:
    char pad[0x18];
    std::uint64_t buttons[3];
};

class csgo_interpolation_info_pb
{
public:
    char pad[0x18];
    float fraction;
    int src_tick;
    int dst_tick;
};

class csgo_input_history_entry
{
public:
    char pad00[0x18];
    c_cmd_qangle* angle;
    char pad0x18[0x20];
    csgo_interpolation_info_pb* cl_interp; // 0x40
    csgo_interpolation_info_pb* sv_interp0; // 0x48
    csgo_interpolation_info_pb* sv_interp1; // 0x50 
    csgo_interpolation_info_pb* player_interp; // 0x58
    int render_tick_count;
    float render_fraction;
    int player_tick_count;
    float player_fraction;
    char pad3[0x12];
    std::uint32_t frame_number;
};

class csgo_input_history_entry_pb
{
public:
    std::uint32_t Count;
    char pad[0x4];
    std::uint64_t Memory;

    csgo_input_history_entry* Get(int i)
    {
        if (i < Count)
        {
            auto* cmd = (csgo_input_history_entry**)(Memory + 0x8);
            return cmd[i];
        }
        return nullptr;
    }
};

class c_subtick_move_step
{
public:
    char pad[0x10];
    std::uint32_t has_bits;
    char pad2[0x4];
    std::uint64_t buttons;
    bool pressed;
    std::int16_t unk;
    std::int8_t unk2;
    float when;
};

template <typename T>
struct RepeatedPtrField_t
{
    struct Rep_t
    {
        int m_nAllocatedSize;
        T* m_tElements[(std::numeric_limits<int>::max() - 2 * sizeof(int)) / sizeof(void*)];
    };

    void* m_pArena;
    int m_nCurrentSize;
    int m_nTotalSize;
    Rep_t* m_pRep;
};

class c_user_cmd_base : public message_lite
{
public:
    RepeatedPtrField_t<c_subtick_move_step> subtick_move;
    std::uintptr_t move_crc;
    c_cmd_buttons* buttons;
    c_cmd_qangle* view;
    int sequence;
    int tick_count;
    float forwardmove;
    float sidemove;
    float upmove; /* doesnt even exist prob */
    std::uint32_t impulse;
    std::uint32_t weapon_select;
    std::uint32_t random_seed;
    std::uint32_t mousedx;
    std::uint32_t mousedy;
    std::uint32_t pawn_entity_handle;
    bool hasbeenpredicted;

    void Set(int button, bool pressed);

    void UnSet(int button, bool pressed);
    void update_move_crc();
    std::uint8_t get_cache_size();
};

struct button_cmd
{
    void* ptr;
    std::uint64_t buttonstate[3];
};

struct button_pb_cmd
{
    void* ptr;
    std::uint64_t buttonstate[3];
};

class c_user_cmd {
public:
    char pad001[0x10];
    std::uint64_t unk_zalupa;
    RepeatedPtrField_t<csgo_input_history_entry> input_history;
    c_user_cmd_base* base;
    char pad[0x4];
    std::uint32_t attack_history_index[3];
    button_cmd buttons;
    char pad2[0x10];
    bool has_been_prediction;
    char pad3[0x9];
    char pad4[0x6];
public:
    void set_input_history_angle(vector& angles);
    c_subtick_move_step* create_subtick_step(void* arena);
    c_subtick_move_step* create_subtick();
    void add_subtick(bool pressed, int button, bool needs_delete = false);
    void set_attack_history(int index);
    void set_button_state(std::uint64_t button, EInButtonState call_type);
    void remove_button_state(std::uint64_t button);
};