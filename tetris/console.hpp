#pragma once
#include "stdafx.h"

namespace console
{
	// GENERAL
	void initialise();
	void set_title(const std::wstring& title);

	// FILLING
	void clear();
	void clear(const int16_t x, const int16_t y, const int16_t width, const int16_t height);
	void draw(const int16_t x, const int16_t y, const uint16_t character);
	uint16_t read(const int16_t x, const int16_t y);
	void fill_horizontal(const int16_t x, const int16_t y, const uint16_t character, const uint16_t count);
	void fill_vertical(const int16_t x, const int16_t y, const uint16_t character, const uint16_t count);

	// POSITION
	void set_position(const int16_t x, const int16_t y);
	std::pair<int16_t, int16_t> get_position();

	// PRIVATE
	namespace details 
	{
		extern HANDLE console_handle;
	}
};