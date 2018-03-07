#pragma once
#include <cstdint>

struct solid_piece
{
	solid_piece() : valid(false), color_code(0x00) {}

	bool& is_valid();
	uint16_t& get_color();

private:
	bool valid;
	uint16_t color_code;
};