#ifndef HINTLEFTRIGHT_H
#define HINTLEFTRIGHT_H


#include "hint.h"

class HintLeftRight: public Hint
{
public:
	HintLeftRight();
	~HintLeftRight();

	bool	applyToField();
};

#endif // HINTLEFTRIGHT_H
