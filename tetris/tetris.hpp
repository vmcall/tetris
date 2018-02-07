#pragma once
#include "stdafx.h"

struct tetromino_data
{
	tetromino_data(screen_vector arg_position, bool arg_is_moving, tetromino arg_piece) : position(arg_position), is_moving(arg_is_moving), piece(arg_piece) {}

	screen_vector position;
	bool is_moving;
	tetromino piece;
};

using tetromino_vector_t = std::vector<tetromino_data>;
using part_vector_t = std::vector<screen_vector>;

class tetris
{
public:
	tetris(console_controller con, int32_t width, int32_t height) : console(con), border_width(width), border_height(height), pieces(), solid_parts() {}

	void run();

private:
	void draw_boundary();
	void clear_game_frame();
	void draw_tetromino(const screen_vector position, tetromino comp);
	tetromino get_random_tetromino();
	screen_vector get_random_start_position();

	// GAME
	void game_loop();
	void add_solid_parts(part_vector_t& parts, screen_vector& position);
	void handle_controls(tetromino_data& data);
	void move_piece(tetromino_data& data, bool& add_new_piece);

	// COLLISION
	bool does_element_collide(tetromino& piece, screen_vector position);
	bool collides(screen_vector part, screen_vector position);

	// CONSOLE I/O CONTROLLER
	console_controller console;
	
	// GAME BORDER
	int32_t border_width;
	int32_t border_height;
	
	// ENTITIES
	tetromino_vector_t pieces;
	std::vector<screen_vector> solid_parts; // FOR COLLISION DETECTION
};