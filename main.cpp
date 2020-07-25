#include "game.h"
#include <ncurses.h>

int main()
{
	Game* game = new Game();
	game->initPuzzle();
	game->start();
	delete game;
	return EXIT_SUCCESS;
}
