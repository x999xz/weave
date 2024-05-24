// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

bool c_player_weapon_services::weapon_owns_this_type(const char* name)
{
	if (this->m_hmyweapons().get_size() <= 0)
		return false;

	bool find = false;

	for (int i{}; i < this->m_hmyweapons().get_size(); i++)
	{
		auto handle = this->m_hmyweapons().get_element(i);

		if (!handle.is_valid())
			continue;

		auto entity = Interfaces::entity_list->get_entity(handle.get_index());

		if (!entity)
			continue;

		if (!entity->get_class_information())
			continue;

		if (!entity->get_class_information()->first_name)
			continue;

		find = !strcmp(entity->get_class_information()->first_name, name);
	}


	return find;
}