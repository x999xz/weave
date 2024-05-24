#pragma once

#include "../interfaces/virtual.hpp"

class ID3D11ShaderResourceView;

class c_texture_dx11
{
public:
	char pad[0x10];
	ID3D11ShaderResourceView* texture_data;
	ID3D11ShaderResourceView* texture_data2;
};

class c_textures_dx11
{
public:
	c_texture_dx11* texture;
};

class c_source2_ui_texture
{
public:
	char pad[0x28];
	c_textures_dx11* texture_dx11;
};

class c_image_data
{
public:
	char pad[0x30];
	c_source2_ui_texture* source2_ui_texture;
};

class c_image_proxy_source
{
public:
	char pad[0x10];
	c_image_data* image_data;
};

class c_image_resource
{
public:
	char pad[24];
	const char* name;
	char pad_0020[80];
	c_image_proxy_source* image_proxy_source;
};

class c_image_resource_array
{
public:
	char pad[0x10];
	c_image_resource* image_resource;
	std::uint64_t alloc_size;
	std::uint32_t unk;
	std::uint32_t size;
};

class c_image_resource_manager
{
public:
	c_image_resource_array image_resource_array[2];
};

class c_panoramas
{
public:
	char pad[0x70];
	std::uintptr_t* panel;
};

class unk_inf
{
public:
	int unk;
	int unk2;
};

class c_panorama_ui_engine2
{
public:
	char pad_0000[200]; //0x0000
	class N00000B54* style_factory_wrapper; //0x00C8
	char pad_00D0[32]; //0x00D0
	c_panoramas* panoramas; //0x00F0
	int64_t alloc_size; //0x00F8
	int32_t N000034DC; //0x0100
	int32_t N000037E6; //0x0104
	int32_t N000034DD; //0x0108
	int32_t size; //0x010C
	char pad_0110[64]; //0x0110
	class N00000B7A* ui_input_engine; //0x0150
	class N00000BA0* layout_manager; //0x0158
	char pad_0160[640]; //0x0160
	class N00000BC6* localization; //0x03E0
	class N00000BEC* sound_system; //0x03E8
	char pad_03F0[1072]; //0x03F0
	class N00000C45* source2_ui_file_system; //0x0820
	char pad_0828[744]; //0x0828
	class N00000C6B* file_handle; //0x0B10
	char pad_0B18[48]; //0x0B18
	class N00000C91* panorama_type_manager; //0x0B48
	class N00000CB7* panorama_type_manager2; //0x0B50
	class N00000CDD* panorama_type_manager3; //0x0B58
	char pad_0B60[16]; //0x0B60
	class N00000D03* panorama_type_manager4; //0x0B70
	class N00000D29* render_device; //0x0B78
	c_image_resource_manager* image_resource_manager; //0x0B80
public:
	std::uintptr_t* get_unk(unk_inf* str, std::uint64_t* aye)
	{
		return CALL_VIRTUAL(std::uintptr_t*, 33, this, str, aye);
	}

	std::uintptr_t* get_penis(std::uint64_t* index)
	{
		return CALL_VIRTUAL(std::uintptr_t*, 34, this, index);
	}
};