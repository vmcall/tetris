#pragma once
#include <cstdint>

struct coordinate_data
{
	uint16_t& get_character();
	uint16_t& get_color();

	coordinate_data() : character(0), color_code(0) {}
	coordinate_data(const uint16_t new_character, const uint16_t new_color_code) : character(new_character), color_code(new_color_code) {}

	bool operator==(const coordinate_data& other)
	{
		return this->character == other.character && this->color_code == other.color_code;
	}

private:
	uint16_t character;
	uint16_t color_code;
};