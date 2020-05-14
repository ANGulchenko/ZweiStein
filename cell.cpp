#include "cell.h"

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
