﻿#include <iostream>

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
}

std::string		Interface::printCell(int row, int col)
{
	Cell* cell = _field->getCell(row, col);
	std::string subvalue_str;

	if (cell->player_knows_value)
	{
		// Player knows the real value so there is no need to show subvalues
		subvalue_str += _literals[row][cell->value];
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

std::string		Interface::printRow(int row)
{
	std::string result;
	result += std::to_string(row);
	for (int i = 0; i < 6; i++)
	{
		result += "│" + printCell(row, i);
	}
	result += "│\n";

	return result;
}



void	Interface::printGame()
{
	std::cout << "\n";
	std::cout << "────────────────┨ ZweiStein ┣────────────────\n";
	std::cout << "\n";
	std::cout << " │A     │ B    │ C    │ D    │ E    │ F    │ \n";
	std::cout << "─┼──────┼──────┼──────┼──────┼──────┼──────┼─\n";
	std::cout << printRow(0);
	std::cout << "─┼──────┼──────┼──────┼──────┼──────┼──────┼─\n";
	std::cout << printRow(1);
	std::cout << "─┼──────┼──────┼──────┼──────┼──────┼──────┼─\n";
	std::cout << printRow(2);
	std::cout << "─┼──────┼──────┼──────┼──────┼──────┼──────┼─\n";
	std::cout << printRow(3);
	std::cout << "─┼──────┼──────┼──────┼──────┼──────┼──────┼─\n";
	std::cout << printRow(4);
	std::cout << "─┼──────┼──────┼──────┼──────┼──────┼──────┼─\n";
	std::cout << printRow(5);
	std::cout << "─┼──────┼──────┼──────┼──────┼──────┼──────┼─\n";
	std::cout << "\n";
	std::cout << "Enter command (claim:C[0-5][A-F][0-5]; switch:S[0-5][A-F][0-5]; hint:S[0-5][A-F]):";
}

void	Interface::printCommandError()
{
	std::cout << "Wrong command!\n";
}