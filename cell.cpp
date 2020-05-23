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

bool	Cell::switchOffSubValue(std::size_t index)
{
	if (index < subvalues.size())
	{
		if (value == index)
		{
			// We're trying to dissmiss the real value of the Cell
			// That is GameOver
			return false;
		}
		else
		{
			subvalues[index] = false;
			if (countSubValues() <= 1)
			{
				// We have already dissmissed all subValues except one which
				// is obviously a real value.

				player_knows_value = true;
				return true;
			}
		}
	}

	return false;
}

bool	Cell::tryValue(int _value)
{
	if (_value == value)
	{
		subvalues = {false, false, false, false, false, false};
		player_knows_value = true;
		return true;
	}
	else
	{
		return false;
	}
}
