#include "hintajacent.h"


HintAjacent::HintAjacent()
{
	type = HintType::ajacent;

	std::vector<Cell*> basic_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	int first_cell_index = Randomizer2000::Instance().random(0, basic_cells.size()-1);
	first_cell = basic_cells[first_cell_index];

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
		int second_cell_index = Randomizer2000::Instance().random(0, unknown_cells.size()-1);
		second_cell = unknown_cells[second_cell_index];
	}
	else
	{
		type = HintType::empty;
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
	int val = second_cell->getValue();

	size_t basic_col = first_cell->col;

	// At this moment we sure that we cannot guess VALUE so
	// we just must switch off VAL in all cells except adjacent.
	for (size_t c = 0; c < 6; c++)
	{
		//Cell* cell = field.getCell(row, c);
		if ((c == (basic_col - 1)) || (c == (basic_col + 1)))
		{
			// That are cell which can have VAl as val
			// so we do nothing with them
		}
		else
		{
			field.switchOffSubValue(row, c, val);
		}
	}

	int new_determinant = field.determinant();

	if (new_determinant == old_determinant)
	{
		return false;
	}

	return true;
}

