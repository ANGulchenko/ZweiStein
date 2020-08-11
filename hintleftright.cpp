#include "hintleftright.h"



HintLeftRight::HintLeftRight()
{
	type = HintType::leftRight;

	std::vector<Cell*> basic_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	std::shuffle(basic_cells.begin(), basic_cells.end(), random_device);
	first_cell = basic_cells[0];

	// now we should find unknown to player cell with bigger column index
	int col = first_cell->col;


	std::vector<Cell*> unknown_cells;
	for (size_t r = 0; r < 6; r++)
	{
		for (size_t c = col + 1; c < 6; c++)
		{
			Cell* cell_tmp = Field::Instance().getCell(r, c);
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
		//std::cout << "second cell exists!"<<std::endl;
	}
	else
	{
		type = HintType::empty;
	}
}

HintLeftRight::~HintLeftRight()
{

}

bool HintLeftRight::applyToField()
{
	Field& field = Field::Instance();
	int old_determinant = field.determinant();

	if (first_cell == nullptr || second_cell == nullptr)
	{
		return false;
	}

	if (first_cell->player_knows_value && second_cell->player_knows_value)
	{
		return false;
	}

	if (first_cell->player_knows_value)
	{
		size_t row = second_cell->row;
		for (size_t c = 0; c <= first_cell->col; c++)
		{
			Field::Instance().switchOffSubValue(row, c, second_cell->getValue());
		}
	}

	if (second_cell->player_knows_value)
	{
		size_t row = first_cell->row;
		for (int c = 5; c >= static_cast<int>(first_cell->col); c--)
		{
			Field::Instance().switchOffSubValue(row, c, second_cell->getValue());
		}
	}


	int new_determinant = field.determinant();

	if (new_determinant == old_determinant)
	{
		return false;
	}

	return true;
}

