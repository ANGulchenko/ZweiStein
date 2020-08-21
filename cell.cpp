#include "cell.h"
#include <algorithm>

Cell::Cell()
{

}

void Cell::resetSubValues()
{
	subvalues = {true, true, true, true, true, true};
}

int Cell::countSubValues() const
{
	return std::count_if(subvalues.begin(), subvalues.end(), [](bool i){return i == true;});
}

size_t	Cell::getIndexOfFirstTrueSubvalue() const
{
	// We need it when countSubValues() == 1 to
	// determine which exactly subvalue is left.

	int res = 0;
	for (const bool& subvalue: subvalues)
	{
		if (subvalue == true)
		{
			return res;
		}else
		{
			res++;
		}
	}
	return res;
}

int	Cell::getValue() const
{
	return value;
}

void	Cell::setValue(int val)
{
	value = val;
}

