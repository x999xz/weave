// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../tls/tls.h"
#include "user.h"

#include <format>

#include "utils.h"
#include "../gui/gui.h"
#include "../hotkey_system/hotkey_system.h"
#include "../../core.hpp"
#include "../exception/weave_error.h"
#include "../../feature/inventory_changer/inventory_changer.h"
#include "../../feature/misc/misc.h"
#include <iostream>
#include "../service/flatbuffers.hpp"
#include "../hash.h"

double CUser::IsActive(std::string var, std::string bind_var, int index)
{
	auto bind = g_gui->has_active_bind(bind_var);

	if (!bind.enabled) {

		if (config_map_.find(var) == config_map_.end())
			return 0;

		return config_map_.at(var);
	}

	return index != -1 ? bind.value[index] : bind.value[0];
}

__attribute__((optnone)) void Register(std::string build) {

	c_flatbuffers m_buffer_auth;
	m_buffer_auth.create_loader_register(g_cs2->username, build);
	m_buffer_auth.create_stream(false);

	c_flatbuffers m_buffer;
	m_buffer.create_request(HASH("register_build"), 0, m_buffer_auth.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());
}

__attribute__((optnone)) void RegisterModule(std::vector<uint64_t> modules) {
	c_flatbuffers m_buffer_auth;
	m_buffer_auth.create_loader_module(modules);
	m_buffer_auth.create_stream(false);

	c_flatbuffers m_buffer;
	m_buffer.create_request(HASH("write_module"), 0, m_buffer_auth.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());
}

__attribute__((optnone)) void RegisterInterface(std::vector<uint64_t> interfaces) {
	c_flatbuffers m_buffer_auth;
	m_buffer_auth.create_loader_interface(interfaces);
	m_buffer_auth.create_stream(false);

	c_flatbuffers m_buffer;
	m_buffer.create_request(HASH("write_interface"), 0, m_buffer_auth.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());
}

__attribute__((optnone)) std::vector<uint64_t> GetModules() {

	c_flatbuffers m_buffer;
	m_buffer.create_request(HASH("get_module"), 0, {});
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	auto data = g_tls_client->read();

	if (!data) {
		return {};
	}

	if (data->empty())
	{
		free(data);
		return {};
	}

	int original_size = atoi(data->c_str());

	free(data);

	auto data2 = g_tls_client->read();

	if (!data2) {
		return {};
	}

	if (data2->empty()) {
		free(data2);
		return {};
	}

	auto response_data = c_flatbuffers::get_response(data2->data(), data2->size(), original_size);

	free(data2);

	if (response_data.empty())
		return {};

	auto response = flatbuffers::GetRoot<Response>(response_data.data());

	if (response->error()) {
		MessageBoxA(0, response->error()->c_str(), 0, MB_OK);
		return {};
	}

	auto p = flatbuffers::GetRoot<ModuleStorage>(response->data()->data());

	std::vector<uint64_t> modules_;

	for (int i{}; i < p->modules()->size(); i++)
	{
		modules_.push_back(p->modules()->Get(i));
	}

	return modules_;
}

__attribute__((optnone)) std::vector<interface_storage> GetInterfaces() {
	c_flatbuffers m_buffer;
	m_buffer.create_request(HASH("get_interface"), 0, {});
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	auto data = g_tls_client->read();

	if (!data) {
		return {};
	}

	if (data->empty())
	{
		free(data);
		return {};
	}

	int original_size = atoi(data->c_str());

	free(data);

	auto data2 = g_tls_client->read();

	if (!data2) {
		return {};
	}

	if (data2->empty()) {
		free(data2);
		return {};
	}

	auto response_data = c_flatbuffers::get_response(data2->data(), data2->size(), original_size);

	free(data2);

	if (response_data.empty())
		return {};

	auto response = flatbuffers::GetRoot<Response>(response_data.data());

	if (response->error()) {
		MessageBoxA(0, response->error()->c_str(), 0, MB_OK);
		return {};
	}

	auto p = flatbuffers::GetRoot<InterfaceStorage>(response->data()->data());

	std::vector<interface_storage> interface_storage_;;

	for (int i{}; i < p->storage()->size(); i++)
	{
		std::vector<uint64_t> interfaces_hash;
		for (int j{}; j < p->storage()->Get(i)->interfaces()->size(); j++)
		{
			interfaces_hash.push_back(p->storage()->Get(i)->interfaces()->Get(j));
		}
		interface_storage_.push_back({ p->storage()->Get(i)->module_(),interfaces_hash });
	}

	return interface_storage_;
}

void DEV_() {
	auto modules = GetModules();
	auto interfaces = GetInterfaces();

	std::vector<std::uint64_t> final_modules;
	std::vector<std::uint64_t> final_interface;

	std::unordered_map<std::uint64_t, std::uint64_t> modules_;
	modules_[FNV64("client.dll")] = std::uintptr_t(GetModuleHandle("client.dll"));
	modules_[FNV64("server.dll")] = std::uintptr_t(GetModuleHandle("server.dll"));
	modules_[FNV64("panorama.dll")] = std::uintptr_t(GetModuleHandle("panorama.dll"));
	modules_[FNV64("engine2.dll")] = std::uintptr_t(GetModuleHandle("engine2.dll"));
	modules_[FNV64("tier0.dll")] = std::uintptr_t(GetModuleHandle("tier0.dll"));
	modules_[FNV64("materialsystem2.dll")] = std::uintptr_t(GetModuleHandle("materialsystem2.dll"));
	modules_[FNV64("resourcesystem.dll")] = std::uintptr_t(GetModuleHandle("resourcesystem.dll"));
	modules_[FNV64("schemasystem.dll")] = std::uintptr_t(GetModuleHandle("schemasystem.dll"));
	modules_[FNV64("steam_api64.dll")] = std::uintptr_t(GetModuleHandle("steam_api64.dll"));
	modules_[FNV64("GameOverlayRenderer64.dll")] = std::uintptr_t(GetModuleHandle("GameOverlayRenderer64.dll"));
	modules_[FNV64("scenesystem.dll")] = std::uintptr_t(GetModuleHandle("scenesystem.dll"));
	modules_[FNV64("SDL3.dll")] = std::uintptr_t(GetModuleHandle("SDL3.dll"));
	modules_[FNV64("animationsystem.dll")] = std::uintptr_t(GetModuleHandle("animationsystem.dll"));
	modules_[FNV64("filesystem_stdio.dll")] = std::uintptr_t(GetModuleHandle("filesystem_stdio.dll"));
	modules_[FNV64("inputsystem.dll")] = std::uintptr_t(GetModuleHandle("inputsystem.dll"));
	modules_[FNV64("particles.dll")] = std::uintptr_t(GetModuleHandle("particles.dll"));
	modules_[FNV64("localize.dll")] = std::uintptr_t(GetModuleHandle("localize.dll"));
	modules_[FNV64("worldrenderer.dll")] = std::uintptr_t(GetModuleHandle("worldrenderer.dll"));
	modules_[FNV64("rendersystemdx11.dll")] = std::uintptr_t(GetModuleHandle("rendersystemdx11.dll"));
	modules_[FNV64("networksystem.dll")] = std::uintptr_t(GetModuleHandle("networksystem.dll"));

	for (auto module : modules) {
		auto module1 = modules_[module];
		final_modules.push_back(module1);
	}

	for (auto& it : interfaces) {
		auto module1 = modules_[it.modules];
		for (auto jt : it.interfaces)
		{
			final_interface.push_back(std::uintptr_t(Interfaces::get_interface<std::uint64_t>(module1, "", true, jt)));
		}
	}

	Register(xorstr_("dev"));
	RegisterModule(final_modules);
	RegisterInterface(final_interface);

	g_tls_client->SetBindingRecview(c_tls_client::HandleRecview);
	g_tls_client->SetBindingSending(c_tls_client::HandleSending);

	g_utils->create_thread([]() { while (true) { g_tls_client->m_recview(); } });
	//g_utils->create_thread([]() { while (true) { g_tls_client->m_sending(); } });
}

