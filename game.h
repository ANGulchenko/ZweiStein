#ifndef GAME_H
#define GAME_H

#include <array>

#include "interface.h"
#include "field.h"
#include "command.h"


class Game
{
public:
	Game();
	~Game();
	void	start();
	void	initPuzzle();

private:
	Field*		field;
	Interface*	interface;
	Command*	command;
};

#endif // GAME_H
