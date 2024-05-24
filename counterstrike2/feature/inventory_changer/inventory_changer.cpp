// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "inventory_changer.h"
#include <tinyformat/tinyformat.h>
#include "../../gui/gui.h"
#include "../../sdk/vtex/VTexParser.h"

void c_inventory_changer::on_set_model(c_base_model_entity* entity, const char*& model)
{
    //bool is_view_model = CALL_VIRTUAL(bool, 245, entity);
    if (!entity || strcmp(entity->get_class_name(), xorstr_("C_CSGOViewModel")))
        return;

    c_csgo_viewmodel* view_model = (c_csgo_viewmodel*)entity;

    auto inventory = Interfaces::m_cs_inventory_manager->get_local_inventory();
    if (!inventory)
        return;

    auto steam_id = inventory->get_owner().m_id;

    auto entity_ = Interfaces::entity_list->get_entity(view_model->handle_weapon().get_index());
    auto pWeapon = reinterpret_cast<c_weapon_cs_base*>(Interfaces::entity_list->get_entity(view_model->handle_weapon().get_index()));
    
    if (!entity_)
        return;

    bool is_weapon = CALL_VIRTUAL(bool, 150, entity);
    
    if (!pWeapon || !is_weapon ||
        pWeapon->original_owner_xuid() != steam_id)
        return;

    if (pWeapon->get_weapon_data() && pWeapon->get_weapon_data()->weapon_type() != e_weapon_type::knife)
        return;

    auto attribute_manager = pWeapon->attribute_manager();
    if (!attribute_manager)
        return;

    auto item_view = attribute_manager->item();
    if (!item_view)
        return;

    auto item_definition = item_view->static_data();
    if (!item_definition)
        return;

    auto item_in_loadout = inventory->get_item_in_loadout(pWeapon->original_team_number(), item_definition->get_loadout_slot());
    if (!item_in_loadout)
        return;

    auto item_definition_loadout = item_in_loadout->static_data();
    if (!item_definition_loadout || (!item_definition_loadout->is_knife(true) && !item_definition_loadout->is_custom_player()))
        return;

    model = item_definition_loadout->get_model_name();
}

void c_inventory_changer::on_frame_stage_notify(int stage)
{
    if (!Interfaces::engine->is_in_game())
        return;

    if (!g_cs2->local_player || !g_cs2->local_player->is_alive())
        return;

    if (stage != 5 && stage != 6)
        return;

    if (stage == 6)
        update_agent();

    update_knife(stage);
    update_glove(stage);

    if (stage == 6)
        update_skins();
}

void c_inventory_changer::update_agent()
{
    auto inventory = Interfaces::m_cs_inventory_manager->get_local_inventory();
    if (!inventory)
        return;

    if (!g_cs2->local_player)
        return;

    c_econ_item_definition* item_view_loadout = nullptr;
    for (int i = 0; i <= 56; ++i) {
        c_econ_item_view* item_view_ = inventory->get_item_in_loadout(g_cs2->local_player->team_num(), i);
        if (!item_view_)
            continue;

        auto p = item_view_->static_data();

        if (p->is_custom_player())
        {
            item_view_loadout = p;
            break;
        }
    }

    if (!item_view_loadout)
        return;

    if (HASH_RT(item_view_loadout->get_model_name()) == hash_agent)
        return;

    hash_agent = HASH_RT(item_view_loadout->get_model_name());

    g_cs2->local_player->set_model(item_view_loadout->get_model_name());
}

#define STRINGTOKEN_MURMURHASH_SEED 0x31415926

