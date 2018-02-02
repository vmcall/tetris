#pragma once
#include "stdafx.h"
#include <cstdint>

using tetromino_vector_t = std::vector<std::tuple<vector_t, bool, tetromino>>;

class tetris
{
public:
	tetris(console_controller con, int32_t width, int32_t height) : 
		console(con), border_width(width), border_height(height), pieces(), solid_parts() {}

	void run();

private:
	void draw_boundary();
	void clear_game_frame();
	void draw_tetromino(const int16_t x, const int16_t y, tetromino comp);
	tetromino get_random_tetromino();
	vector_t get_random_start_position();

	console_controller console;
	
	// GAME BORDER
	int32_t border_width;
	int32_t border_height;
	
	// ENTITIES
	tetromino_vector_t pieces;
	std::vector<vector_t> solid_parts; // FOR COLLISION DETECTION
};