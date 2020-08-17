#ifndef HINT_H
#define HINT_H

#include <utility>
#include <random>
#include <algorithm>

#include "field.h"
#include "Randomizer2000.h"


enum class HintType {empty, vertical, ajacent, leftRight, threeAjacent};

class Hint
{
public:
	Hint();
	virtual ~Hint();

	bool	virtual applyToField() = 0;

	HintType type;
	Cell* first_cell = nullptr;
	Cell* second_cell = nullptr;
	Cell* third_cell = nullptr;
};

#endif // HINT_H
