#pragma once
#include "stdafx.h"

using vector_t = std::pair<int16_t, int16_t>;

struct tetromino
{
	tetromino(const uint8_t character, const std::initializer_list<vector_t> args) : elements(args), unique_character(character) {}

	auto operator[] (const size_t index) -> vector_t&
	{
		return elements[index];
	}

	auto get_elements() -> std::vector<vector_t>&
	{
		return elements;
	}
	
	auto get_character() -> const uint8_t
	{
		return unique_character;
	}
	
	auto get_size() -> const size_t
	{
		return elements.size();
	}

private:
	std::vector<vector_t> elements;
	uint8_t unique_character;
};