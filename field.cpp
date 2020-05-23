#include <random>
#include <algorithm>
#include <iostream>

#include "field.h"

Field::Field()
{
	std::random_device rd;
	std::mt19937 g(rd());
	for (auto &row : _field)
	{
		int val = 0;
		for (auto &col : row)
		{
			col.value = val;
			val++;
		}
	}

	for (auto &row : _field)
	{
		std::shuffle(row.begin(), row.end(), g);
	}

	for (std::size_t row = 0; row < _field.size(); row++)
	{
		for (std::size_t col = 0; col < _field[0].size(); col++)
		{
			_field[row][col].row = row;
			_field[row][col].col = col;
		}
	}

	// We need a few Cells, which are known to player, to start with.
	tryValue(0, 0, _field[0][0].value);
	tryValue(1, 1, _field[1][1].value);

}


bool	Field::tryValue(int row, int column, int val)
{
	bool res = _field[row][column].tryValue(val);
	// If we guessed the value, it would be logical to automatically
	// switch off corresponding subvalues in the whole row
	if (res)
	{
		for (auto cell: _field[row])
		{
			if (_field[row][column].player_knows_value == false)
			{
				switchOffSubValue(cell.row, cell.col, val);
			}
		}
	}

	return res;
}

bool	Field::switchOffSubValue(int row, int column, int subvalue_index)
{
	bool res = _field[row][column].switchOffSubValue(subvalue_index);
	if (res)
	{
		// If switching is ok we should also check if we can automatically switch off
		// something in the same row.
		if (_field[row][column].player_knows_value == true)
		{
			tryValue(row, column, subvalue_index);
		}
	}

	return res;

}

Cell*	Field::getCell(int row, int column)
{
	return &(_field[row][column]);
}

int	Field::determinant()
{
	int determinant = 0;
	for (auto cell_row: _field)
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
	for (auto cell_row: _field)
	{
		for (auto cell: cell_row)
		{
			cell.resetSubValues();
		}
	}
}

std::vector<Cell*>	Field::getAllCellsWhichValueIsKnownToPlayer()
{
	std::vector<Cell*> res;

	for (std::size_t row = 0; row < _field.size(); row++)
	{
		for (std::size_t col = 0; col < _field[0].size(); col++)
		{
			if (_field[row][col].player_knows_value)
			{
				res.push_back(&_field[row][col]);
			}
		}
	}

	return res;
}

bool		Field::isWin()
{
	for (auto cell_row: _field)
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
