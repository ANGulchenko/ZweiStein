#include "hintvertical.h"

HintVertical::HintVertical()
{
	type = HintType::vertical;

	std::vector<Cell*> basic_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	int first_cell_index = Randomizer2000::Instance().random(0, basic_cells.size()-1);
	first_cell = basic_cells[first_cell_index];

	// now we should find all unknown to player cells in this col
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

	// ... and select a random one from this vector
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
