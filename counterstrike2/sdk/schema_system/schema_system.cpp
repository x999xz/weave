// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "schema_system.hpp"
#include "../interfaces/interfaces.hpp"

#include <unordered_map>
#include <ostream>
#include <sstream>
#include <fstream>
#include "../../Logging.h"
#include "../../utilities/fnv.h"

bool schema_system::initialize()
{
	add_trace(__PRETTY_FUNCTION__);
	std::vector<std::string> modules = { xorstr_("client.dll"), xorstr_("engine2.dll"), xorstr_("schemasystem.dll"), xorstr_("meshsystem.dll"), xorstr_("materialsystem2.dll"), xorstr_("scenesystem.dll"), xorstr_("animationsystem.dll"), xorstr_("particles.dll")};

	//for (int i{}; i < modules.size(); i++)
	//{
	//	auto module = modules[i];
	//	schema_system_type_scope* schema_class = Interfaces::schema_system->find_type_scope_for_module(module.c_str());

	//	if (!schema_class)	continue;

	//	utl_ts_hash<schema_class_binding_t*> schema_classes = schema_class->get_classes();

	//	for (schema_class_binding_t* binding : schema_classes.get_elements())
	//	{
	//		schema_class_info_data_t* client_class_info = schema_class->find_type_declared_class(binding->binary_name);

	//		if (!client_class_info)	continue;

	//		for (std::int16_t j = 0; j < client_class_info->field_size; j++)
	//		{
	//			schema_class_field_data_t* field = &client_class_info->fields[j];

	//			if (!binding->binary_name || !field || !field->name)	continue;

	//			schema_data[fnv64::hash_runtime(binding->binary_name)][fnv64::hash_runtime(field->name)] = xored_schema(field->offset);
	//		}
	//	}
	//}

	if (schema_data.size() == 0)
	{
		LogError("failed to initialize schema system\n");
		return false;
	}
	LogInfo("schema system initialized");
	return true;
}

std::uint32_t schema_system::get_schema(uint64_t class_name, uint64_t property_name)
{
	return schema_data.at(class_name).at(property_name);
}

