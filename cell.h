#ifndef CELL_H
#define CELL_H

#include <cstddef>
#include <array>

class Cell
{
public:
	Cell();
	void	resetSubValues();
	int		countSubValues() const;
	size_t	getIndexOfFirstTrueSubvalue() const;
	int		getValue() const;
	void	setValue(int val);


	bool player_knows_value = false;
	std::array<bool, 6> subvalues = {true, true, true, true, true, true};
	std::size_t row = 0;
	std::size_t col = 0;
private:
	int value = 0;
};

#endif // CELL_H
