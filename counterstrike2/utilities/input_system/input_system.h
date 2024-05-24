#pragma once

#include <array>
#include <Windows.h>
#include <windowsx.h>
#include <memory>

struct c_buttons
{
	bool hold_{};
	bool previous_hold_{};
	bool pressed_{};
	bool on_pressed_{};
	float repeat_time_{};
	bool first_press_{};
};

class c_input_system
{
public:
	void wrap_input(int msg, int wparam);
	void wrap_mouse_input(int msg, int wparam);
	void wrap_mouse_move(HWND hwnd);
	void wrap_mouse_scrolling(float scroll);
public:
	bool get_hold_key(int index) { return m_buttons_[index].hold_; }
	bool get_pressed_key(int index) { bool pressed = m_buttons_[index].pressed_; if (pressed) m_buttons_[index].pressed_ = false; return pressed; }
	bool get_on_pressed_key(int index) { return m_buttons_[index].on_pressed_; }
public:
	int get_delta_x() { return m_delta[0]; }
	int get_delta_y() { return m_delta[1]; }
	void reset_delta() {
		m_delta[0] = m_delta[1] = 0;
	}
public:
	void reset_scrolling()
	{
		m_scrolling = 0.f;
	}
	float get_scroll()
	{
		return m_scrolling;
	}
protected:
	std::array<c_buttons, 256> m_buttons_{};
	float m_delta[2]{};
	float m_mouse_pos[2]{};
	float m_scrolling{};
};

inline auto g_input_system = std::make_unique<c_input_system>();