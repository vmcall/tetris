#pragma once
#include "stdafx.h"

using window_procedure_t = LRESULT(*)(HWND window_handle, UINT msg, WPARAM wparam, LPARAM lparam);

class console_controller
{
public:
	console_controller(HANDLE hconsole);

	// GENERAL
	HANDLE& get_console_handle();
	void set_title(const std::wstring& title);

	// CONTROL
	bool get_key_press(const int32_t vkey);
	std::array<bool, 256>& get_pressed_keys();

	// FILLING
	void clear();
	void clear(const int16_t x, const int16_t y, const int16_t width, const int16_t height);
	void draw(const int16_t x, const int16_t y, const uint16_t character);
	void draw(const int16_t x, const int16_t y, const uint16_t character, const uint16_t color_code);
	uint16_t read(const int16_t x, const int16_t y);
	void fill_horizontal(const int16_t x, const int16_t y, const uint16_t character, const uint16_t count, const uint16_t color_code = 0);

	// POSITION
	void set_position(const int16_t x, const int16_t y);
	std::pair<int16_t, int16_t> get_position();

private:
	std::array<bool, 256> pressed_keys;
	HANDLE console_handle;
};