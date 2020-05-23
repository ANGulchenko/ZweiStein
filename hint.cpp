#include "hint.h"

Hint::Hint()
{

}

Hint::~Hint()
{

}

HintVertical::HintVertical()
{
	type = HintType::vertical;

	std::vector<Cell*> basic_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	std::shuffle(basic_cells.begin(), basic_cells.end(), random_device);
	first_cell = basic_cells[0];

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
		//throw exception
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
		second_cell->tryValue(second_cell->value);
	}else
	{
		return false;
	}

	if (field.determinant() == old_determinant)
	{
		return false;
	}

	return true;
}

HintAjacent::HintAjacent()
{
	type = HintType::ajacent;

	std::vector<Cell*> basic_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	std::shuffle(basic_cells.begin(), basic_cells.end(), random_device);
	first_cell = basic_cells[0];

	// now we should find unknown to player cell in the ajacent columns
	int col = first_cell->col;

	std::vector<Cell*> unknown_cells;
	for (int r = 0; r < 6; r++)
	{
		if (col - 1 >= 0)
		{
			Cell* cell_tmp = Field::Instance().getCell(r, col-1);
			if (cell_tmp->player_knows_value == false)
			{
				unknown_cells.push_back(cell_tmp);
			}
		}
		if (col + 1 < 6)
		{
			Cell* cell_tmp = Field::Instance().getCell(r, col+1);
			if (cell_tmp->player_knows_value == false)
			{
				unknown_cells.push_back(cell_tmp);
			}
		}
	}

	if (!unknown_cells.empty())
	{
		std::shuffle(unknown_cells.begin(), unknown_cells.end(), random_device);
		second_cell = unknown_cells[0];
	}
	else
	{
		//throw exception
	}
}

HintAjacent::~HintAjacent()
{

}

bool HintAjacent::applyToField()
{
	Field& field = Field::Instance();
	int old_determinant = field.determinant();

	if (second_cell == nullptr)
	{
		return false;
	}

	size_t row = second_cell->row;
	int val = second_cell->value;

	size_t basic_col = first_cell->col;

	if (basic_col >= 1)
	{
		field.switchOffSubValue(row, basic_col - 1, val);
	}

	if (basic_col + 1 < 6)
	{
		field.switchOffSubValue(row, basic_col + 1, val);
	}


	if (field.determinant() == old_determinant)
	{
		return false;
	}

	return true;
}

