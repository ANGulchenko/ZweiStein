#ifndef CELL_H
#define CELL_H

#include <array>

class Cell
{
public:
	Cell();
	void	resetSubValues();
	int		countSubValues();
	bool	tryValue(int value);
	bool	switchOffSubValue(std::size_t index);

	int value;
	bool player_knows_value = false;
	std::array<bool, 6> subvalues = {true, true, true, true, true, true};
	std::size_t row;
	std::size_t col;
};

#endif // CELL_H
