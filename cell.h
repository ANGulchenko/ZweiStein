#ifndef CELL_H
#define CELL_H

#include <array>

class Cell
{
public:
	Cell();
	void resetSubValues();
	int countSubValues();

	int value;
	bool player_knows_value = false;
	std::array<bool, 6> subvalues = {true, true, true, true, true, true};
	int row;
	int col;
};

#endif // CELL_H
