#pragma once
#include "stdafx.h"
#include "tetromino_data.hpp"
#include <map>
#include "array2d.hpp"

struct solid_piece
{
	bool valid;
	uint16_t color_code;

	solid_piece() : valid(false), color_code(0x00) {}
};

using steady_clock_t = std::chrono::steady_clock;
using key_handler_map_t = std::map<int32_t, void(*)(class tetris*, tetromino_data&, screen_vector, bool&)>;

class tetris
{
public:
	tetris(console_controller con, int32_t width, int32_t height, int16_t tetris_character) : console(con), border_width(width), border_height(height), piece_character(tetris_character), solid_pieces(height + 1, width + 1)
	{
	}

	void run();

private:
	void show_exit_screen();
	void draw_boundary();
	void clear_game_frame();
	void draw_tetromino(const screen_vector position, tetromino comp, const uint8_t color_code);
	tetromino get_random_tetromino();
	screen_vector get_start_position();

	// GAME
	void game_loop();
	void draw_score();
	void draw_ghost_tetromino(tetromino_data &moving_piece);
	void draw_solid_parts();
	void handle_full_lines();
	bool handle_moving_tetromino(tetromino_data &moving_piece, const bool &should_move_piece);
	void add_solid_parts(tetromino& piece, const screen_vector& position);
	void handle_controls(tetromino_data& data, bool& add_new_piece);
	void move_piece(tetromino_data& data, bool& add_new_piece);

	// COLLISION
	bool does_element_collide(tetromino& piece, screen_vector position);
	bool collides(screen_vector part, screen_vector position);

	// CONSOLE I/O CONTROLLER
	console_controller console;
	
	// GAME SETTINGS
	int32_t border_width;
	int32_t border_height;
	int16_t piece_character;

	// SCOREBOARD
	uint32_t score;

	// ENTITIES
	array2d<solid_piece> solid_pieces;
};