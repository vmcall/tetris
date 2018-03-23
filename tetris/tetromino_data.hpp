#pragma once
#include <cstdint>
#include "tetromino.hpp"
#include "screen_vector.hpp"

struct tetromino_data
{
	tetromino_data() = default;
	tetromino_data(screen_vector new_position, tetromino new_piece) : position(new_position), piece(new_piece), is_valid(true) {}

	screen_vector& get_position();
	tetromino& get_piece();
	bool valid();

private:
	bool is_valid;
	screen_vector position;
	tetromino piece;
};