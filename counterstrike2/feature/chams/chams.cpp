// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../../sdk/sdk.hpp"
#include "chams.h"
#include "../../Logging.h"

i_material* find_material(const char* vmat)
{
    i_material** custom_material;

    Interfaces::material_system->FindMaterial(&custom_material, vmat);

    return *custom_material;
}

void c_chams::initilization()
{
    add_trace(__PRETTY_FUNCTION__);
    Materials[0][0] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    Shader = "csgo_unlitgeneric.vfx"
    F_DISABLE_Z_BUFFERING = 0
    F_BLEND_MODE = 1
    F_TRANSLUCENT = 1
    g_vColorTint = [1.000000, 1.000000, 1.000000, 0.000000]
    g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
    g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
    g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
    g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
    g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
    g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
    g_tRoughness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
})");
    Materials[0][1] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    Shader = "csgo_unlitgeneric.vfx"
    F_DISABLE_Z_BUFFERING = 1
    F_BLEND_MODE = 1
    F_TRANSLUCENT = 1
    g_vColorTint = [1.000000, 1.000000, 1.000000, 0.000000]
    g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
    g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
    g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
    g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
    g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
    g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
    g_tRoughness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
})");
    Materials[1][0] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    Shader = "csgo_complex.vfx"
                F_IGNOREZ = 0
                F_DISABLE_Z_WRITE = 0
                F_DISABLE_Z_BUFFERING = 0
F_RENDER_BACKFACES = 0
	F_TRANSLUCENT = 1
    F_PAINT_VERTEX_COLORS = 1
    g_vColorTint = [1.000000, 1.000000, 1.000000, 1.000000]
    TextureNormal = resource:"materials/default/default_normal.tga"
    g_tAmbientOcclusion = resource:"materials/default/default_ao_tga_559f1ac6.vtex"
    g_tColor = resource:"materials/default/default_color_tga_72dcfbfd.vtex"
    g_tNormal = resource:"materials/default/default_normal_tga_7be61377.vtex"
})");
    Materials[1][1] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    Shader = "csgo_complex.vfx"
                F_IGNOREZ = 1
                F_DISABLE_Z_WRITE = 1
                F_DISABLE_Z_BUFFERING = 1
F_RENDER_BACKFACES = 0
	F_TRANSLUCENT = 1
    F_PAINT_VERTEX_COLORS = 1
    g_vColorTint = [1.000000, 1.000000, 1.000000, 1.000000]
    TextureNormal = resource:"materials/default/default_normal.tga"
    g_tAmbientOcclusion = resource:"materials/default/default_ao_tga_559f1ac6.vtex"
    g_tColor = resource:"materials/default/default_color_tga_72dcfbfd.vtex"
    g_tNormal = resource:"materials/default/default_normal_tga_7be61377.vtex"
})");
    Materials[2][0] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
                Shader = "solidcolor.vfx"
                F_BLEND_MODE = 1
                g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
                g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
                g_tRoughness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
                g_tMetalness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
                g_tAmbientOcclusion = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
                F_IGNOREZ = 0
                F_DISABLE_Z_WRITE = 0
                F_DISABLE_Z_BUFFERING = 0
                F_RENDER_BACKFACES = 0
                g_vColorTint = [50.0, 50.0, 50.0, 50.0]
})");
    Materials[2][1] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
				Shader = "solidcolor.vfx"
				g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
				g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
				g_tRoughness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
				g_tMetalness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
				g_tAmbientOcclusion = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
				F_IGNOREZ = 1
				F_DISABLE_Z_WRITE = 1
				F_DISABLE_Z_BUFFERING = 1
				F_RENDER_BACKFACES = 0
                F_BLEND_MODE = 1
				g_vColorTint = [50.0, 50.0, 50.0, 50.0]
})");
    Materials[3][0] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
				Shader = "csgo_effects.vfx"
                g_flFresnelExponent = 7.0
                g_flFresnelFalloff = 10.0
                g_flFresnelMax = 0.1
                g_flFresnelMin = 1.0
				g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
                g_tMask1 = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_tMask2 = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_tMask3 = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_tSceneDepth = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_flToolsVisCubemapReflectionRoughness = 1.0
                g_flBeginMixingRoughness = 1.0
                g_vColorTint = [ 1.000000, 1.000000, 1.000000, 0 ]
                F_IGNOREZ = 0
                F_DISABLE_Z_WRITE = 0
                F_DISABLE_Z_BUFFERING = 0
                F_RENDER_BACKFACES = 0
})");
    Materials[3][1] = create_material(R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
				Shader = "csgo_effects.vfx"
                g_flFresnelExponent = 7.0
                g_flFresnelFalloff = 10.0
                g_flFresnelMax = 0.1
                g_flFresnelMin = 1.0
				g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
                g_tMask1 = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_tMask2 = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_tMask3 = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_tSceneDepth = resource:"materials/default/default_mask_tga_fde710a5.vtex"
                g_flToolsVisCubemapReflectionRoughness = 1.0
                g_flBeginMixingRoughness = 1.0
                g_vColorTint = [ 1.000000, 1.000000, 1.000000, 0 ]
                F_IGNOREZ = 1
                F_DISABLE_Z_WRITE = 1
                F_DISABLE_Z_BUFFERING = 1
                F_RENDER_BACKFACES = 0
})");
    LogInfo("chams done");
}

