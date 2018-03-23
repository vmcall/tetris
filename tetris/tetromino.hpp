#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <initializer_list>
#include <vector>
#include <cstdint>
#include "screen_vector.hpp"


struct tetromino
{
	tetromino() = default;
	tetromino(const uint8_t new_color_code, const std::initializer_list<screen_vector> args) : elements(args), color_code(new_color_code) {}

	inline auto operator[] (const size_t index) -> screen_vector&
	{
		return this->elements[index];
	}

	inline auto get_elements() -> std::vector<screen_vector>&
	{
		return this->elements;
	}
	
	inline constexpr auto get_color() -> const uint8_t
	{
		return this->color_code;
	}
	
	inline auto get_size() -> const size_t
	{
		return this->elements.size();
	}

	inline auto rotate() -> tetromino
	{
		auto copy = *this;

		for (auto& part : copy.get_elements())
		{
			// ROTATING A 2D VECTOR CLOCK-WISE 
			// IS SIMPLE: (y, -x)
			// IN THIS CASE Y COORDINATE IS MIRRORED DUE TO 
			// SCREEN BUFFER STARTING FROM TOP-LEFT (READ CRT WIKIPEDIA)
			// SO CLOCKWISE ROTATION IS (-y, x)
			const auto old_x = part.x();
			part.x() = -part.y();
			part.y() = old_x;
		}

		return copy;
	}

private:
	std::vector<screen_vector> elements;
	uint8_t color_code;
};