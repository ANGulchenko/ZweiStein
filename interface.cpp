#include <iostream>

#include "interface.h"

Interface::Interface()
	: cursor(this)
	, _field (Field::Instance())
	, _hintAutoHide(true)

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

	setlocale(LC_ALL, "");

	mainwin = initscr();
	if (mainwin == NULL )
	{
		fprintf(stderr, "Error initializing ncurses.\n");
		exit(EXIT_FAILURE);
	}

	//int res = resizeterm(interfaceYSize+10, interfaceXSize+10);
	//wrefresh(mainwin);

	noecho();
	curs_set(0);

}

Interface::~Interface()
{
	curs_set(1);
	echo();

	delwin(mainwin);
	endwin();
	refresh();
}

std::string		Interface::printCell(int row, int col)
{
	Cell* cell = _field.getCell(row, col);
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
			print(3+r*2, 2+c*7, cell.c_str());
		}
	}
}



void	Interface::printGame()
{
	clear();
	if (!isTerminalHasEnoughSize())
	{
		printSmallTerminal();
		return;
	}
	print( 1, 0, "┌────────────────┨ ZweiStein ┠─────────────────────────────────────────────────┐");
	print( 2, 0, "│┌──────┬──────┬──────┬──────┬──────┬──────┐┌────────────┨ Hints ┠────────────┐│");
	print( 3, 0, "││      │      │      │      │      │      ││   You can hide unwanted hints   ││");
	print( 4, 0, "│├──────┼──────┼──────┼──────┼──────┼──────┤│     with  'dismiss' command     ││");
	print( 5, 0, "││      │      │      │      │      │      ││                                 ││");
	print( 6, 0, "│├──────┼──────┼──────┼──────┼──────┼──────┤│                                 ││");
	print( 7, 0, "││      │      │      │      │      │      ││                                 ││");
	print( 8, 0, "│├──────┼──────┼──────┼──────┼──────┼──────┤│                                 ││");
	print( 9, 0, "││      │      │      │      │      │      ││                                 ││");
	print(10, 0, "│├──────┼──────┼──────┼──────┼──────┼──────┤│                                 ││");
	print(11, 0, "││      │      │      │      │      │      ││                                 ││");
	print(12, 0, "│├──────┼──────┼──────┼──────┼──────┼──────┤│                                 ││");
	print(13, 0, "││      │      │      │      │      │      ││                                 ││");
	print(14, 0, "│└──────┴──────┴──────┴──────┴──────┴──────┘│                                 ││");
	print(15, 0, "│ Commands: (z)exit, (wasd)move, (q)claim,  │                                 ││");
	print(16, 0, "│           (e)dismiss, (p)help             └─────────────────────────────────┘│");
	print(17, 0, "│                                                           (h)HintAutoHide:NA │");
	print(18, 0, "└──────────────────────────────────────────────────────────────────────────────┘");

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

void	Interface::switchHintAutoHide()
{
	_hintAutoHide = !_hintAutoHide;
}

void	Interface::hideUselessHints()
{
	if (_hintAutoHide == false)
	{
		print(17, 82, "OFF");
		return;
	}

	print(17, 82, "ON");

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
	return "      ";
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
		print( 5+row, 45+col*8, hint.c_str());
	}
}

void	Interface::printWin()
{
	print( 1 + 7, 27, "┌─────────┨  Win  ┠─────────┐");
	print( 2 + 7, 27, "│                           │");
	print( 3 + 7, 27, "│       Not a big deal      │");
	print( 4 + 7, 27, "│  This game is too simple  │");
	print( 5 + 7, 27, "│                           │");
	print( 6 + 7, 27, "└───────────────────────────┘");
}

void	Interface::printLose()
{
	print( 1 + 7, 27, "┌─────────┨ Loser ┠─────────┐");
	print( 2 + 7, 27, "│                           │");
	print( 3 + 7, 27, "│       You have lost       │");
	print( 4 + 7, 27, "│    Don't do that again    │");
	print( 5 + 7, 27, "│                           │");
	print( 6 + 7, 27, "└───────────────────────────┘");
}

