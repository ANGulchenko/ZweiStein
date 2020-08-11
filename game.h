#ifndef GAME_H
#define GAME_H

#include <array>

#include "interface.h"
#include "field.h"
#include "hints.h"
#include "command.h"

enum class GameStatus { gameContinues, gameWon, gameLost};

class Game
{
public:
	Game();
	~Game();
	void	start();
	void	initPuzzle();

private:
	Field&		field;
	Hints&		hints;
	Interface	interface;
	Command		command;
	GameStatus	gameStatus;
};

#endif // GAME_H
