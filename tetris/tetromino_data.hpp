#pragma once
#include "stdafx.h"

struct tetromino_data
{
	tetromino_data(screen_vector arg_position, bool arg_is_moving, tetromino arg_piece) : position(arg_position), is_moving(arg_is_moving), piece(arg_piece) {}

	screen_vector position;
	bool is_moving;
	tetromino piece;
};