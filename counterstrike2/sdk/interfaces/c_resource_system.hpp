#pragma once

#include <cstdint>
#include "../math/vector.hpp"
#include "../../utilities/utilities.hpp"

class C_KeyString {
public:
    uintptr_t m_key;
    const char* m_string;

    C_KeyString(const char* string, bool finding_key = false) {
        m_string = string;
        m_key = finding_key ? FindKey(string) : -1;
    }

    C_KeyString(const char* string, int key) {
        m_string = string;
        m_key = key;
    }

    uintptr_t FindKey(const char* name);
};

class i_material 
{
public:
    const char* get_name() {
        using function_t = const char*(__thiscall*)(i_material*);
        return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[0](this);
    }

    const char* get_name_with_mod() {
        using function_t = const char* (__thiscall*)(i_material*);
        return (*reinterpret_cast<function_t**>(std::uintptr_t(this)))[1](this);
    }
};

class i_material_system
{
public:
    i_material*** FindMaterial(i_material*** material, const char* material_name) {
        return CALL_VIRTUAL(i_material***, 14, this, material, material_name);
    }

    i_material** CreateMaterial(i_material*** empty_material, const char* new_material_name, void* material_data)
    {
        return CALL_VIRTUAL(i_material**, 29, this, empty_material, new_material_name, material_data, 0, 0, 0, 0, 0, 1);
    }

    void SetCreateDataMaterial(void* data, i_material*** material)
    {
        return CALL_VIRTUAL(void, 37, this, material, data);
    }

    void SetColor(void* data, color_t color)
    {
        *(byte*)((uintptr_t)data + 0x40) = color.get_red();
        *(byte*)((uintptr_t)data + 0x41) = color.get_green();
        *(byte*)((uintptr_t)data + 0x42) = color.get_blue();
        *(byte*)((uintptr_t)data + 0x43) = color.get_alpha();
    }

    void SetMaterialShaderType(void* data, const char* shader_name);
    void SetMaterialFunctions(void* data, const char* functions_name, int value);
};

struct resource_array_t {
	uint64_t m_nCount;			// 0x0
	i_material*** m_aResources;	// 0x8
	uint64_t pad_0010[3];		// 0x10
};

class c_resource_system
{
public:
    void enumerate_material(std::uint64_t hash, resource_array_t* array, std::uint8_t flags);
};