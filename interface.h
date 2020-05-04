#ifndef INTERFACE_H
#define INTERFACE_H

#include "field.h"


class Interface
{
public:
	Interface(Field* field);
	void		printGame();
	std::string	printCell(int row, int col);
	std::string	printRow(int row);
	void		printCommandError();

private:
	Field* _field;
	std::array<std::array<std::string, 6>, 6> _literals;
};

#endif // INTERFACE_H
