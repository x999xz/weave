#include "flatbuffers.hpp"
#include <lz4/lz4.h>
#include <time.h>
#include "../UnixTime.h"
#include "../tls/tls.h"

void c_flatbuffers::create_stream(bool has_compressed)
{
   
}

void c_flatbuffers::create_request(uint64_t type, int game, std::vector<int8_t>  memory)
{
   
}

void c_flatbuffers::create_authentication(std::string token, std::string build)
{
   
}

void c_flatbuffers::create_crash(std::string message, int stage, int hook)
{
   
}

void c_flatbuffers::create_config(std::string token, std::string share, std::string value, std::string name)
{
    
}

#include <chrono>

void c_flatbuffers::create_message(std::string username, std::string message) {
   
}

void c_flatbuffers::create_request_sticky_message(int index, bool sticky) {
   
}

void c_flatbuffers::create_loader_register(std::string username, std::string build) {
   
}

void c_flatbuffers::create_loader_module(std::vector<std::uint64_t> modules) {
  
}

void c_flatbuffers::create_loader_interface(std::vector<std::uint64_t> interfaces) {
  
}

std::string c_flatbuffers::get_response(char* data, int size, int original_size) {

    int size_ = original_size;

    if (original_size < size)
        size_ = size;

    char* decompressed = new char[size_];

    int out_size = LZ4_decompress_safe(data, decompressed, size, size_);

    if (out_size < 0) {
        out_size = size;
    }

    std::string message(decompressed, decompressed + out_size);

    delete[] decompressed;

    return message;
}

void c_flatbuffers::release() {
    m_buffer.clear();
    m_builder.Release();
}