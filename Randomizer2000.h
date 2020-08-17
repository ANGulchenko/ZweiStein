// Author: A.N.Gulchenko
// License: MIT
// New versions: https://github.com/ANGulchenko/Randomizer2000

#ifndef RANDOMIZER2000_H
#define RANDOMIZER2000_H

#include <random>
#include <algorithm>

class Randomizer2000
{
public:
	static Randomizer2000& Instance()
	{
		static Randomizer2000 theSingleInstance;
		return theSingleInstance;
	}

	int		random(const int& x, const int& y)
	{
		std::uniform_int_distribution<> distr(x, y);
		return distr(veryrandomDevice);
	}

	template <class T>
	void	shuffle(T& container)
	{
		std::shuffle(container.begin(), container.end(), veryrandomDevice);
	}

private:
	Randomizer2000()
		: veryrandomDevice (randomDevice())
	{

	}
	Randomizer2000(const Randomizer2000& root) = delete;
	Randomizer2000& operator=(const Randomizer2000&) = delete;

	std::random_device randomDevice;
	std::mt19937 veryrandomDevice;

};

#endif
