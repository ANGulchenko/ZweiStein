#include <iostream>
#include "game.h"
#include <curses.h>

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
	int ch;
	//timeout(-1);
	interface->printGame();
	while (!field.isWin())
	{
		interface->printGame();
		ch = getch();
		command->parse(ch);

		switch (command->type)
		{
			case CommandType::quit:
			{
				exit(0);
			}break;
			case CommandType::move_up:
			{
				interface->cursor.moveUp();
			}break;
			case CommandType::move_down:
			{
				interface->cursor.moveDown();
			}break;
			case CommandType::move_left:
			{
				interface->cursor.moveLeft();
			}break;
			case CommandType::move_right:
			{
				interface->cursor.moveRight();
			}break;
			case CommandType::claim:
			{
				bool res = field.tryValue(interface->cursor.row, interface->cursor.col, interface->cursor.subvalue);
				if (!res)
				{
					interface->printLose();
					exit(0);
				}
			}break;
			case CommandType::dismiss:
			{
				if (interface->cursor.zone == CursorZone::field)
				{
					bool res = field.switchOffSubValue(interface->cursor.row, interface->cursor.col, interface->cursor.subvalue);
					if (!res)
					{
						interface->printLose();
						exit(0);
					}
				}
			}break;

		}

/*		if (command->type == CommandType::error)
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

		*/
	}

	interface->printWin();

}