void	Interface::printSmallTerminal()
{
	print( 1 + 7, 27, "┌────┨ Need more space ┠────┐");
	print( 2 + 7, 27, "│                           │");
	print( 3 + 7, 27, "│ Your terminal should have │");
	print( 4 + 7, 27, "│  at least size of  86x18  │");
	print( 5 + 7, 27, "│                           │");
	print( 6 + 7, 27, "└───────────────────────────┘");
}

void	Interface::printHelp()
{
	clear();
	print( 1, 0, "┌────────────────────────────┨ ZweiStein Help and Rules┠───────────────────────┐");
	print( 2, 0, "│The game goal is to open all cards in square of 6x6 cards. Every row of square│");
	print( 3, 0, "│contains cards of one type only. For example, first row contains arabic digits│");
	print( 4, 0, "│second - letters, etc. Open next cards with method of exclusion. If card does │");
	print( 5, 0, "│not opened, cell contains any possible card. For example, │AB DEF│ means that │");
	print( 6, 0, "│this cell may contain every latin letter except C(because card with C image is│");
	print( 7, 0, "│absent. To open card use CLAIM button and to exclude card use DISMISS key.    │");
	print( 8, 0, "│ Use tips to solve this puzzle. There are 4 types of hints:                   │");
	print( 9, 0, "│1) Vertical hint. For example, 6⇕+. It means that 6 and + are in the same     │");
	print(10, 0, "│column.                                                                       │");
	print(11, 0, "│2) Ajacent hint. Like ÷⇔4. It states that ÷ and 4 are in the ajacent columns  │");
	print(12, 0, "│but it tells nothing about which letter is on the left and which is on the    │");
	print(13, 0, "│right.                                                                        │");
	print(14, 0, "│3) L-R hint. 3⋯√. It says that the 3 is on the left side of another but no    │");
	print(15, 0, "│information about the distance between those cards.                           │");
	print(16, 0, "│4) ₴⇔⚁⇔3. ⚁ is in the middle and others are at the ajacent columns. No info   │");
	print(17, 0, "│about about which is on the left and which is on the right, though.           │");
	print(18, 0, "└<Press any button to return>──────────────────────────────────────────────────┘");
}

void	Interface::print(int y, int x , const char* string)
{
	int currentXSize;
	int currentYSize;

	getmaxyx(mainwin, currentYSize, currentXSize);

	int delta_x = (currentXSize - interfaceXSize)/2;
	int delta_y = (currentYSize - interfaceYSize)/2;

	mvprintw(y+delta_y, x+delta_x, string);
}

bool	Interface::isTerminalHasEnoughSize()
{
	int currentXSize;
	int currentYSize;

	getmaxyx(mainwin, currentYSize, currentXSize);

	int delta_x = (currentXSize - interfaceXSize)/2;
	int delta_y = (currentYSize - interfaceYSize)/2;

	if (delta_x < 0 || delta_y < 0)
	{
		return false;
	}else
	{
		return true;
	}
}

/////////////////////////////////////////////////////////////////////

Cursor::Cursor(Interface* intrface)
	: row(0)
	, col(0)
	, subvalue(0)
	, zone(CursorZone::field)
	, hintNo(0)
	, hintRow(0)
	, hintCol(0)
	, interface (intrface)

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
			interface->print(3 + row * 2 - 1, 2 + col * 7 + subvalue, "🠛");
			interface->print(3 + row * 2 + 1, 2 + col * 7 + subvalue, "🠙");
		}break;
		case CursorZone::hints:
		{
			interface->print(5 + hintRow, 45 + hintCol * 8, "🠖");
			interface->print(5 + hintRow, 45 + hintCol * 8 + 6, "🠔");
		}break;
	}
}

size_t  Cursor::getHintNo()
{
	return hintRow * 4 + hintCol;
}
