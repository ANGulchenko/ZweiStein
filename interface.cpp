#include <iostream>

#include "interface.h"
#include <curses.h>

Interface::Interface(Field* field)
	: _field (field)
{
	_literals[0] = {"1", "2", "3", "4", "5", "6"};
	_literals[1] = {"A", "B", "C", "D", "E", "F"};
	_literals[2] = {"⚀", "⚁", "⚂", "⚃", "⚄", "⚅"};
	_literals[3] = {"Θ", "Ψ", "Π", "Σ", "Φ", "Ω"};
	_literals[4] = {"₹", "€", "£", "$", "¥", "₴"};
	_literals[5] = {"+", "-", "÷", "√", "×", "="};

	_hint_literals[HintType::vertical] = "⇕";
	_hint_literals[HintType::ajacent] = "⇔";
}

std::string		Interface::printCell(int row, int col)
{
	Cell* cell = _field->getCell(row, col);
	std::string subvalue_str;

	if (cell->player_knows_value)
	{
		// Player knows the real value so there is no need to show subvalues
		subvalue_str += _literals[row][cell->getValue()];
		subvalue_str += "▒▒▒▒▒";
	}else
	{
		for (int i = 0; i < 6; i++)
		{
			if (cell->subvalues[i] == true)
			{
				subvalue_str += _literals[row][i];
			}else
			{
				subvalue_str += " ";
			}
		}
	}
	return subvalue_str;
}

void		Interface::printAllCells()
{
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
		{
			std::string cell = printCell(r, c);
			mvprintw( 5+r*2, 3+c*7, cell.c_str());
		}
	}
}



void	Interface::printGame()
{
	clear();
	mvprintw( 1, 0, "┌────────────────┨ ZweiStein ┠────────────────────────────────────────────────────────┐");
	mvprintw( 2, 0, "│                                             ┌──────────────┨ Hints ┠───────────────┐│");
	mvprintw( 3, 0, "│ │A     │B     │C     │D     │E     │F     │ │     (You can hide unwanted hints     ││");
	mvprintw( 4, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │        with H[00-99] command)        ││");
	mvprintw( 5, 0, "│1│      │      │      │      │      │      │ │                                      ││");
	mvprintw( 6, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                      ││");
	mvprintw( 7, 0, "│2│      │      │      │      │      │      │ │                                      ││");
	mvprintw( 8, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                      ││");
	mvprintw( 9, 0, "│3│      │      │      │      │      │      │ │                                      ││");
	mvprintw(10, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                      ││");
	mvprintw(11, 0, "│4│      │      │      │      │      │      │ │                                      ││");
	mvprintw(12, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                      ││");
	mvprintw(13, 0, "│5│      │      │      │      │      │      │ │                                      ││");
	mvprintw(14, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                      ││");
	mvprintw(15, 0, "│6│      │      │      │      │      │      │ │                                      ││");
	mvprintw(16, 0, "│─┴──────┴──────┴──────┴──────┴──────┴──────┘ └──────────────────────────────────────┘│");
	mvprintw(17, 0, "│ Commands MEMO: help, claim C[0-5][A-F][0-5], subvalue switch off S[0-5][A-F][0-5]   │");
	mvprintw(18, 0, "└─────────────────────────────────────────────────────────────────────────────────────┘");
	printAllCells();
	printAllHints();
	cursor.draw();
}

void	Interface::printCommandError()
{
	std::cout << "Wrong command!\n";
}

std::string	Interface::printHint(size_t index)
{
	Hints& hints = Hints::Instance();
	if (hints.hints.size() > index)
	{
		std::string res = "";
		if (index < 10) res += "0"; // All indexes should be two-digits
		Hint* hint = hints.hints[index];
		switch (hint->type)
		{
			case HintType::vertical:
			{
				res += std::to_string(index) + ")";
				res += _literals[hint->first_cell->row][hint->first_cell->getValue()];
				res += _hint_literals[HintType::vertical];
				res += _literals[hint->second_cell->row][hint->second_cell->getValue()];
				res += "   ";
			}break;
			case HintType::ajacent:
			{
				res += std::to_string(index) + ")";
				res += _literals[hint->first_cell->row][hint->first_cell->getValue()];
				res += _hint_literals[HintType::ajacent];
				res += _literals[hint->second_cell->row][hint->second_cell->getValue()];
				res += "   ";
			}break;

			default: break;
		}

		return res;

	}
	return "         ";
}

void	Interface::printAllHints()
{
	Hints& hints = Hints::Instance();
	const size_t hints_per_row = 4;

	for (size_t index = 0; index < hints.hints.size(); index++)
	{
		const int row = index / hints_per_row;
		const int col = index % hints_per_row;
		std::string hint = printHint(index);
		mvprintw( 5+row, 47+col*10, hint.c_str());
	}
}

void	Interface::printWin()
{
	std::cout <<"\nWIN!\n";
}

void	Interface::printLose()
{
	std::cout <<"\nLOSE!\n";
}

/////////////////////////////////////////////////////////////////////

Cursor::Cursor()
	: row(0)
	, col(0)
	, subvalue(0)
	, hint(0)
	, zone(CursorZone::field)
{

}
void Cursor::moveRight()
{
	switch (zone)
	{
		case CursorZone::field:
		{
			if (subvalue <= 4)
			{
				subvalue++;
			}else
			if (subvalue == 5)
			{
				if (col <= 4)
				{
					col++;
					subvalue = 0;
				}
			}
		}break;
		case CursorZone::hints:
		{

		}break;
	}
}

void Cursor::moveLeft()
{
	switch (zone)
	{
		case CursorZone::field:
		{
			if (subvalue > 0)
			{
				subvalue--;
			}else
			if (subvalue == 0)
			{
				if (col > 0)
				{
					col--;
					subvalue = 5;
				}
			}
		}break;
		case CursorZone::hints:
		{

		}break;
	}
}

void Cursor::moveUp()
{
	switch (zone)
	{
		case CursorZone::field:
		{
			if (row > 0)
			{
				row--;
			}
		}break;
		case CursorZone::hints:
		{

		}break;
	}
}

void Cursor::moveDown()
{
	switch (zone)
	{
		case CursorZone::field:
		{
			if (row < 5)
			{
				row++;
			}
		}break;
		case CursorZone::hints:
		{

		}break;
	}
}

void Cursor::draw()
{
	switch (zone)
	{
		case CursorZone::field:
		{
			mvprintw(5 + row * 2 - 1, 3 + col * 7 + subvalue, "🠛");
			mvprintw(5 + row * 2 + 1, 3 + col * 7 + subvalue, "🠙");
		}break;
		case CursorZone::hints:
		{

		}break;
	}
}
