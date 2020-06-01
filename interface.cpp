#include <iostream>

#include "interface.h"

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

std::string		Interface::printCellRow(int row)
{
	std::string result;
	result += std::to_string(row);
	for (int i = 0; i < 6; i++)
	{
		result += "│" + printCell(row, i);
	}
	result += "│";

	return result;
}



void	Interface::printGame()
{
	std::cout << "\n";
	std::cout << "┌────────────────┨ ZweiStein ┠────────────────────────────────────────────────────────┐\n";
	std::cout << "│                                             ┌──────────────┨ Hints ┠───────────────┐│\n";
	std::cout << "│ │A     │B     │C     │D     │E     │F     │ │     (You can hide unwanted hints     ││\n";
	std::cout << "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │        with H[00-99] command)        ││\n";
	std::cout << "│" << printCellRow(0)					    <<" │"<<printHintRow(0)              << "  ││\n";
	std::cout << "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │"<<printHintRow(1)              << "  ││\n";
	std::cout << "│" << printCellRow(1)						<<" │"<<printHintRow(2)              << "  ││\n";
	std::cout << "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │"<<printHintRow(3)              << "  ││\n";
	std::cout << "│" << printCellRow(2)						<<" │"<<printHintRow(4)              << "  ││\n";
	std::cout << "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │"<<printHintRow(5)              << "  ││\n";
	std::cout << "│" << printCellRow(3)						<<" │"<<printHintRow(6)              << "  ││\n";
	std::cout << "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │"<<printHintRow(7)              << "  ││\n";
	std::cout << "│" << printCellRow(4)						<<" │"<<printHintRow(8)              << "  ││\n";
	std::cout << "│─┼──────┼──────┼──────┼──────┼──────┼──────┤ │"<<printHintRow(9)              << "  ││\n";
	std::cout << "│" << printCellRow(5)						<<" │"<<printHintRow(10)             << "  ││\n";
	std::cout << "│─┴──────┴──────┴──────┴──────┴──────┴──────┘ └──────────────────────────────────────┘│\n";
	std::cout << "│ Commands MEMO: help, claim C[0-5][A-F][0-5], subvalue switch off S[0-5][A-F][0-5]   │\n";
	std::cout << "└─────────────────────────────────────────────────────────────────────────────────────┘\n";
	std::cout << ">";
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

std::string	Interface::printHintRow(size_t row)
{
	// 4 hints per row.
	std::string res;
	//Hints& hints = Hints::Instance();
	//if (hints.hints.size() > row * 4)
	{
		for (size_t index = row * 4; index < row * 4 + 4; index++)
		{
			res += printHint(index);
		}
	}
	//std::cout << res;
	return res;
}

void	Interface::printWin()
{
	std::cout <<"\nWIN!\n";
}

void	Interface::printLose()
{
	std::cout <<"\nLOSE!\n";
}
