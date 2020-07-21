#ifndef HINT_H
#define HINT_H

#include <utility>
#include <random>
#include <algorithm>

#include "field.h"


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

	std::random_device random_device;
};

#endif // HINT_H
