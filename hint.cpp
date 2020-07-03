#include "hint.h"
#include <iostream>

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

HintAjacent::HintAjacent()
{
	type = HintType::ajacent;

	std::vector<Cell*> basic_cells = Field::Instance().getAllCellsWhichValueIsKnownToPlayer();
	//std::cout << "basic_cells.size()="<<basic_cells.size()<<std::endl;
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
			//std::cout << "Adj. Left cell.r="<<r<<" col="<<col-1<<std::endl;
			if (cell_tmp->player_knows_value == false)
			{
				//std::cout << "Pushing Left cell"<<std::endl;
				unknown_cells.push_back(cell_tmp);
			}
		}
		if (col + 1 < 6)
		{
			Cell* cell_tmp = Field::Instance().getCell(r, col+1);
			//std::cout << "Adj. Right cell.r="<<r<<" col="<<col+1<<std::endl;
			if (cell_tmp->player_knows_value == false)
			{
				//std::cout << "Pushing Right cell"<<std::endl;
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
		//throw exception
		//std::cout << "unknown_cells.empty()"<<std::endl;
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

	// If one(only one!) of the ajacent cell is known to the player
	// that means that we know the other

	/////////////////////////////////////////////////////////////////////////
	// the basic cell is near the border, so it has only 1
	// suspect. And we know its value.

	/*if (basic_col == 0)
	{
		field.tryValue(row, 1, val);
		if (field.determinant() == old_determinant) return false;
	}else
	if (basic_col == 5)
	{
		field.tryValue(row, 4, val);
		if (field.determinant() == old_determinant) return false;
	}
	//////////////////////////////////////////////////////////////////////////

	Cell* suspect1 = field.getCell(row, basic_col - 1);
	Cell* suspect2 = field.getCell(row, basic_col + 1);

	if (suspect1->player_knows_value == true && suspect1->getValue() == val) return false;
	if (suspect2->player_knows_value == true && suspect2->getValue() == val) return false;
	if (suspect1->player_knows_value == true && suspect2->player_knows_value == true) return false;

	if ((suspect1->player_knows_value == true && suspect2->player_knows_value == false) ||
	   (suspect1->player_knows_value == false && suspect2->player_knows_value == true))
	{
		// only one suspect is known
		if (suspect1->player_knows_value == true)
		{
			field.tryValue(row, basic_col + 1, val);
			if (field.determinant() == old_determinant) return false;
		}else
		if (suspect2->player_knows_value == true)
		{
			field.tryValue(row, basic_col - 1, val);
			if (field.determinant() == old_determinant) return false;
		}
	}*/

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

