// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <Windows.h>
#include "utils.h"

#include <sstream>
#include <snappy/snappy.h>

std::vector<std::uint8_t> web_utils::split_binary(std::string in)
{
    std::istringstream iss(in);
    std::string bin;
    std::vector<std::uint8_t> bins;

    while (std::getline(iss, bin, ' ')) {
        bins.push_back(std::atoi(bin.c_str()));
    }

    return bins;
}

std::string web_utils::binary_to_string(flatbuffers::span<std::uint8_t> buffers)
{
    std::string str;
    for (int i{}; i < buffers.size(); i++)
    {
        int char_ = buffers.data()[i];

        char string[6] = "";

        itoa(char_, string, 10);

        str.append(string);
        str.append(" ");
    }

    str.erase(str.end() - 1, str.end());

    return str;
}