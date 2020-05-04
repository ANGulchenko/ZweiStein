#include <iostream>
#include "game.h"

Game::Game()
{
	field = new Field();
	field->fillField();

	interface = new Interface(field);

	command = new Command();
}

Game::~Game()
{
	delete command;
	delete interface;
	delete field;
}

void	initPuzzle()
{
	// 1) Create random (with some probability) Hint;
	// 2) Apply it to the field;
			// a) if Hint was useful then apply all Hints until field stop changing
			// b) if Hint wasn't useful -- create new of the same type
	// 3) Check if Field is Filled, if not -- goto 1
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
			field->switchSubValue(command->row, command->column, command->value);
		}
	}

}
