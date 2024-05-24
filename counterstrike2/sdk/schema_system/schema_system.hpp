#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include "../../utilities/xorstr.h"

#include "../sdk.hpp"

class schema_system
{
public:
    bool initialize();
    std::uint32_t get_schema(uint64_t class_name, uint64_t property_name);
public:
    std::unordered_map<uint64_t, std::unordered_map<uint64_t, xored_schema>> schema_data;
};

inline auto g_schema_system = std::make_unique<schema_system>();

#define SCHEMA(class_name, property_name, function, type) \
__forceinline type function() \
{ \
    return *reinterpret_cast<type*>(reinterpret_cast<std::uint64_t>(this) + g_pSchemaOffset->property_name); \
} \

#define SCHEMA_(class_name, property_name, function, type) \
__forceinline type* function() \
{ \
    return reinterpret_cast<type*>(reinterpret_cast<std::uint64_t>(this) + g_pSchemaOffset->property_name); \
} \
