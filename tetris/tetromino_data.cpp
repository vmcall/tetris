#include "tetromino_data.hpp"

screen_vector& tetromino_data::get_position()
{
	return this->position;
}

tetromino& tetromino_data::get_piece()
{
	return this->piece;
}

bool tetromino_data::valid()
{
	return this->is_valid;
}
