#ifndef HINTVERTICAL_H
#define HINTVERTICAL_H

#include "hint.h"

class HintVertical: public Hint
{
public:
	HintVertical();
	~HintVertical();

	bool	applyToField();
};

#endif // HINTVERTICAL_H
