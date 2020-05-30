#include "hints.h"
#include <iostream>

Hints::Hints()
{
	hintProbabilities = {
							{HintType::vertical, 20},
							{HintType::ajacent, 80},
						};

	int limit = 0;
	for (auto i = hintProbabilities.begin(); i != hintProbabilities.end(); i++)
	{
		limit += i->second;
		hintProbabilityDiapasones[limit] = i->first;
	}
}

Hints::~Hints()
{

}

Hint*	Hints::getNewHint(HintType hintType)
{
	HintType type;
	if (hintType != HintType::empty)
	{
		type = hintType;
	}else
	{
		std::random_device randomDevice;
		std::mt19937 veryRandomDevice(randomDevice());

		int probabilityDiapasoneUpperLimit = (--hintProbabilityDiapasones.end())->first;
		std::uniform_int_distribution<int> dist(0, probabilityDiapasoneUpperLimit);

		int random_int = dist(veryRandomDevice);

		auto iD = hintProbabilityDiapasones.begin();
		while (iD->first < random_int)
		{
			iD++;
		}

		type = iD->second;
	}

	switch (type)
	{

		case HintType::ajacent :
		{
			return new HintAjacent();
		} break;
		case HintType::vertical :
		{
			return new HintVertical();
		} break;
		default:
		{
			// throw exception;
		}
	}

	return nullptr;
}

void	Hints::createFullSetOfHints()
{
	Field& field = Field::Instance();

	while (!field.isWin())
	{
		Hint* temp_hint = getNewHint(HintType::empty);
		bool apply_result = temp_hint->applyToField();
		if (apply_result)
		{
			hints.push_back(temp_hint);

			for (Hint* hint: hints)
			{
				hint->applyToField();
			}

//			i_face->printGame();
		}else
		{
			delete temp_hint;
		}
	}
}
