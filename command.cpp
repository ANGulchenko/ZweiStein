#include <ncurses.h>

#include "command.h"

Command::Command()
	: type (CommandType::error)
{

}

void	Command::parse(int button)
{
	switch (button)
	{
		case 'z':
		{
			type = CommandType::quit;
		}break;

		case 'w':
		case KEY_UP:
		{
			type = CommandType::move_up;
		}break;
		case 's':
		case KEY_DOWN:
		{
			type = CommandType::move_down;
		}break;
		case 'a':
		case KEY_LEFT:
		{
			type = CommandType::move_left;
		}break;
		case 'd':
		case KEY_RIGHT:
		{
			type = CommandType::move_right;
		}break;

		case 'q':
		{
			type = CommandType::claim;
		}break;
		case 'e':
		{
			type = CommandType::dismiss;
		}break;
		case 'h':
		{
			type = CommandType::toggle_autohide;
		}break;
		case 'p':
		{
			type = CommandType::help;
		}break;
		case 'm':
		{
			type = CommandType::about;
		}break;


	}

}
