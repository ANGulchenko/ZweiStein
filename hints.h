#ifndef HINTS_H
#define HINTS_H

#include <vector>

#include "hint.h"

class Hints
{
public:
	Hints();
	~Hints();
	Hint*	getNewHint();
	void	lastHintWasUseless();
	void	lastHintWasGood();

	Hint* tempHint;
	std::vector<Hint*> hints;
};

#endif // HINTS_H
