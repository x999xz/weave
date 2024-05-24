#pragma once

#include <string>
#include <vector>

#include "request_generated.h"
#include "authentication_generated.h"
#include "config_generated.h"
#include "user_generated.h"
#include "loader_generated.h"
#include "configs_generated.h"
#include "response_generated.h"
#include "chat_generated.h"
#include "online_generated.h"
#include "loader_pattern_generated.h"
#include "loader_interface_generated.h"
#include "schema_generated.h"
#include "crash_generated.h"
#include "loader_register_generated.h"
#include "loader_interface_generated.h"
#include "loader_module_generated.h"
#include "loader_pattern_generated.h"
#include "module_storage_generated.h"
#include "interface_storage_generated.h"
#include "../flat_message/output/cpp/config_table_generated.h"

struct loader_pattern {
	loader_pattern(std::uint64_t module_, std::uint64_t offset_) : module(module_), offset(offset_) {};
	std::uint64_t module;
	std::uint64_t offset;
};

struct interface_storage {
	uint64_t modules;
	std::vector<uint64_t> interfaces;
};

class c_flatbuffers
{
public:
	void create_stream(bool has_compressed = true);
public:
	void create_request(uint64_t type, int game, std::vector<int8_t> memory);
	void create_authentication(std::string token, std::string build);
	void create_crash(std::string message, int stage, int hook);
	void create_config(std::string token, std::string share = "", std::string value = "", std::string name = "");
	void create_message(std::string username, std::string message);
	void create_request_sticky_message(int index, bool sticky);
	void create_loader_register(std::string username, std::string build);
	void create_loader_module(std::vector<std::uint64_t> modules);
	void create_loader_interface(std::vector<std::uint64_t> interfaces);
	void create_loader_pattern(std::vector<loader_pattern> pattern);
public:
	static std::string get_response(char* data, int size, int original_size);
	void release();
public:
	flatbuffers::FlatBufferBuilder m_builder = flatbuffers::FlatBufferBuilder(0);
	std::vector<int8_t> m_buffer;
	int m_original_size;
};