#include <random>
#include <algorithm>

#include "field.h"

Field::Field()
{

}

void	Field::fillField()
{
	std::random_device rd;
	std::mt19937 g(rd());

	for (auto row : _field)
	{
		std::shuffle(row.begin(), row.end(), g);
	}
}

bool	Field::tryValue(int row, int column, int value)
{

}

void	Field::switchSubValue(int row, int column, int subvalue_index)
{
	_field[row][column].subvalues[subvalue_index] = !_field[row][column].subvalues[subvalue_index];
}

Cell*	Field::getCell(int row, int column)
{
	return &(_field[row][column]);
}

int	Field::determinant()
{

}
