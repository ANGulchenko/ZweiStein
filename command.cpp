#include "command.h"

Command::Command()
{

}

void	Command::parse(std::string command)
{
	// claim:C[0-5][A-F][0-5]
	// switch:S[0-5][A-F][0-5]
	// hint:H[0-5][0-100])


	if (command.compare(0, 1, "C") == 0)
	{
		type = CommandType::claim;
	}else
	if (command.compare(0, 1, "S") == 0)
	{
	type = CommandType::switch_subvalue;
	}else
	if (command.compare(0, 1, "H") == 0)
	{
		type = CommandType::switch_hint;
	}else
	{
		type = CommandType::error;
		return;
	}

	try
	{
		row = std::stoi(command.substr(1, 1));
	}
	catch (...)
	{
		type = CommandType::error;
		return;
	}

	if (type == CommandType::claim || type == CommandType::switch_subvalue)
	{
		// Third char is column coordinate
		char col = command.substr(2, 1)[0];
		switch (col)
		{
			case 'A':
			case 'a':
			{
				column = 0;
			}break;
			case 'B':
			case 'b':
			{
				column = 1;
			}break;
			case 'C':
			case 'c':
			{
				column = 2;
			}break;
			case 'D':
			case 'd':
			{
				column = 3;
			}break;
			case 'E':
			case 'e':
			{
				column = 4;
			}break;
			case 'F':
			case 'f':
			{
				column = 5;
			}break;
			default:
			{
				type = CommandType::error;
				return;
			}
		}

		// All remaining chars are "value"
		try
		{
			value = std::stoi(command.substr(3));
		}
		catch (...)
		{
			type = CommandType::error;
			return;
		}

	}else
	{
		// All chars until the end of command are hint number
		try
		{
			value = std::stoi(command.substr(2));
		}
		catch (...)
		{
			type = CommandType::error;
			return;
		}
		return;
	}

}
