#pragma once
#include "stdafx.h"
#include <map>

struct tetromino_data
{
	tetromino_data(screen_vector arg_position, bool arg_is_moving, tetromino arg_piece) : position(arg_position), is_moving(arg_is_moving), piece(arg_piece) {}

	screen_vector position;
	bool is_moving;
	tetromino piece;
};
struct solid_piece
{
	bool valid;
	uint8_t color_code;

	solid_piece() : valid(false), color_code(0x00) {}
};

template <typename T>
using vector_2d_t = std::vector<std::vector<T>>;
using steady_clock_t = std::chrono::steady_clock;
using tetromino_vector_t = std::vector<tetromino_data>;
using part_vector_t = std::vector<screen_vector>;
using key_handler_map_t = std::map<int32_t, void(*)(class tetris*, tetromino_data&, screen_vector, bool&)>;

class tetris
{
public:
	tetris(console_controller con, int32_t width, int32_t height, int16_t tetris_character) : console(con), border_width(width), border_height(height), piece_character(tetris_character), solid_pieces(height + 1)
	{
		std::for_each(solid_pieces.begin(), solid_pieces.end(), [width](auto& row) {
			row.resize(width + 1);
		});
	}

	void run();

private:
	template<class operation, class member>
	auto make_handler(member m)
	{
		return [=](tetris* instance, tetromino_data& data, screen_vector vector_copy, bool& add_new_piece)
		{
			vector_copy.*m = operation()(vector_copy.*m, 1);
			if (!instance->does_element_collide(data.piece, vector_copy))
				data.position.*m = operation()(data.position.*m, 1);
		}
	}

	void draw_boundary();
	void clear_game_frame();
	void draw_tetromino(const screen_vector position, tetromino comp);
	tetromino get_random_tetromino();
	screen_vector get_start_position();

	// GAME
	void game_loop();
	void draw_solid_parts();
	void handle_full_lines();
	void handle_moving_tetromino(tetromino_data &moving_piece, const bool &should_move_piece);
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

	// ENTITIES
	vector_2d_t<solid_piece> solid_pieces; // FOR COLLISION DETECTION
	//std::vector<screen_vector> solid_parts; 
};