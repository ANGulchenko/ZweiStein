#ifndef FIELD_H
#define FIELD_H

#include <array>
#include <vector>

#include "cell.h"

class Field
{
public:
	static Field& Instance()
	{
		static Field theSingleInstance;
		return theSingleInstance;
	}
	bool	tryValue(int row, int column, int value);
	bool	switchOffSubValue(int row, int column, int subvalue_index);
	Cell*	getCell(int row, int column);
	int		determinant();	// Works in the same way as in matrix.
							// Used to check if field has changed.
	void	resetSubValues();
	std::vector<Cell*>	getAllCellsWhichValueIsKnownToPlayer();
	bool	isWin();
	// getAllCellsWhichValueIsKnownToPlayer() is needed to make Hints more useful
	// not just pure random


private:
	Field();
	Field(const Field& root) = delete;
	Field& operator=(const Field&) = delete;

	std::array<std::array<Cell, 6>, 6> field; // row:column
};

#endif // FIELD_H
