#pragma once
#include <Windows.h>
#include <cstdint>
#include <array>
#include "array2d.hpp"
#include "coordinate_data.hpp"

enum console_color
{
	dark_purple = 1,
	dark_green,
	dark_cyan,
	dark_red,
	dark_pink,
	dark_yellow,
	grey,
	dark_grey,
	dark_blue,
	green,
	cyan,
	red,
	pink,
	yellow,
	white
};



class console_controller
{
public:
	console_controller(const HANDLE hconsole, const int32_t width, const int32_t height);

	// GENERAL
	HANDLE& get_console_handle();
	void set_title(const std::wstring& title);

	// CONTROL
	bool get_key_press(const int32_t vkey);

	// FILLING
	void clear();
	void clear(const int16_t x, const int16_t y, const int16_t width, const int16_t height);
	void draw(const int16_t x, const int16_t y, const std::string& message, const uint16_t color_code = 0);
	void draw(const int16_t x, const int16_t y, const uint16_t character, const uint16_t color_code = 0);
	uint16_t read(const int16_t x, const int16_t y);
	void fill_horizontal(const int16_t x, const int16_t y, const uint16_t character, const uint16_t count, const uint16_t color_code = 0);

	// BUFFER
	void update_scene();
	void toggle_buffer_render(bool toggle);

	// POSITION
	void set_position(const int16_t x, const int16_t y);
	std::pair<int16_t, int16_t> get_position();

private:
	// BUFFER
	bool use_buffer;
	bool& should_use_buffer();
	array2d<coordinate_data> new_frame;
	array2d<coordinate_data> previous_frame;
	array2d<coordinate_data>& get_new_frame();
	array2d<coordinate_data>& get_previous_frame();

	// INPUT
	std::array<bool, 256> pressed_keys;
	std::array<bool, 256>& get_pressed_keys();

	// HANDLE
	HANDLE console_handle;
};