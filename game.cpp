#include <iostream>
#include "game.h"

Game::Game()
	: field (Field::Instance())
	, hints (Hints::Instance())
{
//	field.fillField();

	interface = new Interface(&field);

	command = new Command();
}

Game::~Game()
{
	delete command;
	delete interface;
//	delete field;
}

void	Game::initPuzzle()
{
	interface->printGame();
	hints.createFullSetOfHints();
}

void	Game::start()
{
	//main cycle: print game| read and parse commands | use commands
	bool win = false;
	std::string command_str;

	while (!win)
	{
		interface->printGame();
		std::cin >> command_str;
		command->parse(command_str);

		if (command->type == CommandType::error)
		{
			interface->printCommandError();
		}else
		if (command->type == CommandType::switch_subvalue)
		{
			field.switchOffSubValue(command->row, command->column, command->value);
		}
	}

}