void CUser::Processing(const EProcessingType type, const ProcessingRecord processing_record)
{
	g_user->m_should_processing = false;

	g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::SendAuthServer;
	g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::ProcessingGetConfigs;
	g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::SendGetConfigsServer;
	g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::CreateImage;

	c_tls_client::HandleRecview( );
}

void CUser::Avatar(ProcessingRecord processing_record_)
{
	c_flatbuffers m_buffer_auth;
	m_buffer_auth.create_authentication(g_cs2->token, g_cs2->build);
	m_buffer_auth.create_stream(false);

	c_flatbuffers m_buffer;
	m_buffer.create_request(HASH("get_avatar"), 1, m_buffer_auth.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	m_buffer.release();
	m_buffer_auth.release();
}

void CUser::GetOnline(ProcessingRecord processing_record_)
{
	c_flatbuffers m_buffer_auth;
	m_buffer_auth.create_authentication(g_cs2->token, g_cs2->build);
	m_buffer_auth.create_stream(false);

	c_flatbuffers m_buffer;
	m_buffer.create_request(HASH("get_online"), 1, m_buffer_auth.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	m_buffer.release();
	m_buffer_auth.release();
}

void CUser::Auth(ProcessingRecord processing_record_)
{

	g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::ProcessingGetConfigs;

}

void CUser::GetConfigList(ProcessingRecord processing_record_)
{
	c_flatbuffers m_buffer_config;
	c_flatbuffers m_buffer;

	m_buffer_config.create_config(g_cs2->token, xorstr_("dashdk"), xorstr_("dkqawsdqw"));
	m_buffer_config.create_stream(false);

	m_buffer.create_request(HASH("get_configs"), 1, m_buffer_config.m_buffer);
	m_buffer.create_stream();

	if (!g_cs2->m_initilization)
		g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::SendGetConfigsServer;

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	m_buffer.release();
	m_buffer_config.release();
}

void CUser::Load(ProcessingRecord processing_record_)
{
	if (processing_record_.share.empty())
		return;

	g_hotkey->mutex_.lock();
	for (auto it = g_hotkey->hotkeys_->begin(); it != g_hotkey->hotkeys_->end(); it++)
	{
		it->second.binds.clear();
	}
	g_hotkey->mutex_.unlock();

	g_gui->m_color_picker.clear();

	for (auto it : g_gui->skin_added)
	{
		auto items = Interfaces::m_cs_inventory_manager->get_local_inventory()->get_items();
		for (int i{}; i < items.get_size(); i++)
		{
			auto item = items.get_element(i);

			if (item->item_id() != it.id)
				continue;

			auto soc_data = Interfaces::m_cs_inventory_manager->get_local_inventory()->get_soc_data_for_item(item->item_id());

			Interfaces::m_cs_inventory_manager->get_local_inventory()->remove_econ_item(soc_data);
		}
	}
	g_gui->skin_added.clear();

	auto config = flatbuffers::GetMutableRoot<ConfigSettings>(configs_[processing_record_.share].data_.data());
	auto table_config = reinterpret_cast<flatbuffers::Table*>(config);

	flatbuffers::Verifier verify_flat(configs_[processing_record_.share].data_.data(), configs_[processing_record_.share].data_.size());

	const auto data = configs_[processing_record_.share].data_.data();

	ConfigSettingsT new_config{};
	new_config.m_antiaim = std::make_unique<antiaimT>();
	new_config.m_rage_global_settings = std::make_unique<rage_global_settingsT>();
	new_config.m_visuals = std::make_unique<visualsT>();
	new_config.m_visuals->flags = std::make_unique<flags_T>();
	new_config.m_visuals->m_weapons = std::make_unique<weapons_T>();
	new_config.m_misc = std::make_unique<miscT>();
	new_config.m_misc->misc_fov = 90.f;

	if (table_config->VerifyTableStart(verify_flat) && config) {

		if (table_config->VerifyField<std::uint8_t>(verify_flat, ConfigSettings::FlatBuffersVTableOffset::VT_M_VERIFY, 1))
			new_config.m_verify = config->m_verify();

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_ANTIAIM) && verify_flat.VerifyTable(config->m_antiaim()) && config->m_antiaim()->Verify(verify_flat) && config->m_antiaim())
		{
			new_config.m_antiaim = std::unique_ptr<antiaimT>(config->m_antiaim()->UnPack());
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_LEGIT_WEAPONS) && verify_flat.VerifyVector(config->m_legit_weapons()) && verify_flat.VerifyVectorOfTables(config->m_legit_weapons()))
		{
			if (config->m_legit_weapons())
			{
				for (int i{}; i < config->m_legit_weapons()->size(); i++)
				{
					auto weapon = config->m_legit_weapons()->Get(i);

					if (verify_flat.VerifyTable<legit_settings>(weapon) && weapon->Verify(verify_flat) && weapon)
						new_config.m_legit_weapons.push_back(std::unique_ptr< legit_settingsT>(weapon->UnPack()));
				}
			}
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_RAGE_GLOBAL_SETTINGS) && verify_flat.VerifyTable(config->m_rage_global_settings()) && config->m_rage_global_settings()->Verify(verify_flat) && config->m_rage_global_settings())
		{
			new_config.m_rage_global_settings = std::unique_ptr<rage_global_settingsT>(config->m_rage_global_settings()->UnPack());
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_RAGE_WEAPONS) && verify_flat.VerifyVector(config->m_rage_weapons()) && verify_flat.VerifyVectorOfTables(config->m_rage_weapons()))
		{
			if (config->m_rage_weapons())
			{
				for (int i{}; i < config->m_rage_weapons()->size(); i++)
				{
					auto weapon = config->m_rage_weapons()->Get(i);

					if (verify_flat.VerifyTable<rage_settings>(weapon) && weapon->Verify(verify_flat) && weapon)
						new_config.m_rage_weapons.push_back(std::unique_ptr< rage_settingsT>(weapon->UnPack()));
				}
			}
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_VISUALS) && verify_flat.VerifyTable(config->m_visuals()) && config->m_visuals()->Verify(verify_flat) && config->m_visuals())
		{
			new_config.m_visuals = std::unique_ptr<visualsT>(config->m_visuals()->UnPack());
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_MISC) && verify_flat.VerifyTable(config->m_misc()) && config->m_misc()->Verify(verify_flat) && config->m_misc())
		{
			new_config.m_misc = std::unique_ptr<miscT>(config->m_misc()->UnPack());
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_BINDS) && verify_flat.VerifyVector(config->m_binds()) && verify_flat.VerifyVectorOfTables(config->m_binds()))
		{
			if (config->m_binds())
			{
				for (int i{}; i < config->m_binds()->size(); i++)
				{
					auto bind = config->m_binds()->Get(i);

					if (verify_flat.VerifyTable<Hotkey_>(bind) && bind->Verify(verify_flat) && bind)
						new_config.m_binds.push_back(std::unique_ptr< Hotkey_T>(bind->UnPack()));
				}
			}
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_EQUIP_INVENTORY) && verify_flat.VerifyVector(config->m_equip_inventory()) && verify_flat.VerifyVectorOfTables(config->m_equip_inventory()))
		{
			if (config->m_equip_inventory())
			{
				for (int i{}; i < config->m_equip_inventory()->size(); i++)
				{
					auto inventory = config->m_equip_inventory()->Get(i);

					if (verify_flat.VerifyTable<Inventory>(inventory) && inventory->Verify(verify_flat) && inventory)
						new_config.m_equip_inventory.push_back(std::unique_ptr< InventoryT>(inventory->UnPack()));
				}
			}
		}

		if (table_config->VerifyOffset(verify_flat, ConfigSettings::VT_M_ADDED_ITEM) && verify_flat.VerifyVector(config->m_added_item()) && verify_flat.VerifyVectorOfTables(config->m_added_item()))
		{
			if (config->m_added_item())
			{
				for (int i{}; i < config->m_added_item()->size(); i++)
				{
					auto inventory = config->m_added_item()->Get(i);

					if (verify_flat.VerifyTable<Item>(inventory) && inventory->Verify(verify_flat) && inventory)
						new_config.m_added_item.push_back(std::unique_ptr< ItemT>(inventory->UnPack()));
				}
			}
		}
	}

	verify_flat.EndTable();

	if (new_config.m_rage_global_settings)
	{
		config_map_[xorstr_("ragebot_enable")] = new_config.m_rage_global_settings->m_enabled;
		config_map_[xorstr_("ragebot_auto_fire")] = new_config.m_rage_global_settings->m_auto_fire;
		config_map_[xorstr_("ragebot_auto_silent")] = new_config.m_rage_global_settings->m_silent;
		config_map_[xorstr_("ragebot_penetration")] = new_config.m_rage_global_settings->m_penetration;
		config_map_[xorstr_("ragebot_nospread")] = new_config.m_rage_global_settings->m_nospread;
		config_map_[xorstr_("ragebot_auto_scope")] = new_config.m_rage_global_settings->m_auto_scope;
	}

	for (int i{}; i < new_config.m_rage_weapons.size(); i++)
	{

		if (!new_config.m_rage_weapons.empty())
		{
			if (new_config.m_rage_weapons[i]->hitboxes)
			{
				config_map_[std::format("ragebot_hitbox_head_{}", i)] = new_config.m_rage_weapons[i]->hitboxes->m_head;
				config_map_[std::format("ragebot_hitbox_chest_{}", i)] = new_config.m_rage_weapons[i]->hitboxes->m_chest;
				config_map_[std::format("ragebot_hitbox_stomach_{}", i)] = new_config.m_rage_weapons[i]->hitboxes->m_stomach;
				config_map_[std::format("ragebot_hitbox_arms_{}", i)] = new_config.m_rage_weapons[i]->hitboxes->m_arms;
				config_map_[std::format("ragebot_hitbox_legs_{}", i)] = new_config.m_rage_weapons[i]->hitboxes->m_legs;
				config_map_[std::format("ragebot_hitbox_foot_{}", i)] = new_config.m_rage_weapons[i]->hitboxes->m_foot;
			}

			if (new_config.m_rage_weapons[i]->multipoints)
			{
				config_map_[std::format("ragebot_multipoint_head_{}", i)] = new_config.m_rage_weapons[i]->multipoints->m_head;
				config_map_[std::format("ragebot_multipoint_chest_{}", i)] = new_config.m_rage_weapons[i]->multipoints->m_chest;
				config_map_[std::format("ragebot_multipoint_stomach_{}", i)] = new_config.m_rage_weapons[i]->multipoints->m_stomach;
				config_map_[std::format("ragebot_multipoint_arms_{}", i)] = new_config.m_rage_weapons[i]->multipoints->m_arms;
				config_map_[std::format("ragebot_multipoint_legs_{}", i)] = new_config.m_rage_weapons[i]->multipoints->m_legs;
				config_map_[std::format("ragebot_multipoint_foot_{}", i)] = new_config.m_rage_weapons[i]->multipoints->m_foot;
			}

			if (new_config.m_rage_weapons[i]->autostop_option)
			{
				config_map_[std::format("ragebot_autostop_beetwen_shots_{}", i)] = new_config.m_rage_weapons[i]->autostop_option->m_beetwen_shot;
				config_map_[std::format("ragebot_autostop_accuracy_{}", i)] = new_config.m_rage_weapons[i]->autostop_option->m_accuracy;
				config_map_[std::format("ragebot_autostop_molotov_ignore_{}", i)] = new_config.m_rage_weapons[i]->autostop_option->m_molotov_ignore;
			}

			config_map_[std::format("ragebot_multipoint_scale_{}", i)] = new_config.m_rage_weapons[i]->point_scale;

			config_map_[std::format("ragebot_autostop_{}", i)] = new_config.m_rage_weapons[i]->autostop;
			config_map_[std::format("ragebot_hitchance_amount_{}", i)] = new_config.m_rage_weapons[i]->hitchance_amount;
			config_map_[std::format("ragebot_damage_{}", i)] = new_config.m_rage_weapons[i]->damage;
		}

		if (!new_config.m_legit_weapons.empty())
		{

		}

	}

	if (new_config.m_antiaim)
	{
		config_map_[xorstr_("antiaim_enable")] = new_config.m_antiaim->enabled;
		config_map_[xorstr_("antiaim_at_target")] = new_config.m_antiaim->at_target;
		config_map_[xorstr_("antiaim_pitch")] = new_config.m_antiaim->pitch;
		config_map_[xorstr_("antiaim_yaw")] = new_config.m_antiaim->yaw;
		config_map_[xorstr_("antiaim_yaw_offset")] = new_config.m_antiaim->yaw_offset;
		config_map_[xorstr_("antiaim_jitter")] = new_config.m_antiaim->jitter;
	}

	if (new_config.m_visuals)
	{
		config_map_[xorstr_("esp_name")] = new_config.m_visuals->name;
		config_map_[xorstr_("esp_name_color")] = new_config.m_visuals->name_color;
		config_map_[xorstr_("esp_box")] = new_config.m_visuals->box;
		config_map_[xorstr_("esp_box_color")] = new_config.m_visuals->box_color;
		config_map_[xorstr_("esp_health")] = new_config.m_visuals->health;
		if (new_config.m_visuals->flags)
		{
			config_map_[xorstr_("esp_flags_armor")] = new_config.m_visuals->flags->armor;
			config_map_[xorstr_("esp_flags_bomb")] = new_config.m_visuals->flags->bomb;
			config_map_[xorstr_("esp_flags_defuser")] = new_config.m_visuals->flags->defuser;
			config_map_[xorstr_("esp_flags_flashed")] = new_config.m_visuals->flags->flashed;
			config_map_[xorstr_("esp_flags_kits")] = new_config.m_visuals->flags->kits;
			config_map_[xorstr_("esp_flags_zeus")] = new_config.m_visuals->flags->zeus;
		}
		config_map_[xorstr_("esp_skeleton")] = new_config.m_visuals->skeleton;
		config_map_[xorstr_("esp_skeleton_color")] = new_config.m_visuals->skeleton_color;
		if (new_config.m_visuals->m_weapons)
		{
			config_map_[xorstr_("esp_weapons_icon")] = new_config.m_visuals->m_weapons->icon;
			config_map_[xorstr_("esp_weapons_name")] = new_config.m_visuals->m_weapons->name;
		}
		config_map_[xorstr_("chams_visible")] = new_config.m_visuals->chams_visible;
		config_map_[xorstr_("chams_visible_color")] = new_config.m_visuals->chams_visible_color;
		config_map_[xorstr_("chams_type")] = new_config.m_visuals->chams_type;
		config_map_[xorstr_("chams_invisible")] = new_config.m_visuals->chams_invisible;
		config_map_[xorstr_("chams_invisible_color")] = new_config.m_visuals->chams_invisible_color;
		config_map_[xorstr_("attachment_chams")] = new_config.m_visuals->attachment_chams;
		config_map_[xorstr_("attachment_chams_color")] = new_config.m_visuals->attachment_chams_color;
	}

	if (new_config.m_misc)
	{
		config_map_[xorstr_("misc_autopeek")] = new_config.m_misc->autopeek;
		config_map_[xorstr_("misc_duck_assist")] = new_config.m_misc->duck_assist;
		config_map_[xorstr_("ragebot_slowwalk")] = new_config.m_misc->slowwalk;
		config_map_[xorstr_("misc_bunnyhop")] = new_config.m_misc->bunnyhop;
		config_map_[xorstr_("misc_autostrafe")] = new_config.m_misc->auto_strafe;
		config_map_[xorstr_("misc_disable_light")] = new_config.m_misc->disable_light;
		config_map_[xorstr_("misc_penetration_crosshair")] = new_config.m_misc->penetration_crosshair;
		config_map_[xorstr_("misc_force_crosshair")] = new_config.m_misc->force_crosshair;
		config_map_[xorstr_("misc_blur")] = new_config.m_misc->blur;
		config_map_[xorstr_("misc_world_changer")] = new_config.m_misc->world_changer;
		config_map_[xorstr_("misc_grenade_trail_color")] = new_config.m_misc->grenade_trail_color;
		config_map_[xorstr_("misc_thirdperson")] = new_config.m_misc->thirdperson;
		config_map_[xorstr_("misc_thirdperson_amount")] = new_config.m_misc->thirdperson_amount;
		config_map_[xorstr_("misc_smoke_remove")] = new_config.m_misc->smoke_remove;
		config_map_[xorstr_("misc_server_impact")] = new_config.m_misc->server_impact;
		config_map_[xorstr_("misc_client_impact")] = new_config.m_misc->client_impact;
		config_map_[xorstr_("misc_bullet_trace")] = new_config.m_misc->bullet_trace;
		config_map_[xorstr_("misc_bullet_trace_color")] = new_config.m_misc->bullet_trace_color;
		config_map_[xorstr_("misc_bullet_trace_enemy")] = new_config.m_misc->bullet_trace_enemy;
		config_map_[xorstr_("misc_bullet_trace_enemy_color")] = new_config.m_misc->bullet_trace_enemy_color;
		config_map_[xorstr_("misc_grenade_trail")] = new_config.m_misc->grenade_trail;
		config_map_[xorstr_("misc_keybind")] = new_config.m_misc->keybind;
		config_map_[xorstr_("misc_spectators")] = new_config.m_misc->spectators;
		config_map_[xorstr_("misc_watermark")] = new_config.m_misc->watermark;
		config_map_[xorstr_("misc_onshot_capsule")] = new_config.m_misc->misc_onshot_capsule;
		config_map_[xorstr_("misc_remove_scope")] = new_config.m_misc->misc_remove_scope;
		config_map_[xorstr_("misc_remove_bob")] = new_config.m_misc->misc_remove_bob;
		config_map_[xorstr_("misc_norecoil")] = new_config.m_misc->misc_norecoil;
		config_map_[xorstr_("misc_remove_post_processing")] = new_config.m_misc->misc_remove_post_processing;
		config_map_[xorstr_("misc_remove_legs")] = new_config.m_misc->misc_remove_legs;
		config_map_[xorstr_("misc_auto_strafe")] = new_config.m_misc->auto_strafe;
		config_map_[xorstr_("misc_viewmodel_changer")] = new_config.m_misc->misc_viewmodel_changer;
		config_map_[xorstr_("misc_viewmodel_x")] = new_config.m_misc->misc_viewmodel_x;
		config_map_[xorstr_("misc_viewmodel_y")] = new_config.m_misc->misc_viewmodel_y;
		config_map_[xorstr_("misc_viewmodel_z")] = new_config.m_misc->misc_viewmodel_z;
		config_map_[xorstr_("misc_fov")] = new_config.m_misc->misc_fov;
		config_map_[xorstr_("misc_unlock_inventory")] = new_config.m_misc->misc_unlock_inventory;
		config_map_[xorstr_("misc_buybot")] = new_config.m_misc->misc_buybot;
		config_map_[xorstr_("misc_buybot_primary")] = new_config.m_misc->misc_buybot_primary;
		config_map_[xorstr_("misc_buybot_secondary")] = new_config.m_misc->misc_buybot_secondary;
		config_map_[xorstr_("misc_buybot_zeus")] = new_config.m_misc->misc_buybot_zeus;
		config_map_[xorstr_("misc_buybot_armor")] = new_config.m_misc->misc_buybot_armor;
		config_map_[xorstr_("misc_buybot_grenades")] = new_config.m_misc->misc_buybot_grenades;
		config_map_[xorstr_("misc_grenade_prediction")] = new_config.m_misc->misc_grenade_prediction;
		config_map_[xorstr_("misc_dark_mode")] = new_config.m_misc->misc_dark_mode;
		config_map_[xorstr_("misc_remove_grenade_crosshair")] = new_config.m_misc->misc_remove_grenade_crosshair;
		config_map_[xorstr_("misc_killfeed")] = new_config.m_misc->misc_preserve_killfeed;
		config_map_[xorstr_("esp_oof")] = new_config.m_misc->misc_esp_oof;
		config_map_[xorstr_("esp_oof_color")] = new_config.m_misc->misc_esp_oof_color;
		config_map_[xorstr_("misc_hitsound")] = new_config.m_misc->misc_hitsound;
		config_map_[xorstr_("misc_hitmarker")] = new_config.m_misc->misc_hitmarker;
		config_map_[xorstr_("ragebot_track")] = new_config.m_rage_global_settings->backtrack_mode;

		auto keybind_window = std::find_if(g_gui->m_windows.begin(), g_gui->m_windows.end(), [&](const auto x) {
			return x.m_window_name == xorstr_("Keybind");
			});

		if (!new_config.m_misc->keybind_position.empty())
		{
			keybind_window->m_window_position.x = new_config.m_misc->keybind_position[0];
			keybind_window->m_window_position.y = new_config.m_misc->keybind_position[1];
		}

		auto spectators_window = std::find_if(g_gui->m_windows.begin(), g_gui->m_windows.end(), [&](const auto x) {
			return x.m_window_name == xorstr_("Spectators");
			});

		if (!new_config.m_misc->spectators_position.empty())
		{
			spectators_window->m_window_position.x = new_config.m_misc->spectators_position[0];
			spectators_window->m_window_position.y = new_config.m_misc->spectators_position[1];
		}

		auto rapid_window = std::find_if(g_gui->m_windows.begin(), g_gui->m_windows.end(), [&](const auto x) {
			return x.m_window_name == xorstr_("Rapid");
			});

		if (!new_config.m_misc->rapid_position.empty())
		{
			rapid_window->m_window_position.x = new_config.m_misc->rapid_position[0];
			rapid_window->m_window_position.y = new_config.m_misc->rapid_position[1];
		}
	}

	g_hotkey->mutex_.lock();
	for (auto& hotkey : new_config.m_binds)
	{
		if (!g_hotkey->hotkeys_->contains(hotkey->hash))
			continue;

		auto& hotkey_ = g_hotkey->hotkeys_->at(hotkey->hash).binds.emplace_back();
		hotkey_.key = hotkey->key;
		hotkey_.mode = hotkey->mode;
		hotkey_.value = hotkey->value;
		hotkey_.visible = hotkey->visible;
		hotkey_.type = hotkey->type;
	}
	g_hotkey->mutex_.unlock();

	for (int i{}; i < new_config.m_added_item.size(); i++)
	{
		auto& item = new_config.m_added_item[i];
		c_econ_item new_econ_item = c_econ_item();
		auto pItem = new_econ_item.create_instance();
		if (pItem) {
			auto pInventory = Interfaces::m_cs_inventory_manager->get_local_inventory();

			pItem->id = item->id;
			pItem->account_id = uint32_t(pInventory->get_owner().m_id);
			pItem->def_index = item->item_def;
			pItem->rarity = item->rariry;

			float percent = float(item->paint_wear) / 100.f;

			pItem->set_stat_trak(item->stattrack);
			pItem->set_paint_kit(item->paint_id);
			pItem->set_paint_seed(item->paint_seed);
			pItem->set_paint_wear(percent);
			if (item->stickers_0 != -1)
				pItem->set_sticker(0, item->stickers_0);

			if (item->stickers_1 != -1)
				pItem->set_sticker(1, item->stickers_1);

			if (item->stickers_2 != -1)
				pItem->set_sticker(2, item->stickers_2);

			if (item->stickers_3 != -1)
				pItem->set_sticker(3, item->stickers_3);

			if (item->stickers_4 != -1)
				pItem->set_sticker(4, item->stickers_4);

			if (!item->custom_name.empty())
				pItem->set_custom_name(item->custom_name.c_str());

			pInventory->add_econ_item(pItem);
		}

		gui_skins item_temp;

		item_temp.item_def = item->item_def;
		item_temp.custom_name = item->custom_name;
		item_temp.is_initilization = false;
		item_temp.texture_id = -1;
		item_temp.name = item->name;
		item_temp.paint_id = item->paint_id;
		item_temp.paint_name = item->paint_name;
		item_temp.paint_seed = item->paint_seed;
		item_temp.paint_wear = item->paint_wear;
		item_temp.path_image = item->path_image;
		item_temp.type = item->type;
		item_temp.rarity = item->rariry;
		item_temp.stickers[0] = item->stickers_0;
		item_temp.stickers[1] = item->stickers_1;
		item_temp.stickers[2] = item->stickers_2;
		item_temp.stickers[3] = item->stickers_3;
		item_temp.stickers[4] = item->stickers_4;
		item_temp.skin_key = item->skin_key;
		item_temp.id = pItem->id;

		g_gui->skin_added.push_back(item_temp);
	}

	for (int i{}; i < new_config.m_equip_inventory.size(); i++)
	{
		auto& inventory = new_config.m_equip_inventory[i];
		Interfaces::m_cs_inventory_manager->equip_item(inventory->team, inventory->slot, inventory->item_id);
	}

	g_misc->add_notify(xorstr_("Load Config"), xorstr_(""), 7.f);
}

