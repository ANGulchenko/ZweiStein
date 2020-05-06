#ifndef HINT_H
#define HINT_H

#include <utility>

#include "field.h"


enum class HintType {vertical, ajacent};

class Hint
{
public:
	Hint(Field* field);
	virtual ~Hint();

	bool	virtual applyToField() = 0;

	HintType type;
	std::pair<int, int> first_literal;	// row-index (like in Interface::_literals)
	std::pair<int, int> second_literal;
	std::pair<int, int> third_literal;

	Field*	field;

};

class HintVertical: public Hint
{
public:
	HintVertical(Field* field);
	~HintVertical();

	bool	applyToField();
};

class HintAjacent: public Hint
{
public:
	HintAjacent(Field* field);
	~HintAjacent();

	bool	applyToField();
};

#endif // HINT_H
