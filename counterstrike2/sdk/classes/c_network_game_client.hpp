#pragma once

#include "../sdk.hpp"
#include "../interfaces/virtual.hpp"

// xref find struct SetSignonState

// virtual offset 0x228 | index 0x45

class c_net_chan;

struct client_class
{
	char* name;
	char* name2;
	std::uintptr_t penis_table;
	char pad[0x70];
	__int64 penis2;
};

class c_server_class_info
{
public:
	const char* name;
	client_class* client_state;
};

class CNetworkStringTableContainer;
class CRenderingWorldSession;
class CSpawnGroupMgrGameSystem;
class CCallbackInternal_Steam_OnUGCDownload;

class class_information
{
public:
	char* name; //0x0000
	char* name2; //0x0008
	void* pointer_data; //0x0010
	char* module_name; //0x0018
	char pad_0020[32]; //0x0020
}; //Size: 0x0040

class ClassInfo
{
public:
	char* name; //0x0000
	class_information* class_information; //0x0008
}; //Size: 0x0010

class ClassName
{
public:
	int64_t size; //0x0000
	class ClassData* class_data; //0x0008
}; //Size: 0x0010

class N000000FC
{
public:
	char pad_0000[80]; //0x0000
}; //Size: 0x0050


class c_network_game_client {
	enum vtables
	{
		global_vars_ = 4,
		client_tick = 5,
		server_tick = 6,
		net_channel = 41,
		unk = 68,
		set_signon_state = 116,
		copy_new_entity = 123
	};
public:
	c_global_vars* get_global_vars()
	{
		//xref: Curtime( %f )\nRealtime( %f )\n module: engine2
		return CALL_VIRTUAL(c_global_vars*, vtables::global_vars_, this);
	}

	c_net_chan* get_net_channel()
	{
		return CALL_VIRTUAL(c_net_chan*, vtables::net_channel, this, 0);
	}

	int get_client_tick()
	{
		return CALL_VIRTUAL(int, vtables::client_tick, this);
	}

	int get_server_tick()
	{
		return CALL_VIRTUAL(int, vtables::server_tick, this);
	}

	void get_prediction_tick(int* prediction_tick)
	{
		int unk{};
		return CALL_VIRTUAL(void, vtables::unk, this, prediction_tick, &unk);
	}

	void set_prediction(bool value)
	{
		*(bool*)(std::uintptr_t(this) + 0xDC) = value;
	}

	bool get_prediction()
	{
		return *(bool*)(std::uintptr_t(this) + 0xDC);
	}
public:
	c_net_chan* get_net_channel2()
	{
		return *(c_net_chan**)(std::uintptr_t(this) + 0xE8);
	}

	c_utl_vector<c_server_class_info>* server_classes()
	{
		return reinterpret_cast<c_utl_vector<c_server_class_info>*>(std::uintptr_t(this) + 0x1A0);
	}

	int m_server_count()
	{
		return *(int*)(std::uintptr_t(this) + 0x258);
	}

	int& m_delta_tick()
	{
		return *(int*)(std::uintptr_t(this) + 0x25C);
	}

	int m_command()
	{
		return *(int*)(std::uintptr_t(this) + 0x285E78);
	}
public:
	char pad_0000[104]; //0x0000
	std::uintptr_t* N0000005C; //0x0068
	char pad_0070[48]; //0x0070
	c_global_vars global_vars; //0x00A0
	char pad_00F0[176]; //0x00F0
	ClassName class_names; //0x01A0
	char pad_01B0[40]; //0x01B0
	CNetworkStringTableContainer* CNetworkStringTableContainer; //0x01D8
	char pad_01E0[64]; //0x01E0
	char* map_vpk; //0x0220
	char* map_name; //0x0228
	char pad_0230[16]; //0x0230
	int64_t signon_state; //0x0240
	char pad_0248[16]; //0x0248
	int32_t server_count; //0x0258
	int32_t delta_tick; //0x025C
	char pad_0260[272]; //0x0260
	CRenderingWorldSession* CRenderingWorldSession; //0x0370
	CSpawnGroupMgrGameSystem* CSpawnGroupMgrGameSystem; //0x0378
	char pad_0380[64]; //0x0380
	N000000FC entity_cache[16385]; //0x03C0
	char pad_140410[8]; //0x140410
	N000000FC entity_cache2[16383]; //0x140418
	char pad_2803C8[4184]; //0x2803C8
	CCallbackInternal_Steam_OnUGCDownload* CCallbackInternal_Steam_OnUGCDownload_; //0x281420
	CCallbackInternal_Steam_OnUGCDownload* CCallbackInternal_Steam_OnUGCDownload2; //0x281428
	char pad_281430[24]; //0x281430
};