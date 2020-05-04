#ifndef FIELD_H
#define FIELD_H

#include <array>

struct Cell
{
	int value;
	bool player_knows_value = false;
	std::array<bool, 6> subvalues = {true, true, true, true, true, true};
};

class Field
{
public:
	Field();
	void	fillField();
	bool	tryValue(int row, int column, int value);
	void	switchSubValue(int row, int column, int subvalue_index);
	Cell*	getCell(int row, int column);
	int		determinant();	// Works in the same way as in matrix.
							// Used to check if field has changed.
private:
	std::array<std::array<Cell, 6>, 6> _field; // row:column
};

#endif // FIELD_H
