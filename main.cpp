#include "game.h"
#include <ncurses.h>

int main()
{
	WINDOW * mainwin;
	setlocale(LC_ALL, "");

	if ( (mainwin = initscr()) == NULL )
	{
		fprintf(stderr, "Error initializing ncurses.\n");
		exit(EXIT_FAILURE);
	}
	noecho();
	curs_set(0);

	Game game;
	game.initPuzzle();
	game.start();

	delwin(mainwin);
	endwin();
	refresh();

	return EXIT_SUCCESS;
}
