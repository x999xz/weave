// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../hooks.hpp"

class weave_request2
{
public:
	std::uint64_t type;
	std::vector<int> items;
};

void hooks::recview_message::hook(std::uintptr_t* a1, c_network_serialize_pb* message_handle, std::uintptr_t* message, std::uint64_t* a4, std::uint64_t* a5, unsigned int a6, unsigned int a7)
{
	g_cs2->m_latest_hook = LoggerHack::RecviewMessage;
	if (message_handle->messageID != 47)
		return recview_message_original(a1, message_handle, message, a4, a5, a6,a7);

	c_svc_msg_voice_data* msg = (c_svc_msg_voice_data*)message;

	if(!msg)
		return recview_message_original(a1, message_handle, message, a4, a5, a6, a7);

	auto controller = Interfaces::entity_list->get_controller(msg->client + 1);

	if(!controller)
		return recview_message_original(a1, message_handle, message, a4, a5, a6, a7);

	if(!controller->is_controller())
		return recview_message_original(a1, message_handle, message, a4, a5, a6, a7);

	if (controller->is_local_player_controller())
		return recview_message_original(a1, message_handle, message, a4, a5, a6,a7);

	if (msg->xuid == FNV64("weave"))
		g_cs2->weave_users.try_emplace(controller->handle_player_pawn().get_handle());

	recview_message_original(a1, message_handle, message, a4, a5, a6,a7);
}