#include "cell.h"
#include <assert.h>

Cell::Cell()
{

}

void Cell::resetSubValues()
{
	subvalues = {true, true, true, true, true, true};
}

int Cell::countSubValues()
{
	int res = 0;
	for (bool subvalue: subvalues)
	{
		if (subvalue == true)
		{
			res++;
		}
	}
	return res;
}

size_t	Cell::getIndexOfFirstTrueSubvalue()
{
	// We need it when countSubValues() == 1 to
	// determine which exactly subvalue is left.
	int res = 0;
	for (bool subvalue: subvalues)
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

int	Cell::getValue()
{
	return value;
}

void	Cell::setValue(int val)
{
	value = val;
}

