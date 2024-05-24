// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "input_system.h"
#include "../../gui/gui.h"
#include "../dx11_helper/dx11_helper.hpp"

void c_input_system::wrap_mouse_move(HWND hwnd)
{
	POINT p;
	if (GetCursorPos(&p) && GetForegroundWindow() == hwnd)
	{
		bool is_screen = ScreenToClient(hwnd, &p);

		if (p.x <= 0 || p.y <= 0 || p.x >= GetSystemMetrics(SM_CXSCREEN) || p.y >= GetSystemMetrics(SM_CYSCREEN))
			return;

		m_delta[0] += p.x - m_mouse_pos[0];
		m_delta[1] += p.y - m_mouse_pos[1];

		float delta_x = p.x - m_mouse_pos[0];
		float delta_y = p.y - m_mouse_pos[1];

		m_mouse_pos[0] = p.x;
		m_mouse_pos[1] = p.y;
		g_gui->set_mouse_pos(m_mouse_pos[0], m_mouse_pos[1]);
	}

	for (int i{}; i < m_buttons_.size(); i++)
	{
		auto& it = m_buttons_[i];
		if (it.hold_)
			it.hold_ = GetKeyState(i) & 0x8000;
	}
}

void c_input_system::wrap_mouse_input(int msg, int wparam)
{
	if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP)
	{
		bool is_keydown = msg == WM_LBUTTONDOWN;

		m_buttons_[VK_LBUTTON].hold_ = is_keydown;

		if (m_buttons_[VK_LBUTTON].hold_ && !m_buttons_[VK_LBUTTON].previous_hold_)
			m_buttons_[VK_LBUTTON].pressed_ = !m_buttons_[VK_LBUTTON].pressed_;

		if (m_buttons_[VK_LBUTTON].hold_ && !m_buttons_[VK_LBUTTON].previous_hold_)
			m_buttons_[VK_LBUTTON].on_pressed_ = !m_buttons_[VK_LBUTTON].pressed_;

		m_buttons_[VK_LBUTTON].previous_hold_ = m_buttons_[VK_LBUTTON].hold_;
	}

	if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP)
	{
		bool is_keydown = msg == WM_RBUTTONDOWN;

		m_buttons_[VK_RBUTTON].hold_ = is_keydown;

		if (m_buttons_[VK_RBUTTON].hold_ && !m_buttons_[VK_RBUTTON].previous_hold_)
			m_buttons_[VK_RBUTTON].pressed_ = !m_buttons_[VK_RBUTTON].pressed_;

		if (m_buttons_[VK_RBUTTON].hold_ && !m_buttons_[VK_RBUTTON].previous_hold_)
			m_buttons_[VK_RBUTTON].on_pressed_ = !m_buttons_[VK_RBUTTON].pressed_;

		m_buttons_[VK_RBUTTON].previous_hold_ = m_buttons_[VK_RBUTTON].hold_;
	}

	if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP)
	{
		bool is_keydown = msg == WM_MBUTTONDOWN;

		m_buttons_[VK_MBUTTON].hold_ = is_keydown;

		if (m_buttons_[VK_MBUTTON].hold_ && !m_buttons_[VK_MBUTTON].previous_hold_)
			m_buttons_[VK_MBUTTON].pressed_ = !m_buttons_[VK_MBUTTON].pressed_;

		if (m_buttons_[VK_MBUTTON].hold_ && !m_buttons_[VK_MBUTTON].previous_hold_)
			m_buttons_[VK_MBUTTON].on_pressed_ = !m_buttons_[VK_MBUTTON].pressed_;

		m_buttons_[VK_MBUTTON].previous_hold_ = m_buttons_[VK_MBUTTON].hold_;
	}

	if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONUP)
	{
		bool is_keydown = msg == WM_XBUTTONDOWN;
		int button = GET_XBUTTON_WPARAM(wparam);

		int key = button == 1 ? VK_XBUTTON1 : VK_XBUTTON2;

		m_buttons_[key].hold_ = is_keydown;

		if (m_buttons_[key].hold_ && !m_buttons_[key].previous_hold_)
			m_buttons_[key].pressed_ = !m_buttons_[key].pressed_;

		if (m_buttons_[key].hold_ && !m_buttons_[key].previous_hold_)
			m_buttons_[key].on_pressed_ = !m_buttons_[key].pressed_;

		m_buttons_[key].previous_hold_ = m_buttons_[key].hold_;
	}
}

void c_input_system::wrap_input(int msg, int wparam)
{
	if (wparam < 0 || wparam > 255)
		return;

	if (wparam == VK_LBUTTON)
		return;

	bool is_keydown = msg == WM_SYSKEYDOWN || msg == WM_KEYDOWN;

	m_buttons_[wparam].hold_ = is_keydown;

	if (m_buttons_[wparam].hold_ && !m_buttons_[wparam].previous_hold_)
		m_buttons_[wparam].pressed_ = !m_buttons_[wparam].pressed_;

	m_buttons_[wparam].previous_hold_ = m_buttons_[wparam].hold_;
}

void c_input_system::wrap_mouse_scrolling(float scroll)
{
	m_scrolling = scroll;
}