#pragma once

#include <cstdint>
#include <vector>
#include <d3d11.h>
#include <string>
#include <memory>

#include "debug_console/debug.hpp"
#include "fnv.h"
#include "xorstr.h"
#include "address/address.hpp"
#include "stack_trace/stack_trace.h"
#include "UnixTime.h"

#define in_range(x, a, b) ((x) >= (a) && (x) <= (b))
#define get_bits(x) (in_range((x & (~0x20)), 'A', 'F') ? (((x) & (~0x20)) - 'A' + 0xA): (in_range(x, '0', '9') ? (x) - '0': 0))
#define get_byte(x) (get_bits(x[0]) << 4 | get_bits(x[1]))

class messages;

class utilities
{
public:
	c_address pattern_scan(uintptr_t module, const char* signature);
	uintptr_t resolve_rip(uintptr_t address, uintptr_t offset);
	float random_float(float min, float max);
	uintptr_t get_module_base(const wchar_t* mod_name);
	uintptr_t get_proc_address(uintptr_t mod, char* name);
	void random_seed(unsigned int seed);
	void create_thread(void* target);
	void* get_virtual(void* class_pointer, std::uint32_t index);
	std::vector<uint8_t> get_image_in_vtex_c(std::vector<uint8_t> binare);
	ID3D11ShaderResourceView* create_image_path(std::string path);
	ID3D11ShaderResourceView* create_image_memory(uint8_t* data, int size);
	std::string get_time_date(messages& message);

	void create_hook_steam(__int64 iAddr, __int64 iFunction, __int64* iOriginal);
};

inline auto g_utils = std::make_unique<utilities>();