class KeyValues3
{
public:
    char pad[0x100]{};
};

struct KV3ID_t
{
    const char* name;
    std::uint64_t key;
    std::uint64_t key2;
};

enum kv_basic_type : uint8_t
{
    kv_basic_invalid,
    kv_basic_null,
    kv_basic_bool,
    kv_basic_int,
    kv_basic_uint,
    kv_basic_double,
    kv_basic_string,
    kv_basic_binary_blob,
    kv_basic_array,
    kv_basic_table
};

enum kv_field_type_t : uint8_t
{
    kv_field_invalid,
    kv_field_resource,
    kv_field_resource_name,
    kv_field_panorama,
    kv_field_soundevent,
    kv_field_subclass,
    kv_field_unspecified,
    kv_field_null,
    kv_field_binary_blob,
    kv_field_array,
    kv_field_table,
    kv_field_bool8,
    kv_field_char8,
    kv_field_uchar32,
    kv_field_int8,
    kv_field_uint8,
    kv_field_int16,
    kv_field_uint16,
    kv_field_int32,
    kv_field_uint32,
    kv_field_int64,
    kv_field_uint64,
    kv_field_float32,
    kv_field_float64,
    kv_field_string,
    kv_field_pointer,
    kv_field_color32,
    kv_field_vector,
    kv_field_vector2d,
    kv_field_vector4d,
    kv_field_rotation_vector,
    kv_field_quaternion,
    kv_field_qangle,
    kv_field_matrix3x4,
    kv_field_transform,
    kv_field_string_token,
    kv_field_ehandle
};

void set_type(KeyValues3* kv3, int type, int type2)
{
    using function_t = void(__fastcall*)(KeyValues3* kv3, int, int);
    g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "40 53 48 83 EC 20 48 8B 01 48 8B D9 44" ).as<function_t>()(kv3, type, type2);
}

bool LoadKV3(KeyValues3* kv3, std::uintptr_t* string, const char* buffer, const KV3ID_t* kv3_id, char* unk_string)
{
    using function_t = bool(__fastcall*)(KeyValues3* kv3, std::uintptr_t* string, const char* buffer, const KV3ID_t* kv3_id, char* unk_strin);
    return g_cs2->m_patterns[FNV32("load_kv3")].as<function_t>()(kv3, string, buffer, kv3_id, unk_string);
}

i_material* c_chams::create_material(const char* vmat)
{

    KeyValues3 kv3;
    set_type(&kv3, kv_basic_type::kv_basic_null, kv_basic_type::kv_basic_string);

    // materialsystem + 0x00000001800C6308
    KV3ID_t kv3_id;
    kv3_id.name = xorstr_("generic");
    kv3_id.key = 0x469806E97412167C;
    kv3_id.key2 = 0x0E73790B53EE6F2AF;

    if (!LoadKV3(&kv3, nullptr, vmat, &kv3_id, nullptr))
        return nullptr;

    i_material** custom_material;

    // "materialsystem2.dll", "48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 48

    g_utils->pattern_scan( g_cs2->m_module_system.get_materialsystem2( ), "48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 48" ).as<void(__fastcall*)(std::uintptr_t*, i_material***, const char*, KeyValues3*, int, std::uint8_t)>()(nullptr, &custom_material, "weave", &kv3, 0, 1);

    return *custom_material;
}