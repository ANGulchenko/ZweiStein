#include "hintthreeajacent.h"

HintThreeAjacent::HintThreeAjacent()
{
	type = HintType::threeAjacent;

	std::vector<Cell*> known_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	std::vector<Cell*> basic_cells;
	std::vector<Cell*> side1_cells;
	std::vector<Cell*> side2_cells;
	// We cannot use cells ajacent to the field border as basic cells

	for (auto iC = known_cells.begin(); iC != known_cells.end(); iC++)
	{
		Cell* cell_tmp = *iC;
		if (cell_tmp->col != 0 && cell_tmp->col != 5)
		{
			basic_cells.push_back(cell_tmp);
		}
	}

	if (basic_cells.size() < 1)
	{
		type = HintType::empty;
		return;
	}

	int second_cell_index = Randomizer2000::Instance().random(0, basic_cells.size()-1);
	second_cell = basic_cells[second_cell_index];
	size_t col = second_cell->col;

	for (size_t r = 0; r <= 5; r++)
	{
		side1_cells.push_back(Field::Instance().getCell(r, col-1));
		side2_cells.push_back(Field::Instance().getCell(r, col+1));
	}

	Randomizer2000::Instance().shuffle(side1_cells);
	Randomizer2000::Instance().shuffle(side2_cells);

	// We have 3 cells. Middle one already in its place
	// But 2 others must be randomly placed.

	std::vector<Cell*> temp_vector {side1_cells[0], side2_cells[0]};
	Randomizer2000::Instance().shuffle(temp_vector);

	first_cell = temp_vector[0];
	third_cell = temp_vector[1];
}

HintThreeAjacent::~HintThreeAjacent()
{

}

bool HintThreeAjacent::applyToField()
{
	const Field& field = Field::Instance();
	int old_determinant = field.determinant();

	if (first_cell  == nullptr ||
		second_cell == nullptr ||
		third_cell  == nullptr)
	{
		return false;
	}

	if (first_cell->player_knows_value &&
		second_cell->player_knows_value &&
		third_cell->player_knows_value)
	{
		return false;
	}

	size_t row1 = first_cell->row;
	int val1	= first_cell->getValue();

	size_t row2 = third_cell->row;
	int val2	= third_cell->getValue();

	for (size_t c = 0; c <= 5; c++)
	{
		if ((c != second_cell->row - 1) && (c != second_cell->row + 1))
		{
			Field::Instance().switchOffSubValue(row1, c, val1);
			Field::Instance().switchOffSubValue(row2, c, val2);
		}
	}



	int new_determinant = field.determinant();

	if (new_determinant == old_determinant)
	{
		return false;
	}

	return true;
}
