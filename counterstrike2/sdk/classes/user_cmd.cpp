// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "../sdk.hpp"

void c_user_cmd::set_button_state(std::uint64_t button, EInButtonState call_type)
{
	auto v7 = ~button;

	if (call_type == EInButtonState::IN_BUTTON_DOWN)
	{
		buttons.buttonstate[0] = buttons.buttonstate[0] & v7 | button;
		base->buttons->buttons[EButtonType::HOLD] = base->buttons->buttons[EButtonType::HOLD] & v7 | button;
	}

	if (call_type == EInButtonState::IN_BUTTON_DOWN_UP)
	{
		buttons.buttonstate[1] = buttons.buttonstate[1] & v7 | button;
		base->buttons->buttons[EButtonType::PRESSED] = base->buttons->buttons[EButtonType::PRESSED] & v7 | button;
	}

	if (call_type == EInButtonState::IN_BUTTON_UP_DOWN_UP)
	{
		buttons.buttonstate[2] = buttons.buttonstate[2] & v7 | button;
		base->buttons->buttons[EButtonType::UNPRESSED] = base->buttons->buttons[EButtonType::UNPRESSED] & v7 | button;
	}
}

void c_user_cmd::remove_button_state(std::uint64_t button)
{
	buttons.buttonstate[0] &= ~button;
	buttons.buttonstate[1] &= ~button;
}

void c_user_cmd_base::Set(int button, bool pressed)
{
    //bool once = pressed;

    //for (int i{}; i < subtick_move.size; i++)
    //{
    //    auto subtick = subtick_move.Get(i);

    //    if (!subtick)
    //        continue;

    //    subtick->buttons = button;
    //    subtick->pressed = true;
    //    subtick->when = 0.865f;
    //}
}

void c_user_cmd_base::UnSet(int button, bool pressed)
{
    //for (int i{}; i < subtick_move.size; i++)
    //{
    //    auto subtick = subtick_move.Get(i);

    //    if (!subtick)
    //        continue;

    //    subtick->buttons = 0;
    //    subtick->pressed = false;
    //}
}

std::uint8_t c_user_cmd_base::get_cache_size()
{
	return CALL_VIRTUAL(std::uint8_t, 7, this);
}

void c_user_cmd_base::update_move_crc()
{
	std::uint8_t size = get_cache_size();

	c_utl_buffer buffer;
	buffer.ensure(size + 1);

	//if (serialize_partial_to_array(&buffer, size))
	//{
	//	message_lite message;
	//	message.parse_partial_to_array(&buffer, size);
	//	//message.merge(&move_crc);
	//}
}

void c_user_cmd::set_attack_history(int index) {
	for (int i{}; i < 3; i++) {
		attack_history_index[i] = index;
	}
}

c_subtick_move_step* c_user_cmd::create_subtick_step(void* arena) {
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 10 57 48 83 EC 20 33 FF 48 8B D9 48 85 C9 75 21 8D 4B 30 E8 ?? ?? ?? ?? 48 85 C0 74 06 48 89 78 08 EB 23 48 8B C7 48 8B 5C 24 38 48 83 C4 20 5F C3 4C 8D 05 ?? ?? ?? ?? BA 30 00 00 00 E8 ?? ?? ?? ?? 48 89 58 08 48 8B 5C 24 38 48 8D 0D ?? ?? ?? ?? 48 89 08 33 C9 48 89 48 10 89 78 2C" );
	return pattern.as<c_subtick_move_step * (__fastcall*)(void*)>()(arena);
}

c_subtick_move_step* c_user_cmd::create_subtick() {

	if (!base)
		return nullptr;

	if (base->subtick_move.m_pRep && base->subtick_move.m_nCurrentSize < base->subtick_move.m_pRep->m_nAllocatedSize) {
		return base->subtick_move.m_pRep->m_tElements[base->subtick_move.m_nCurrentSize++];
	}

	auto new_subtick = create_subtick_step(base->subtick_move.m_pArena);
	static auto pattern = g_utils->pattern_scan( g_cs2->m_module_system.get_client( ), "48 89 5C 24 08 57 48 83 EC 20 48 8B D9 48 8B FA 48 8B 49 10" );
	return pattern.as<c_subtick_move_step * (__fastcall*)(RepeatedPtrField_t<c_subtick_move_step>&, c_subtick_move_step*)>()(base->subtick_move, new_subtick);
}

void c_user_cmd::add_subtick(bool pressed, int button, bool needs_delete) {
	auto subtick = create_subtick();

	if (!subtick)
		return;

	subtick->has_bits = 7;
	subtick->buttons = button;
	subtick->pressed = pressed;
	subtick->unk = 4;
	subtick->when = 0.999f;
}

void c_user_cmd::set_input_history_angle(vector& angles)
{
	if (!input_history.m_pRep)
		return;

	for (std::int32_t i = 0; i < input_history.m_nCurrentSize; i++)
	{
		csgo_input_history_entry* tick = input_history.m_pRep->m_tElements[i];

		if (tick && tick->angle)
		{
			tick->angle->angles = angles;
		}
	}
}