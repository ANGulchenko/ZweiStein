#include "hint.h"

Hint::Hint(Field *_field)
	: field(_field)

{


}

Hint::~Hint()
{

}

HintVertical::HintVertical(Field *field)
	: Hint(field)
{
	type = HintType::vertical;
}

HintVertical::~HintVertical()
{

}

bool HintVertical::applyToField()
{
	return false;
}

HintAjacent::HintAjacent(Field *field)
	: Hint(field)
{
	type = HintType::ajacent;
}

HintAjacent::~HintAjacent()
{

}

bool HintAjacent::applyToField()
{
	return false;
}

