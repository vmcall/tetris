#include "stdafx.h"
#include "console.hpp"
#define GWL_WNDPROC (-4)

console_controller::console_controller(const HANDLE hconsole, const int32_t width, const int32_t height)
{
	this->console_handle = hconsole;

	// SET WINDOW SIZE
	const auto window_handle = GetConsoleWindow();
	RECT window_rectangle;
	GetWindowRect(window_handle, &window_rectangle);
	MoveWindow(window_handle, window_rectangle.left, window_rectangle.top, width, height, true);

	// HIDE NATIVE CURSOR
	CONSOLE_CURSOR_INFO cursor_info{ 1, false };
	SetConsoleCursorInfo(this->get_console_handle(), &cursor_info);

	// SET UP BUFFER
	this->new_frame = array2d<coordinate_data>(height, width);
	this->previous_frame = array2d<coordinate_data>(height, width);
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
	if (this->use_buffer)
	{
		for (size_t row_index = 0; row_index < this->new_frame.row_count(); row_index++)
		{
			for (size_t element_index = 0; element_index < this->new_frame.row_size(); element_index++)
			{
				this->new_frame.get_element(row_index, element_index) = coordinate_data();
			}
		}
	}
	else
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
}
void console_controller::clear(const int16_t x, const int16_t y, const int16_t width, const int16_t height)
{
	if (this->use_buffer)
	{
		for (size_t row_index = y; row_index < y + height; row_index++)
		{
			for (size_t element_index = x; element_index < x + width; element_index++)
			{
				this->new_frame.get_element(row_index, element_index) = coordinate_data();
			}
		}
	}
	else
	{
		const std::string clear_buffer(width, ' ');
		for (int16_t i = 0; i < height; i++)
			fill_horizontal(x, y + i, ' ', width);
	}
}

void console_controller::draw(const int16_t x, const int16_t y, const std::string& message, const uint16_t color_code)
{
	if (this->use_buffer)
	{
		for (size_t i = 0; i < message.size(); i++)
		{
			this->new_frame.get_element(y, x + i) = coordinate_data(message[i], color_code);
		}
	}
	else
	{
		// SET COLOR
		if (color_code)
			SetConsoleTextAttribute(this->get_console_handle(), color_code);

		// SET POSITION AND WRITE
		this->set_position(x, y);
		printf("%s", message.c_str());
	}
}
void console_controller::draw(const int16_t x, const int16_t y, const uint16_t character, const uint16_t color_code)
{
	if (this->use_buffer)
	{
		this->new_frame.get_element(y, x) = coordinate_data(character, color_code);
	}
	else
	{
		// SET COLOR
		if (color_code)
			SetConsoleTextAttribute(this->get_console_handle(), color_code);

		// SET POSITION AND WRITE
		this->set_position(x, y);
		printf("%lc", character);
	}
}

uint16_t console_controller::read(const int16_t x, const int16_t y)
{
	if (this->use_buffer)
	{
		return this->new_frame.get_element(y, x).character;
	}
	else
	{
		CHAR_INFO buffer;
		SMALL_RECT rectangle{ x, y, x, y };
		const COORD coords{ x, y };
		const COORD size{ 1,1 };

		return ReadConsoleOutput(this->get_console_handle(), &buffer, size, coords, &rectangle) ? buffer.Char.UnicodeChar : L' ';
	}
}

void console_controller::fill_horizontal(const int16_t x, const int16_t y, const uint16_t character, const uint16_t count, const uint16_t color_code)
{
	if (this->use_buffer)
	{
		for (size_t i = 0; i < count; i++)
		{
			this->new_frame.get_element(y, x + i) = coordinate_data(character, color_code);
		}
	}
	else
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
}

void console_controller::update_scene()
{
	if (!this->use_buffer)
		return;

	// DRAW ONLY UPDATED SQUARES
	for (size_t row_index = 0; row_index < this->new_frame.row_count(); row_index++)
	{
		for (size_t element_index = 0; element_index < this->new_frame.row_size(); element_index++)
		{
			auto new_data = this->new_frame.get_element(row_index, element_index);
			auto previous_data = this->previous_frame.get_element(row_index, element_index);

			// DO NOT UPDATE CHARACTER
			if (new_data == previous_data)
				continue;

			if (new_data.color_code)
				SetConsoleTextAttribute(this->get_console_handle(), new_data.color_code);

			this->set_position(element_index, row_index);
			printf("%lc", new_data.character);
		}
	}

	this->previous_frame = this->new_frame;
}

void console_controller::toggle_buffer_render(bool toggle)
{
	this->use_buffer = toggle;
}

void console_controller::set_position(const int16_t x, const int16_t y)
{
	SetConsoleCursorPosition(this->get_console_handle(), COORD{ x, y });
}

std::pair<int16_t, int16_t> console_controller::get_position()
{
	CONSOLE_SCREEN_BUFFER_INFO  info;
	GetConsoleScreenBufferInfo(this->get_console_handle(), &info);

	return std::make_pair(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}
