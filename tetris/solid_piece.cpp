#include "solid_piece.hpp"

bool& solid_piece::is_valid()
{
	return this->valid;
}

uint16_t& solid_piece::get_color()
{
	return this->color_code;
}
