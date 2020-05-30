#ifndef HINTS_H
#define HINTS_H

#include <vector>
#include <map>
#include <random>

#include "hint.h"
#include "interface.h"

class Hints
{
public:
	static Hints& Instance()
	{
		static Hints theSingleInstance;
		return theSingleInstance;
	}
	~Hints();
	Hint*	getNewHint(HintType hintType);
	void	createFullSetOfHints();

	std::vector<Hint*> hints;
//	Interface* i_face;
private:
		Hints();
		Hints(const Hints& root) = delete;
		Hints& operator=(const Hints&) = delete;

		std::map<HintType, int> hintProbabilities;
		std::map<int, HintType> hintProbabilityDiapasones;
};

#endif // HINTS_H
