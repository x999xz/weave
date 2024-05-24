#pragma once

#include <vector>
#include <string>
#include <flatbuffers/flatbuffers.h>

class web_utils
{
public:
	std::vector<std::uint8_t> split_binary(std::string in);
	std::string binary_to_string(flatbuffers::span<std::uint8_t> buffers);
public:
	flatbuffers::FlatBufferBuilder fbb_;
};

inline auto g_web_utils = std::make_unique<web_utils>();