#include <algorithm>
#include <iostream>

#include "field.h"
#include "Randomizer2000.h"

Field::Field()
{
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
		Randomizer2000::Instance().shuffle(row);
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
	int r1 = Randomizer2000::Instance().random(0, 5);
	int c1 = Randomizer2000::Instance().random(0, 5);
	int r2 = Randomizer2000::Instance().random(0, 5);
	int c2 = Randomizer2000::Instance().random(0, 5);

	aFewAlreadyKnownCellsToBeginALevelWith.push_back(std::make_pair(r1, c1));
	aFewAlreadyKnownCellsToBeginALevelWith.push_back(std::make_pair(r2, c2));

	for (auto cell_coord : aFewAlreadyKnownCellsToBeginALevelWith)
	{
		tryValue(cell_coord.first, cell_coord.second, field[cell_coord.first][cell_coord.second].getValue());
	}
}


bool	Field::tryValue(int row, int column, int val)
{
	Cell* test_cell = getCell(row, column);
	if (test_cell->player_knows_value == true)
	{
		return true;
	}

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
		tryValue(row, column, test_cell->getIndexOfFirstTrueSubvalue());
	}

	// After switching off subvalue here there is a chance that
	// only one such subvalue left in the whole row. Obviously
	// we can "try" it.
	int counter = 0;
	size_t good_c = 0;
	for (size_t c = 0; c < 6; c++)
	{
		Cell* t_cell = getCell(row, c);
		if (t_cell->subvalues[subvalue_index] == true)
		{
			counter++;
			good_c = c;
		}
	}

	if (counter == 1)
	{
		tryValue(row, good_c, subvalue_index);
	}

	return true;

}

Cell*	Field::getCell(int row, int column)
{
	return &(field[row][column]);
}

int	Field::determinant() const
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

	for (auto cell_coord : aFewAlreadyKnownCellsToBeginALevelWith)
	{
		tryValue(cell_coord.first, cell_coord.second, field[cell_coord.first][cell_coord.second].getValue());
	}
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
	for (const auto& cell_row: field)
	{
		for (const auto& cell: cell_row)
		{
			if (cell.player_knows_value == false)
			{
				return false;
			}
		}
	}

	return true;

}
