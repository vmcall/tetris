#include "tetris.hpp"

// ENTRYPOINT
int main()
{
	auto my_console = console_controller(GetStdHandle(STD_OUTPUT_HANDLE), 400, 400);

	auto tetris_game = tetris(
		my_console, // CONSOLE HANDLE
		14,			// WIDTH
		20,			// HEIGHT
		'#');		// CHARACTER USED TO DRAW BORDER AND PIECES

	tetris_game.run();
}