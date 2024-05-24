// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

bool c_econ_item_definition::is_weapon() {
    // Every gun supports at least 4 stickers.
    return get_stickers_supported_count() >= 4;
}

bool c_econ_item_definition::is_knife(bool excludeDefault) {

    if (strcmp(item_type_name, "#CSGO_Type_Knife"))
        return false;

    return excludeDefault ? item_def >= 500 : true;
}

bool c_econ_item_definition::is_custom_player()
{
    if (strcmp(item_type_name, "#Type_CustomPlayer"))
        return false;

    if (item_def >= 5036 && item_def < 5106)
        return false;

    if (item_def >= 5200 && item_def <= 5205)
        return false;

    if (item_def >= 5300 && item_def <= 5305)
        return false;

    if (item_def == 5600)
        return false;

    return true;
}

bool c_econ_item_definition::is_glove(bool excludeDefault) {

    if (strcmp(item_type_name, "#Type_Hands"))
        return false;

    const bool defaultGlove = item_def == 5028 || item_def == 5029;

    return excludeDefault ? !defaultGlove : true;
}