uint32_t MurmurHash2(const void* key, int len, uint32_t seed)
{
    /* 'm' and 'r' are mixing constants generated offline.
       They're not really 'magic', they just happen to work well.  */

    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    /* Initialize the hash to a 'random' value */

    uint32_t h = seed ^ len;

    /* Mix 4 bytes at a time into the hash */

    const unsigned char* data = (const unsigned char*)key;

    while (len >= 4)
    {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    /* Handle the last few bytes of the input array  */

    switch (len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    /* Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.  */

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

#define TOLOWERU( c ) ( ( uint32_t ) ( ( ( c >= 'A' ) && ( c <= 'Z' ) )? c + 32 : c ) )
uint32_t MurmurHash2LowerCaseA(char const* pString, int len, uint32_t nSeed)
{
    char* p = (char*)malloc(len + 1);
    for (int i = 0; i < len; i++)
    {
        p[i] = TOLOWERU(pString[i]);
    }
    return MurmurHash2(p, len, nSeed);
}


#define DEBUG_STRINGTOKENS 0

#define STRINGTOKEN_MURMURHASH_SEED 0x31415926
class CUtlStringToken
{
public:
    std::uint32_t m_nHashCode;
#if DEBUG_STRINGTOKENS
    char const* m_pDebugName;
#endif

    CUtlStringToken(char const* szString)
    {
        this->SetHashCode(this->MakeStringToken(szString));
    }

    bool operator==(CUtlStringToken const& other) const
    {
        return (other.m_nHashCode == m_nHashCode);
    }

    bool operator!=(CUtlStringToken const& other) const
    {
        return (other.m_nHashCode != m_nHashCode);
    }

    bool operator<(CUtlStringToken const& other) const
    {
        return (m_nHashCode < other.m_nHashCode);
    }

    /// access to the hash code for people who need to store thse as 32-bits, regardless of the
    /// setting of DEBUG_STRINGTOKENS (for instance, for atomic operations).
    uint32_t GetHashCode(void) const
    {
        return m_nHashCode;
    }

    void SetHashCode(uint32_t nCode)
    {
        m_nHashCode = nCode;
    }

    __forceinline std::uint32_t MakeStringToken(char const* szString, int nLen)
    {
        std::uint32_t nHashCode = MurmurHash2LowerCaseA(szString, nLen, STRINGTOKEN_MURMURHASH_SEED);
        return nHashCode;
    }

    __forceinline std::uint32_t MakeStringToken(char const* szString)
    {
        return MakeStringToken(szString, (int)strlen(szString));
    }

    //__forceinline std::uint32_t MakeStringToken(CUtlString& str)
    //{
    //    return MakeStringToken(str.Get(), str.Length());
    //}

    CUtlStringToken() { m_nHashCode = 0; }
};

void __fastcall InvalidateMaterial(c_csgo_viewmodel* viewmodel, std::uint32_t material_index) {
    static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "89 54 24 10 48 83 EC 28 48 81 C1 88" );


    pattern.as<decltype(&InvalidateMaterial)>()(viewmodel, material_index);
}

//void update_world_glove(c_cs_player_pawn* pawn) {
//    static auto sign = g_utils->pattern_scan(g_cs2->m_module_system.get_client(), "48 89 4C 24 08 55 56 41 54 48");
//    sign.as<void(__fastcall*)(std::uintptr_t*)>()((std::uintptr_t*)(std::uintptr_t(pawn) + 0x17D8));
//}

void c_inventory_changer::update_glove(int stage) {

    if (stage != frame_net_update_postdataupdate_end)
        return;

    if (!g_cs2->local_player)
        return;

    if (!g_cs2->local_player->is_alive())
        return;

    auto pawn = g_cs2->local_player;
    c_csgo_viewmodel* viewmodel = (c_csgo_viewmodel*)Interfaces::entity_list->get_entity(pawn->viewmodel_services()->view_model().get_index());
    auto gloves = (c_econ_item_view*)(std::uintptr_t(pawn) + 5752);
    auto player_team = pawn->team_num();

    auto inventory = Interfaces::m_cs_inventory_manager->get_local_inventory();
    if (!inventory)
        return;

    auto steam_id = inventory->get_owner().m_id;

    auto item_view_loadout = inventory->get_item_in_loadout(player_team, 41);

    if (!item_view_loadout)
        return;

    c_econ_item_definition* item_definition_loadout = item_view_loadout->static_data();
    if (!item_definition_loadout)
        return;

    if (!item_definition_loadout->is_glove(false))
        return;

    auto item_id = item_view_loadout->item_id();

    /* Detect if we have to change gloves */
    if (gloves->item_id() != item_id || force_update)
    {
        glove_update_frames = 10;

        gloves->item_id() = item_id;
        gloves->item_id_high() = item_view_loadout->item_id_high();
        gloves->item_id_low() = item_view_loadout->item_id_low();
        gloves->account_id() = uint32_t(steam_id);
        gloves->item_index() = item_definition_loadout->item_def;
        *(bool*)(std::uintptr_t(gloves) + 0x1e9) = false;
        force_update = false;
    }

    if (glove_update_frames)
    {
        InvalidateMaterial(viewmodel, 0xF143B82A);

        *(bool*)(std::uintptr_t(gloves) + 488) = true;
        *(bool*)(std::uintptr_t(pawn) + 5744) = true;

        glove_update_frames--;
    }
}

void c_inventory_changer::update_knife(int stage)
{
    auto inventory = Interfaces::m_cs_inventory_manager->get_local_inventory();
    if (!inventory)
        return;

    auto steam_id = inventory->get_owner().m_id;

    auto view_model_services = g_cs2->local_player->viewmodel_services();
    if (!view_model_services)
        return;

    c_csgo_viewmodel* view_model = reinterpret_cast<c_csgo_viewmodel*>(Interfaces::entity_list->get_entity(view_model_services->view_model().get_index()));

    int highestIndex = Interfaces::entity_list->get_highest_entity_index();
    for (int i = 0; i <= highestIndex; ++i) {
        auto entity = Interfaces::entity_list->get_entity(i);
        if (!entity)
            continue;

        bool is_weapon = CALL_VIRTUAL(bool, 150, entity);
        if (!is_weapon)
            continue;

        c_weapon_cs_base* weapon = reinterpret_cast<c_weapon_cs_base*>(entity);

        if (weapon->original_owner_xuid() != steam_id)
            continue;

        if (weapon->get_weapon_data() && weapon->get_weapon_data()->weapon_type() != e_weapon_type::knife)
            continue;

        c_attribute_container* attribute_manager = weapon->attribute_manager();

        c_econ_item_view* item_view = attribute_manager->item();

        c_econ_item_definition* item_definition = item_view->static_data();

        if (!item_definition)
            continue;

        auto item_view_loadout = inventory->get_item_in_loadout(weapon->original_team_number(), item_definition->get_loadout_slot());

        if (!item_view_loadout)
            continue;

        c_econ_item_definition* item_definition_loadout = item_view_loadout->static_data();
        if (!item_definition_loadout)
            continue;

        if (!item_definition_loadout->is_knife(false))
            continue;

        if (stage == 6)
        {
            auto item_id = item_view_loadout->item_id();
            item_view->item_id() = item_id;
            item_view->item_id_high() = item_view_loadout->item_id_high();
            item_view->item_id_low() = item_view_loadout->item_id_low();
            item_view->account_id() = uint32_t(steam_id);
            item_view->item_index() = item_definition_loadout->item_def;
            *(bool*)(std::uintptr_t(item_view) + 0x1e9) = false;
        }

        const char* model = item_definition_loadout->get_model_name();

        if (stage == 6)
        {
            std::uint32_t hash_ = CUtlStringToken(std::to_string(item_definition_loadout->item_def).c_str()).GetHashCode();
            weapon->subclass_id() =  hash_;
            weapon->update_subclass();

            auto& penis = *(const char**)(std::uintptr_t(weapon->get_weapon_data()) + 0x10);
            penis = item_definition_loadout->get_weapon_name();
            weapon->get_weapon_data()->name() = item_definition_loadout->get_weapon_name();
            CALL_VIRTUAL(void, 180, weapon);

            // check later for fix
           //weapon->set_model(model);
           //if (view_model && view_model->handle_weapon().get_handle() == g_cs2->get_handle_entity((c_cs_player_pawn*)weapon))
           //{
           //    view_model->set_model(model);
           //    *(std::uintptr_t**)(std::uintptr_t(*(std::uintptr_t**)(std::uintptr_t(view_model) + 0xD08)) + 0x02E0) = nullptr;
           //}
        }

    }
}

void c_inventory_changer::update_skins()
{
    auto inventory = Interfaces::m_cs_inventory_manager->get_local_inventory();
    if (!inventory)
        return;

    auto steam_id = inventory->get_owner().m_id;

    auto view_model_services = g_cs2->local_player->viewmodel_services();
    if (!view_model_services)
        return;

    c_csgo_viewmodel* view_model = reinterpret_cast<c_csgo_viewmodel*>(Interfaces::entity_list->get_entity(view_model_services->view_model().get_index()));

    int highestIndex = Interfaces::entity_list->get_highest_entity_index();
    for (int i = 0; i <= highestIndex; ++i) {
        auto entity = Interfaces::entity_list->get_entity(i);

        if (!entity)
            continue;

        bool is_weapon = CALL_VIRTUAL(bool, 150, entity);
        if (!is_weapon)
            continue;

        c_weapon_cs_base* weapon = reinterpret_cast<c_weapon_cs_base*>(entity);

        if (weapon->original_owner_xuid() != steam_id)
            continue;

        c_attribute_container* attribute_manager = weapon->attribute_manager();

        c_econ_item_view* item_view = attribute_manager->item();

        c_econ_item_definition* item_definition = item_view->static_data();

        if (!item_definition)
            continue;

        c_econ_item_view* item_view_loadout = nullptr;
        if (item_definition->is_weapon()) {
            for (int i = 0; i <= 56; ++i) {
                c_econ_item_view* item_view_ = inventory->get_item_in_loadout(weapon->original_team_number(), i);
                if (!item_view_)
                    continue;

                if (item_view_->item_index() == item_definition->item_def) {
                    item_view_loadout = item_view_;
                    break;
                }
            }
        }

        if (!item_view_loadout)
            continue;

        c_econ_item_definition* item_definition_loadout = item_view_loadout->static_data();
        if (!item_definition_loadout)
            continue;

        if (item_definition_loadout->is_knife(false))
            continue;

        if (item_definition_loadout->item_def != item_definition->item_def)
            continue;

        auto skin_item_id = item_view_loadout->item_id();
        auto skin_item_def = item_definition_loadout->item_def;
        auto custom_paint_kit = item_view_loadout->custom_paint_kit_index();

        item_view->item_id() = skin_item_id;
        item_view->item_id_high() = item_view_loadout->item_id_high();
        item_view->item_id_low() = item_view_loadout->item_id_low();
        item_view->account_id() = uint32_t(steam_id);
        item_view->item_index() = skin_item_def;
        *(bool*)(std::uintptr_t(item_view) + 0x1e9) = false;
        weapon->paint_kit() = custom_paint_kit;

        auto paint_kit = Interfaces::econ_item_system->get_paint_kits().find_by_key(custom_paint_kit);

        bool uses_old_model = paint_kit.has_value() && paint_kit.value()->uses_legacy_model();

        weapon->game_scene_node()->set_mesh_group_mask(1 + uses_old_model);
        if (view_model && view_model->handle_weapon().get_handle() == g_cs2->get_handle_entity((c_cs_player_pawn*)weapon)) {
            view_model->game_scene_node()->set_mesh_group_mask(1 + uses_old_model);
        }

    }
}

void c_inventory_changer::create_image()
{
    auto& items = Interfaces::econ_item_system->get_sorted_item_definition_map();
    auto& paint_kits = Interfaces::econ_item_system->get_paint_kits();
    auto& skin_image_path = Interfaces::econ_item_system->get_alternate_icons_map();
    auto& sticker_kits = Interfaces::econ_item_system->get_sticker_kits();

    for (auto sticker : sticker_kits)
    {
        if (!strcmp(sticker.m_value->item_name, xorstr_("#StickerKit_Default")))
            continue;

        std::string path = tfm::format(xorstr_("panorama/images/%s_png.vtex_c"), sticker.m_value->path_image);
        std::string name = Interfaces::m_localize->find_safe(sticker.m_value->item_name);

        gui_skins temp_skins{};
        temp_skins.item_def = sticker.m_value->id;
        temp_skins.paint_name = "";
        temp_skins.name = name;
        temp_skins.skin_key = 0;
        temp_skins.paint_id = -1;
        temp_skins.rarity = sticker.m_value->rarity;
        temp_skins.texture_id = -1;
        temp_skins.type = type_item::type_sticker;
        temp_skins.path_image = path;
        temp_skins.is_initilization = false;

        g_gui->skin_preview.emplace_back(temp_skins);
    }

    for (auto item : items)
    {
        if (!item.m_value->is_custom_player() && !item.m_value->is_knife(true) && !item.m_value->is_weapon() && !item.m_value->is_glove(false))
            continue;

        if (!item.m_value->path_image)
            continue;

        std::string path = tfm::format(xorstr_("panorama/images/%s_png.vtex_c"), item.m_value->path_image);
        int item_def = item.m_value->item_def;
        std::string name = Interfaces::m_localize->find_safe(item.m_value->item_base_name);
        auto vtex = VTexParser::Load(path.c_str());

        int rarity = -1;

        if (item.m_value->is_custom_player())
            rarity = item.m_value->get_rarity();

        gui_skins temp_skins{};
        temp_skins.item_def = item_def;
        temp_skins.paint_name = "";
        temp_skins.name = name;
        temp_skins.skin_key = 0;
        temp_skins.paint_id = -1;
        temp_skins.rarity = rarity;
        temp_skins.texture_id = g_render->create_texture_rgba(vtex.data, vtex.w, vtex.h);

        int type_ = 0;

        if (item.m_value->is_custom_player())
            type_ = type_item::type_agent;
        else if (item.m_value->is_knife(true))
            type_ = type_item::type_knife;
        else if (item.m_value->is_weapon())
            type_ = type_item::type_weapons;
        else if (item.m_value->is_glove(false))
            type_ = type_item::type_glove;
        else
            type_ = type_item::type_sticker;


        temp_skins.type = type_;
        temp_skins.path_image = path;
        temp_skins.is_initilization = true;

        g_gui->skin_preview.emplace_back(temp_skins);
    }

    for (auto item : items)
    {
        if (!item.m_value->is_knife(true) && !item.m_value->is_weapon() && !item.m_value->is_glove(false))
            continue;

        for (auto paint_kit : paint_kits)
        {
            const uint64_t skinKey = Helper_GetAlternateIconKeyForWeaponPaintWearItem(item.m_value->item_def, paint_kit.m_value->id, 0);

            if (skin_image_path.find_by_key(skinKey).has_value())
            {
                auto it = skin_image_path.find_by_key(skinKey).value();

                std::string path = tfm::format(xorstr_("panorama/images/%s_png.vtex_c"), it.path_image);

                if (path.find(xorstr_("newcs2")) != std::string::npos)
                    continue;

                int item_def = item.m_value->item_def;
                std::string name = Interfaces::m_localize->find_safe(item.m_value->item_base_name);
                std::string paint_name = Interfaces::m_localize->find_safe(paint_kit.m_value->description_name);

                auto rarity = std::clamp(item.m_value->get_rarity() + paint_kit.m_value->rarity - 1, 0,
                    (paint_kit.m_value->rarity == 7) ? 7 : 6);

                gui_skins temp_skins{};
                temp_skins.item_def = item_def;
                temp_skins.paint_name = paint_name;
                temp_skins.name = name;
                temp_skins.skin_key = skinKey;
                temp_skins.paint_id = paint_kit.m_value->id;
                temp_skins.rarity = rarity;
                temp_skins.texture_id = -1;
                int type_ = 0;

                if (item.m_value->is_custom_player())
                    type_ = type_item::type_agent;
                else if (item.m_value->is_knife(true))
                    type_ = type_item::type_knife;
                else if (item.m_value->is_weapon())
                    type_ = type_item::type_weapons;
                else if (item.m_value->is_glove(false))
                    type_ = type_item::type_glove;
                else
                    type_ = type_item::type_sticker;


                temp_skins.type = type_;
                temp_skins.path_image = path;
                temp_skins.is_initilization = false;

                g_gui->skin_preview.emplace_back(temp_skins);
            }
        }
    }

    std::copy_if(g_gui->skin_preview.begin(), g_gui->skin_preview.end(), std::back_inserter(g_gui->item_default), [](gui_skins skin) {
        return skin.paint_id == -1 && skin.type == type_item::type_weapons;
        });
    std::copy_if(g_gui->skin_preview.begin(), g_gui->skin_preview.end(), std::back_inserter(g_gui->item_knife_default), [](gui_skins skin) {
        return skin.paint_id == -1 && skin.type == type_item::type_knife;
        });
    std::copy_if(g_gui->skin_preview.begin(), g_gui->skin_preview.end(), std::back_inserter(g_gui->item_stickers), [](gui_skins skin) {
        return skin.type == type_item::type_sticker;
        });
    std::copy_if(g_gui->skin_preview.begin(), g_gui->skin_preview.end(), std::back_inserter(g_gui->item_agent), [](gui_skins skin) {
        return skin.type == type_item::type_agent;
        });
    std::copy_if(g_gui->skin_preview.begin(), g_gui->skin_preview.end(), std::back_inserter(g_gui->item_glove), [](gui_skins skin) {
        return skin.type == type_item::type_glove;
        });

    for (auto item : g_gui->skin_preview)
    {
        if (item.paint_id == -1)
            continue;

        if (item.type != type_item::type_knife && item.type != type_item::type_weapons)
            continue;

        g_gui->item_weapons[item.item_def].emplace_back(item);
    }
}