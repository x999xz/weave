#pragma once

#include "../classes/c_resource_binding.h"
#include "../classes/c_strong_handle.h"
#include "c_particle_snapshot.h"

class color_t;
class vector;

class particle_effect
{
public:
    const char* name{};
    char pad[0x30]{};
};

class particle_information
{
public:
    float time{};
    float width{};
    float unk2{};
};

class particle_data
{
public:
    vector* positions{};
    char pad[0x50]{};
    float* times{};
    void* unk_ptr{};
    char pad2[0x10];
    float* times2{};
    void* unk_ptr2{};
};

struct particle_color
{
    float r;
    float g;
    float b;
};

class c_game_particle_manager_system
{
public:
    void create_effect_index(unsigned int* effect_index, particle_effect* effect_data);
    void create_effect(unsigned int effect_index, int unk, void* clr, int unk2);
    void unk_function(int effect_index, unsigned int unk, const strong_handle<c_particle_snapshot>* handle);
};