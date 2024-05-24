#pragma once

#include "../sdk.hpp"

class CAttributeString
{
public:
    char pad[0x10];
    std::string* data2;
    std::string* data;
};

class CSchemaAttributeType_String
{

};

class CEconItemAttributeDefinition
{
public:
    char pad[0x18];
    CSchemaAttributeType_String* m_pSchemaAttributeType_String;
};