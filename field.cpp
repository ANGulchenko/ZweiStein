﻿#include <random>
#include <algorithm>
#include <iostream>

#include "field.h"

Field::Field()
{
	std::random_device rd;
	std::mt19937 g(rd());
	for (auto &row : field)
	{
		int val = 0;
		for (auto &col : row)
		{
			col.setValue(val);
			val++;
		}
	}

	for (auto &row : field)
	{
		std::shuffle(row.begin(), row.end(), g);
	}

	for (std::size_t row = 0; row < field.size(); row++)
	{
		for (std::size_t col = 0; col < field[0].size(); col++)
		{
			field[row][col].row = row;
			field[row][col].col = col;
		}
	}

	// We need a few Cells, which are known to player, to start with.
	tryValue(0, 0, field[0][0].getValue());
	tryValue(1, 1, field[1][1].getValue());

}


bool	Field::tryValue(int row, int column, int val)
{
	Cell* test_cell = getCell(row, column);

	if (test_cell->getValue() == val)
	{
		test_cell->subvalues = {false, false, false, false, false, false};
		test_cell->subvalues[val] = true;
		test_cell->player_knows_value = true;

		// If we guessed the value, it would be logical to automatically
		// switch off corresponding subvalues in the whole row
		for (auto &cell: field[row])
		{
			if (cell.player_knows_value == false)
			{
				switchOffSubValue(cell.row, cell.col, val);
			}
		}

		return true;
	}

	return false;
}

bool	Field::switchOffSubValue(int row, int column, int subvalue_index)
{
	Cell* test_cell = getCell(row, column);

	// We lose if we try to switch off the real value
	if (test_cell->getValue() == subvalue_index)
	{
		return false;
	}
	test_cell->subvalues[subvalue_index] = false;

	// Maybe after switching off this subvalue we already know the real value?
	if (test_cell->countSubValues() <= 1)
	{
		tryValue(row, column, subvalue_index);
	}

	return true;

}

Cell*	Field::getCell(int row, int column)
{
	return &(field[row][column]);
}

int	Field::determinant()
{
	int determinant = 0;
	for (auto cell_row: field)
	{
		for (auto cell: cell_row)
		{
			determinant += cell.countSubValues();
		}
	}
	return determinant;
}

void	Field::resetSubValues()
{
	for (auto &cell_row: field)
	{
		for (auto &cell: cell_row)
		{
			cell.resetSubValues();
			cell.player_knows_value = false;
		}
	}

	tryValue(0, 0, field[0][0].getValue());
	tryValue(1, 1, field[1][1].getValue());
}

std::vector<Cell*>	Field::getAllCellsWhichValueIsKnownToPlayer()
{
	std::vector<Cell*> res;

	for (std::size_t row = 0; row < field.size(); row++)
	{
		for (std::size_t col = 0; col < field[0].size(); col++)
		{
			if (field[row][col].player_knows_value)
			{
				res.push_back(&field[row][col]);
			}
		}
	}

	return res;
}

bool		Field::isWin()
{
	for (auto cell_row: field)
	{
		for (auto cell: cell_row)
		{
			if (cell.player_knows_value == false)
			{
				return false;
			}
		}
	}

	return true;

}
