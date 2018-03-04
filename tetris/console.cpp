#include "stdafx.h"
#include "console.hpp"
#define GWL_WNDPROC (-4)

console_controller::console_controller(HANDLE hconsole)
{
	this->console_handle = hconsole;

	// SET WINDOW SIZE
	const auto window_handle = GetConsoleWindow();
	RECT window_rectangle;
	GetWindowRect(window_handle, &window_rectangle);
	MoveWindow(window_handle, window_rectangle.left, window_rectangle.top, 400, 400, true);

	// HIDE NATIVE CURSOR
	CONSOLE_CURSOR_INFO cursor_info{ 1, false };
	SetConsoleCursorInfo(this->get_console_handle(), &cursor_info);
}

HANDLE& console_controller::get_console_handle()
{
	return this->console_handle;
}

void console_controller::set_title(const std::wstring& title)
{
	SetConsoleTitleW(title.c_str());
}


bool console_controller::get_key_press(const int32_t vkey)
{
	const auto key_down = GetAsyncKeyState(vkey);
	const auto pressed_last_call = this->get_pressed_keys()[vkey];
	const auto result = key_down && !pressed_last_call;
	this->get_pressed_keys()[vkey] = key_down;

	return result;
}

std::array<bool, 256>& console_controller::get_pressed_keys()
{
	return this->pressed_keys;
}

void console_controller::clear()
{
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	if (!GetConsoleScreenBufferInfo(this->get_console_handle(), &buffer))
		return;

	const auto null_coords = COORD{ 0,0 };
	const auto count = buffer.dwSize.X * buffer.dwSize.Y;

	uint32_t written_count;
	if (!FillConsoleOutputCharacterW(this->get_console_handle(), static_cast<TCHAR>(' '), count, null_coords, reinterpret_cast<LPDWORD>(&written_count)))
		return;
}
void console_controller::clear(const int16_t x, const int16_t y, const int16_t width, const int16_t height)
{
	const std::string clear_buffer(width, ' ');
	for (int16_t i = 0; i < height; i++)
		fill_horizontal(x, y + i, ' ', width);
}

void console_controller::draw(const int16_t x, const int16_t y, const uint16_t character)
{
	// SET POSITION AND WRITE
	this->set_position(x, y);
	printf("%lc", character);
}
void console_controller::draw(const int16_t x, const int16_t y, const uint16_t character, const uint16_t color_code)
{
	// SET COLOR
	SetConsoleTextAttribute(this->get_console_handle(), color_code);

	// SET POSITION AND WRITE
	this->set_position(x, y);
	printf("%lc", character);
}

uint16_t console_controller::read(const int16_t x, const int16_t y)
{
	CHAR_INFO buffer;
	SMALL_RECT rectangle{ x, y, x, y };
	const COORD coords{ x, y };
	const COORD size{ 1,1 };

	return ReadConsoleOutput(this->get_console_handle(), &buffer, size, coords, &rectangle) ? buffer.Char.UnicodeChar : L' ';
}

void console_controller::fill_horizontal(const int16_t x, const int16_t y, const uint16_t character, const uint16_t count, const uint16_t color_code)
{
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	if (!GetConsoleScreenBufferInfo(this->get_console_handle(), &buffer))
		return;

	const auto coords = COORD{ x, y };

	uint32_t written_count;
	FillConsoleOutputCharacterW(this->get_console_handle(), character, count, coords, reinterpret_cast<LPDWORD>(&written_count));

	if (color_code)
		FillConsoleOutputAttribute(this->get_console_handle(), color_code, count, coords, reinterpret_cast<LPDWORD>(&written_count));
}

void console_controller::set_position(const int16_t x, const int16_t y)
{
	const auto coord = COORD{ x, y };
	SetConsoleCursorPosition(this->get_console_handle(), coord);
}

std::pair<int16_t, int16_t> console_controller::get_position()
{
	CONSOLE_SCREEN_BUFFER_INFO  info;
	GetConsoleScreenBufferInfo(this->get_console_handle(), &info);

	return std::make_pair(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}
