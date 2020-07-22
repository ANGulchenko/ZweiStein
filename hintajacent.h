#ifndef HINTAJACENT_H
#define HINTAJACENT_H

#include "hint.h"

class HintAjacent: public Hint
{
public:
	HintAjacent();
	~HintAjacent();

	bool	applyToField();
};

#endif // HINTAJACENT_H
