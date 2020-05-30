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
//	hints.i_face = interface;
//	interface->printGame();
	hints.createFullSetOfHints();
	field.resetSubValues();
}

void	Game::start()
{
	//main cycle: print game| read and parse commands | use commands
	std::string command_str;

	while (!field.isWin())
	{
		interface->printGame();
		interface->printHints();
		std::cin >> command_str;
		command->parse(command_str);

		if (command->type == CommandType::error)
		{
			interface->printCommandError();
		}else
		if (command->type == CommandType::switch_subvalue)
		{
			bool res = field.switchOffSubValue(command->row, command->column, command->value);
			if (!res)
			{
				interface->printLose();
				exit(0);
			}
		}else
		if (command->type == CommandType::claim)
		{
			bool res = field.tryValue(command->row, command->column, command->value);
			if (!res)
			{
				interface->printLose();
				exit(0);
			}
		}
	}

	interface->printWin();

}
