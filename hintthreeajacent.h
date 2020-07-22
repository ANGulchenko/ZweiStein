#ifndef HINTTHREEAJACENT_H
#define HINTTHREEAJACENT_H


#include "hint.h"

class HintThreeAjacent: public Hint
{
public:
	HintThreeAjacent();
	~HintThreeAjacent();

	bool	applyToField();
};

#endif // HINTTHREEAJACENT_H
