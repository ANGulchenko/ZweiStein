﻿#include "hintvertical.h"

HintVertical::HintVertical()
{
	type = HintType::vertical;

	std::vector<Cell*> basic_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	std::shuffle(basic_cells.begin(), basic_cells.end(), random_device);
	first_cell = basic_cells[0];

	//std::cout << "HV first_cell_test. Row="<<first_cell->row<<" Col="<<first_cell->col << std::endl;

	// now we should find unknown to player cell in this col
	int col = first_cell->col;

	std::vector<Cell*> unknown_cells;
	for (int r = 0; r < 6; r++)
	{
		Cell* cell_tmp = Field::Instance().getCell(r, col);
		if (cell_tmp->player_knows_value == false)
		{
			unknown_cells.push_back(cell_tmp);
		}
	}

	//std::pair<int, int> second_cell;
	if (!unknown_cells.empty())
	{
		std::shuffle(unknown_cells.begin(), unknown_cells.end(), random_device);
		second_cell = unknown_cells[0];
	}
	else
	{
		type = HintType::empty;
	}

}

HintVertical::~HintVertical()
{

}

bool HintVertical::applyToField()
{
	Field& field = Field::Instance();
	// If determinant haven't changed after applying the Hint
	// that means that Hint is useless.
	int old_determinant = field.determinant();

	if (second_cell != nullptr)
	{
		field.tryValue(second_cell->row, second_cell->col, second_cell->getValue());
	}
	else
	{
		return false;
	}

	if (field.determinant() == old_determinant)
	{
		return false;
	}

	return true;
}
