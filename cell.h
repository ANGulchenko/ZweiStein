#ifndef CELL_H
#define CELL_H

#include <cstddef>
#include <array>

class Cell
{
public:
	Cell();
	void	resetSubValues();
	int		countSubValues();
	size_t	getIndexOfFirstTrueSubvalue();
	int		getValue();
	void	setValue(int val);


	bool player_knows_value = false;
	std::array<bool, 6> subvalues = {true, true, true, true, true, true};
	std::size_t row;
	std::size_t col;
private:
	int value;
};

#endif // CELL_H