void CUser::Save(ProcessingRecord processing_record_)
{
	Processing(EProcessingType::Parse, ProcessingRecord(config_map_));

	flatbuffers::FlatBufferBuilder builder(20000);

	config_->m_verify = false;

	builder.Finish(CreateConfigSettings(builder, config_.get()));

	c_flatbuffers m_buffer_config;
	c_flatbuffers m_buffer;

	auto config = flatbuffers::GetMutableRoot<ConfigSettings>(builder.GetBufferSpan().data());
	auto table_config = reinterpret_cast<flatbuffers::Table*>(config);

	flatbuffers::Verifier verify_flat(builder.GetBufferSpan().data(), builder.GetBufferSpan().size());

	m_buffer_config.create_config(g_cs2->token, g_gui->select_config, g_web_utils->binary_to_string(builder.GetBufferSpan()));
	m_buffer_config.create_stream(false);

	m_buffer.create_request(HASH("save_config"), 1, m_buffer_config.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	builder.Release();
}

void CUser::Rename(ProcessingRecord processing_record_) {

	c_flatbuffers m_buffer_config;
	c_flatbuffers m_buffer;

	m_buffer_config.create_config(g_cs2->token, processing_record_.share, "", processing_record_.name);
	m_buffer_config.create_stream(false);

	m_buffer.create_request(HASH("rename_config"), 1, m_buffer_config.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	m_buffer.release();
	m_buffer_config.release();
}

void CUser::Delete(ProcessingRecord processing_record_) {

	c_flatbuffers m_buffer_config;
	c_flatbuffers m_buffer;

	m_buffer_config.create_config(g_cs2->token, processing_record_.share);
	m_buffer_config.create_stream(false);

	m_buffer.create_request(HASH("delete_config"), 1, m_buffer_config.m_buffer);
	m_buffer.create_stream();

	g_user->mutex_.lock();
	g_user->GetConfigs()[processing_record_.share].is_deleted = true;
	g_user->mutex_.unlock();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	m_buffer.release();
	m_buffer_config.release();
}

void CUser::Create(ProcessingRecord processing_record_) {

	c_flatbuffers m_buffer_config;
	c_flatbuffers m_buffer;

	m_buffer_config.create_config(g_cs2->token);
	m_buffer_config.create_stream(false);

	m_buffer.create_request(HASH("create_config"), 1, m_buffer_config.m_buffer);
	m_buffer.create_stream();

	g_tls_client->send(m_buffer.m_buffer.data(), m_buffer.m_buffer.size());

	m_buffer.release();
	m_buffer_config.release();
}

double GetElement(std::string str) {
	if (!g_user->config_map_.contains(str))
		return 0.f;

	return g_user->config_map_[str];
}

void CUser::Parse(ProcessingRecord processing_record_) {

	auto json = processing_record_.json;

	config_->m_rage_weapons.clear();
	config_->m_legit_weapons.clear();
	config_->m_binds.clear();
	config_->m_equip_inventory.clear();
	config_->m_added_item.clear();

	if (!config_->m_rage_global_settings)
		config_->m_rage_global_settings = std::make_unique<rage_global_settingsT>();

	config_->m_rage_global_settings->m_enabled = GetElement(xorstr_("ragebot_enable"));
	config_->m_rage_global_settings->m_auto_fire = GetElement(xorstr_("ragebot_auto_fire"));
	config_->m_rage_global_settings->m_silent = GetElement(xorstr_("ragebot_auto_silent"));
	config_->m_rage_global_settings->m_penetration = GetElement(xorstr_("ragebot_penetration"));
	config_->m_rage_global_settings->m_nospread = GetElement(xorstr_("ragebot_nospread"));
	config_->m_rage_global_settings->m_auto_scope = GetElement(xorstr_("ragebot_auto_scope"));
	config_->m_rage_global_settings->m_norecoil = GetElement(xorstr_("ragebot_norecoil"));

	for (int i{}; i < g_gui->groups_weapon.size(); i++)
	{
		if (config_->m_rage_weapons.size() <= i)
			config_->m_rage_weapons.emplace_back();

		if (i == -1 || g_gui->groups_weapon.at(i).empty())
			continue;

		{
			auto& weapon = config_->m_rage_weapons.at(i);
			weapon = std::make_unique<rage_settingsT>();
			weapon->hitboxes = std::make_unique<hitboxes_T>();
			weapon->multipoints = std::make_unique<hitboxes_T>();
			weapon->autostop_option = std::make_unique<autostop_option_T>();
			weapon->m_group = i;
			weapon->hitboxes->m_head = GetElement(std::format("ragebot_hitbox_head_{}", i));
			weapon->hitboxes->m_chest = GetElement(std::format("ragebot_hitbox_chest_{}", i));
			weapon->hitboxes->m_stomach = GetElement(std::format("ragebot_hitbox_stomach_{}", i));
			weapon->hitboxes->m_arms = GetElement(std::format("ragebot_hitbox_arms_{}", i));
			weapon->hitboxes->m_legs = GetElement(std::format("ragebot_hitbox_legs_{}", i));
			weapon->hitboxes->m_foot = GetElement(std::format("ragebot_hitbox_foot_{}", i));
			weapon->multipoints->m_head = GetElement(std::format("ragebot_multipoint_head_{}", i));
			weapon->multipoints->m_chest = GetElement(std::format("ragebot_multipoint_chest_{}", i));
			weapon->multipoints->m_stomach = GetElement(std::format("ragebot_multipoint_stomach_{}", i));
			weapon->multipoints->m_arms = GetElement(std::format("ragebot_multipoint_arms_{}", i));
			weapon->multipoints->m_legs = GetElement(std::format("ragebot_multipoint_legs_{}", i));
			weapon->multipoints->m_foot = GetElement(std::format("ragebot_multipoint_foot_{}", i));
			weapon->autostop_option->m_beetwen_shot = GetElement(std::format("ragebot_autostop_beetwen_shots_{}", i));
			weapon->autostop_option->m_accuracy = GetElement(std::format("ragebot_autostop_accuracy_{}", i));
			weapon->autostop_option->m_molotov_ignore = GetElement(std::format("ragebot_autostop_molotov_ignore_{}", i));
			weapon->point_scale = GetElement(std::format("ragebot_multipoint_scale_{}", i));
			weapon->autostop = GetElement(std::format("ragebot_autostop_{}", i));
			weapon->hitchance_amount = GetElement(std::format("ragebot_hitchance_amount_{}", i));
			weapon->damage = GetElement(std::format("ragebot_damage_{}", i));
		}

		if (config_->m_legit_weapons.size() <= i)
			config_->m_legit_weapons.emplace_back();

		{
			auto& weapon = config_->m_legit_weapons.at(i);
			weapon = std::make_unique<legit_settingsT>();
			weapon->m_group = i;
		}
	}

	if (!config_->m_antiaim)
		config_->m_antiaim = std::make_unique<antiaimT>();

	config_->m_antiaim->enabled = GetElement(xorstr_("antiaim_enable"));
	config_->m_antiaim->pitch = GetElement(xorstr_("antiaim_pitch"));
	config_->m_antiaim->yaw = GetElement(xorstr_("antiaim_yaw"));
	config_->m_antiaim->at_target = GetElement(xorstr_("antiaim_at_target"));
	config_->m_antiaim->yaw_offset = GetElement(xorstr_("antiaim_yaw_offset"));
	config_->m_antiaim->jitter = GetElement(xorstr_("antiaim_jitter"));

	if (!config_->m_visuals)
		config_->m_visuals = std::make_unique<visualsT>();

	config_->m_visuals->name = GetElement(xorstr_("esp_name"));
	config_->m_visuals->name_color = GetElement(xorstr_("esp_name_color"));
	config_->m_visuals->box = GetElement(xorstr_("esp_box"));
	config_->m_visuals->box_color = GetElement(xorstr_("esp_box_color"));
	config_->m_visuals->health = GetElement(xorstr_("esp_health"));

	if (!config_->m_visuals->flags)
		config_->m_visuals->flags = std::make_unique<flags_T>();

	config_->m_visuals->flags->armor = GetElement(xorstr_("esp_flags_armor"));
	config_->m_visuals->flags->bomb = GetElement(xorstr_("esp_flags_bomb"));
	config_->m_visuals->flags->defuser = GetElement(xorstr_("esp_flags_defuser"));
	config_->m_visuals->flags->flashed = GetElement(xorstr_("esp_flags_flashed"));
	config_->m_visuals->flags->kits = GetElement(xorstr_("esp_flags_kits"));
	config_->m_visuals->flags->zeus = GetElement(xorstr_("esp_flags_zeus"));
	config_->m_visuals->skeleton = GetElement(xorstr_("esp_skeleton"));
	config_->m_visuals->skeleton_color = GetElement(xorstr_("esp_skeleton_color"));

	if (!config_->m_visuals->m_weapons)
		config_->m_visuals->m_weapons = std::make_unique<weapons_T>();

	config_->m_visuals->m_weapons->icon = GetElement(xorstr_("esp_weapons_icon"));
	config_->m_visuals->m_weapons->name = GetElement(xorstr_("esp_weapons_name"));
	config_->m_visuals->chams_visible = GetElement(xorstr_("chams_visible"));
	config_->m_visuals->chams_visible_color = GetElement(xorstr_("chams_visible_color"));
	config_->m_visuals->chams_type = GetElement(xorstr_("chams_type"));
	config_->m_visuals->chams_invisible = GetElement(xorstr_("chams_invisible"));
	config_->m_visuals->chams_invisible_color = GetElement(xorstr_("chams_invisible_color"));
	config_->m_visuals->attachment_chams = GetElement(xorstr_("attachment_chams"));
	config_->m_visuals->attachment_chams_color = GetElement(xorstr_("attachment_chams_color"));

	if (!config_->m_misc)
		config_->m_misc = std::make_unique<miscT>();

	config_->m_misc->keybind_position.clear();
	config_->m_misc->spectators_position.clear();
	config_->m_misc->rapid_position.clear();

	config_->m_misc->autopeek = GetElement(xorstr_("misc_autopeek"));
	config_->m_misc->duck_assist = GetElement(xorstr_("misc_duck_assist"));
	config_->m_misc->slowwalk = GetElement(xorstr_("ragebot_slowwalk"));
	config_->m_misc->bunnyhop = GetElement(xorstr_("misc_bunnyhop"));
	config_->m_misc->misc_onshot_capsule = GetElement(xorstr_("misc_onshot_capsule"));
	config_->m_misc->misc_dark_mode = GetElement(xorstr_("misc_dark_mode"));
	config_->m_misc->misc_remove_scope = GetElement(xorstr_("misc_remove_scope"));
	config_->m_misc->misc_norecoil = GetElement(xorstr_("misc_norecoil"));
	config_->m_misc->misc_remove_post_processing = GetElement(xorstr_("misc_remove_post_processing"));
	config_->m_misc->misc_remove_legs = GetElement(xorstr_("misc_remove_legs"));
	config_->m_misc->misc_remove_bob = GetElement(xorstr_("misc_remove_bob"));
	config_->m_misc->misc_remove_grenade_crosshair = GetElement(xorstr_("misc_remove_grenade_crosshair"));
	config_->m_misc->auto_strafe = GetElement(xorstr_("misc_autostrafe"));
	config_->m_misc->disable_light = GetElement(xorstr_("misc_disable_light"));
	config_->m_misc->penetration_crosshair = GetElement(xorstr_("misc_penetration_crosshair"));
	config_->m_misc->force_crosshair = GetElement(xorstr_("misc_force_crosshair"));
	config_->m_misc->blur = GetElement(xorstr_("misc_blur"));
	config_->m_misc->world_changer = GetElement(xorstr_("misc_world_changer"));
	config_->m_misc->grenade_trail_color = GetElement(xorstr_("misc_grenade_trail_color"));
	config_->m_misc->thirdperson = GetElement(xorstr_("misc_thirdperson"));
	config_->m_misc->thirdperson_amount = GetElement(xorstr_("misc_thirdperson_amount"));
	config_->m_misc->smoke_remove = GetElement(xorstr_("misc_smoke_remove"));
	config_->m_misc->server_impact = GetElement(xorstr_("misc_server_impact"));
	config_->m_misc->client_impact = GetElement(xorstr_("misc_client_impact"));
	config_->m_misc->bullet_trace = GetElement(xorstr_("misc_bullet_trace"));
	config_->m_misc->bullet_trace_color = GetElement(xorstr_("misc_bullet_trace_color"));
	config_->m_misc->bullet_trace_enemy = GetElement(xorstr_("misc_bullet_trace_enemy"));
	config_->m_misc->bullet_trace_enemy_color = GetElement(xorstr_("misc_bullet_trace_enemy_color"));
	config_->m_misc->grenade_trail = GetElement(xorstr_("misc_grenade_trail"));
	config_->m_misc->keybind = GetElement(xorstr_("misc_keybind"));
	config_->m_misc->spectators = GetElement(xorstr_("misc_spectators"));
	config_->m_misc->misc_viewmodel_changer = GetElement(xorstr_("misc_viewmodel_changer"));
	config_->m_misc->misc_viewmodel_x = GetElement(xorstr_("misc_viewmodel_x"));
	config_->m_misc->misc_viewmodel_y = GetElement(xorstr_("misc_viewmodel_y"));
	config_->m_misc->misc_viewmodel_z = GetElement(xorstr_("misc_viewmodel_z"));
	config_->m_misc->misc_fov = GetElement(xorstr_("misc_fov"));
	config_->m_misc->watermark = GetElement(xorstr_("misc_watermark"));
	config_->m_misc->misc_unlock_inventory = GetElement(xorstr_("misc_unlock_inventory"));
	config_->m_misc->misc_buybot = GetElement(xorstr_("misc_buybot"));
	config_->m_misc->misc_buybot_secondary = GetElement(xorstr_("misc_buybot_secondary"));
	config_->m_misc->misc_buybot_primary = GetElement(xorstr_("misc_buybot_primary"));
	config_->m_misc->misc_buybot_zeus = GetElement(xorstr_("misc_buybot_zeus"));
	config_->m_misc->misc_buybot_armor = GetElement(xorstr_("misc_buybot_armor"));
	config_->m_misc->misc_buybot_grenades = GetElement(xorstr_("misc_buybot_grenades"));
	config_->m_misc->misc_grenade_prediction = GetElement(xorstr_("misc_grenade_prediction"));
	config_->m_misc->misc_preserve_killfeed = GetElement(xorstr_("misc_killfeed"));
	config_->m_misc->misc_esp_oof = GetElement(xorstr_("esp_oof"));
	config_->m_misc->misc_esp_oof_color = GetElement(xorstr_("esp_oof_color"));
	config_->m_misc->misc_hitsound = GetElement(xorstr_("misc_hitsound"));
	config_->m_misc->misc_hitmarker = GetElement(xorstr_("misc_hitmarker"));
	config_->m_rage_global_settings->backtrack_mode = GetElement(xorstr_("ragebot_track"));

	auto keybind_window = g_gui->find_window(xorstr_("Keybind"));
	auto keybind_spectators = g_gui->find_window(xorstr_("Spectators"));
	auto rapid_spectators = g_gui->find_window(xorstr_("Rapid"));

	if (keybind_window.has_value()) {
		config_->m_misc->keybind_position.emplace_back(keybind_window.value().m_window_position.x);
		config_->m_misc->keybind_position.emplace_back(keybind_window.value().m_window_position.y);
	}

	if (keybind_spectators.has_value()) {
		config_->m_misc->spectators_position.emplace_back(keybind_spectators.value().m_window_position.x);
		config_->m_misc->spectators_position.emplace_back(keybind_spectators.value().m_window_position.y);
	}

	if (rapid_spectators.has_value()) {
		config_->m_misc->rapid_position.emplace_back(rapid_spectators.value().m_window_position.x);
		config_->m_misc->rapid_position.emplace_back(rapid_spectators.value().m_window_position.y);
	}

	for (auto it = g_hotkey->hotkeys_->begin(); it != g_hotkey->hotkeys_->end(); it++)
	{
		for (auto& hotkey : it->second.binds)
		{
			auto& bind = config_->m_binds.emplace_back();
			bind = std::make_unique<Hotkey_T>();
			bind->hash = it->first;
			bind->key = hotkey.key;
			bind->mode = hotkey.mode;
			bind->value = hotkey.value;
			bind->visible = hotkey.visible;
			bind->type = hotkey.type;
		}
	}

	auto inventory = Interfaces::m_cs_inventory_manager->get_local_inventory();
	if (!inventory)
		return;

	for (int i = 0; i <= 3; i++)
	{
		c_econ_item_definition* item_view_loadout = nullptr;
		for (int j = 0; j <= 56; ++j) {
			c_econ_item_view* item_view_ = inventory->get_item_in_loadout(i, j);
			if (!item_view_)
				continue;

			auto econ_item_def = item_view_->static_data();

			auto& inventory_ = config_->m_equip_inventory.emplace_back();
			inventory_ = std::make_unique<InventoryT>();

			inventory_->item_id = item_view_->item_id();
			inventory_->team = i;
			inventory_->slot = j;
		}
	}

	for (auto& item : g_gui->skin_added)
	{
		ItemT item_temp;
		item_temp.item_def = item.item_def;
		item_temp.custom_name = item.custom_name;
		item_temp.is_initilization = false;
		item_temp.texture_id = -1;
		item_temp.name = item.name;
		item_temp.paint_id = item.paint_id;
		item_temp.paint_name = item.paint_name;
		item_temp.paint_seed = item.paint_seed;
		item_temp.paint_wear = item.paint_wear;
		item_temp.path_image = item.path_image;
		item_temp.type = item.type;
		item_temp.rariry = item.rarity;
		item_temp.stickers_0 = std::max(0,item.stickers[0]);
		item_temp.stickers_1 = std::max(0, item.stickers[1]);
		item_temp.stickers_2 = std::max(0, item.stickers[2]);
		item_temp.stickers_3 = std::max(0, item.stickers[3]);
		item_temp.stickers_4 = std::max(0, item.stickers[4]);
		item_temp.skin_key = item.skin_key;
		item_temp.id = item.id;

		config_->m_added_item.push_back(std::make_unique<ItemT>(item_temp));
	}
}