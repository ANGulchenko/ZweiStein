#include <iostream>

#include "hints.h"
#include "Randomizer2000.h"


Hints::Hints()
{
	initHintsProbability({
							 {HintType::vertical, 10},
							 {HintType::ajacent, 30},
							 {HintType::leftRight, 60},
							 {HintType::threeAjacent, 20}
						 });
}

void	Hints::initHintsProbability(const std::map<HintType, int>& new_probabilities)
{
	hintProbabilities.clear();
	hintProbabilityDiapasones.clear();
	for (auto& [type, value]: new_probabilities)
	{
		hintProbabilities[type] = value;
	}
	int limit = 0;
	for (auto& [type, value]: hintProbabilities)
	{
		if (value <= 0) value = 1; // Zeroes can make making sat of Hints impossible;
		limit += value;
		hintProbabilityDiapasones[limit] = type;
	}
}

Hints::~Hints()
{
	for (auto& h: hints)
	{
		delete h;
	}
}

Hint*	Hints::getNewHint(HintType hintType)
{
	HintType type;
	if (hintType != HintType::empty)
	{
		type = hintType;
	}else
	{
		int probabilityDiapasoneUpperLimit = (--hintProbabilityDiapasones.end())->first;
		int random_int = Randomizer2000::Instance().random(0, probabilityDiapasoneUpperLimit);

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
		case HintType::leftRight :
		{
			return new HintLeftRight();
		} break;
		case HintType::threeAjacent :
		{
			return new HintThreeAjacent();
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
	do
	{
		if (hints.size() > 44)
		{
			for (auto& h: hints)
			{
				delete h;
			}
			hints.clear();
			field.resetSubValues();
		}
		createSingleSetOfHints();
		field.resetSubValues();
	}while (hints.size() > 44);
}

void	Hints::createSingleSetOfHints()
{
	Field& field = Field::Instance();
	Hint* temp_hint = nullptr;

	while (!field.isWin())
	{
		temp_hint = nullptr;
		while (temp_hint == nullptr)
		{
			temp_hint = getNewHint(HintType::empty);
			if (temp_hint == nullptr || temp_hint->type == HintType::empty)
			{
				delete temp_hint;
				temp_hint = nullptr;
			}
		}


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

	Randomizer2000::Instance().shuffle(hints);
}
