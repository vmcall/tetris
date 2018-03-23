#pragma once
#include <cstdint>

struct screen_vector
{
	screen_vector() = default;
	screen_vector(const int16_t new_x, const int16_t new_y) : data_x(new_x), data_y(new_y) {}

	bool operator ==(screen_vector other)
	{
		return other.x() == this->x() && other.y() == this->y();
	}

	int16_t& x();
	int16_t& y();

private:
	int16_t data_x;
	int16_t data_y;
};