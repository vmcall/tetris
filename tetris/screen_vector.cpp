#include "screen_vector.hpp"

int16_t& screen_vector::x()
{
	return this->data_x;
}

int16_t& screen_vector::y()
{
	return this->data_y;
}
