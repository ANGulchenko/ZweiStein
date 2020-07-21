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
	_hint_literals[HintType::leftRight] = "⋯";

	//_hints_visibility;
	_hints_visibility.resize(100, true);
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
	mvprintw( 1, 0, "┌────────────────┨ ZweiStein ┠───────────────────────────────────────────────────────┐");
	mvprintw( 2, 0, "│                                             ┌──────────────┨ Hints ┠──────────────┐│");
	mvprintw( 3, 0, "│ │A     │B     │C     │D     │E     │F     │ │     You can hide unwanted hints     ││");
	mvprintw( 4, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │       with  'dismiss' command       ││");
	mvprintw( 5, 0, "│1│      │      │      │      │      │      │ │                                     ││");
	mvprintw( 6, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                     ││");
	mvprintw( 7, 0, "│2│      │      │      │      │      │      │ │                                     ││");
	mvprintw( 8, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                     ││");
	mvprintw( 9, 0, "│3│      │      │      │      │      │      │ │                                     ││");
	mvprintw(10, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                     ││");
	mvprintw(11, 0, "│4│      │      │      │      │      │      │ │                                     ││");
	mvprintw(12, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                     ││");
	mvprintw(13, 0, "│5│      │      │      │      │      │      │ │                                     ││");
	mvprintw(14, 0, "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │                                     ││");
	mvprintw(15, 0, "│6│      │      │      │      │      │      │ │                                     ││");
	mvprintw(16, 0, "│─┴──────┴──────┴──────┴──────┴──────┴──────┘ └─────────────────────────────────────┘│");
	mvprintw(17, 0, "│ Commands MEMO: z - exit, wasd - move, q - claim, e - dismiss                       │");
	mvprintw(18, 0, "└────────────────────────────────────────────────────────────────────────────────────┘");
	printAllCells();
	hideUselessHints();
	printAllHints();
	cursor.draw();
}

void	Interface::printCommandError()
{
	std::cout << "Wrong command!\n";
}

void	Interface::changeVisibilityOfHint(size_t index)
{
	if (_hints_visibility.size() > index )
	{
		_hints_visibility[index] = !_hints_visibility[index];
	}
}

void	Interface::hideUselessHints()
{
	Hints& hints = Hints::Instance();
	for (size_t hintNo = 0; hintNo < hints.hints.size(); hintNo++)
	{
		Hint* hint = hints.hints[hintNo];
		if ((hint->first_cell == nullptr || hint->first_cell->player_knows_value) &&
			(hint->second_cell == nullptr || hint->second_cell->player_knows_value) &&
			(hint->third_cell == nullptr || hint->third_cell->player_knows_value)
			)
		{
			_hints_visibility[hintNo] = false;
		}
	}
}

std::string	Interface::printHint(size_t index)
{
	Hints& hints = Hints::Instance();
	if (hints.hints.size() > index && _hints_visibility[index] == true)
	{
		std::string res = " ";
		Hint* hint = hints.hints[index];

		switch (hint->type)
		{
			case HintType::vertical:
			{
				res += _literals[hint->first_cell->row][hint->first_cell->getValue()];
				res += _hint_literals[HintType::vertical];
				res += _literals[hint->second_cell->row][hint->second_cell->getValue()];
				res += "  ";
			}break;
			case HintType::ajacent:
			{
				res += _literals[hint->first_cell->row][hint->first_cell->getValue()];
				res += _hint_literals[HintType::ajacent];
				res += _literals[hint->second_cell->row][hint->second_cell->getValue()];
				res += "  ";
			}break;
			case HintType::leftRight:
			{
				res += _literals[hint->first_cell->row][hint->first_cell->getValue()];
				res += _hint_literals[HintType::leftRight];
				res += _literals[hint->second_cell->row][hint->second_cell->getValue()];
				res += "  ";
			}break;
			case HintType::threeAjacent:
			{
				res += _literals[hint->first_cell->row][hint->first_cell->getValue()];
				res += _hint_literals[HintType::ajacent];
				res += _literals[hint->second_cell->row][hint->second_cell->getValue()];
				res += _hint_literals[HintType::ajacent];
				res += _literals[hint->third_cell->row][hint->third_cell->getValue()];
			}break;

			default: break;
		}

		res += " ";

		return res;

	}
	return "       ";
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
	mvprintw( 1 + 7, 27, "┌─────────┨  Win  ┠─────────┐");
	mvprintw( 3 + 7, 27, "│                           │");
	mvprintw( 4 + 7, 27, "│       Not a big deal      │");
	mvprintw( 5 + 7, 27, "│  This game is too simple  │");
	mvprintw( 6 + 7, 27, "│                           │");
	mvprintw( 7 + 7, 27, "└───────────────────────────┘");
}

void	Interface::printLose()
{
	mvprintw( 1 + 7, 27, "┌─────────┨ Loser ┠─────────┐");
	mvprintw( 3 + 7, 27, "│                           │");
	mvprintw( 4 + 7, 27, "│       You have lost       │");
	mvprintw( 5 + 7, 27, "│    Don't do that again    │");
	mvprintw( 6 + 7, 27, "│                           │");
	mvprintw( 7 + 7, 27, "└───────────────────────────┘");
}

/////////////////////////////////////////////////////////////////////

Cursor::Cursor()
	: row(0)
	, col(0)
	, subvalue(0)
	, zone(CursorZone::field)
	, hintNo(0)
	, hintRow(0)
	, hintCol(0)

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
				}else
				if (col == 5)
				{
					// That is the right border.
					zone = CursorZone::hints;
					hintCol = 0;
					hintRow = 0;
				}
			}
		}break;
		case CursorZone::hints:
		{
			if (hintCol < 3)
			{
				hintCol++;
			}
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
			if (hintCol > 0)
			{
				hintCol--;
			}else
			if (hintCol == 0)
			{
				zone = CursorZone::field;
				col = 5;
				row = 0;
			}
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
			if (hintRow > 0)
			{
				hintRow--;
			}
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
			if (hintRow < 10)
			{
				hintRow++;
			}
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
			mvprintw(5 + hintRow, 47 + hintCol * 10, "🠖");
			mvprintw(5 + hintRow, 47 + hintCol * 10 + 5, "🠔");
		}break;
	}
}

size_t  Cursor::getHintNo()
{
	return hintRow * 4 + hintCol;
}
