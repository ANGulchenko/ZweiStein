#ifndef INTERFACE_H
#define INTERFACE_H

#include "field.h"
#include "hints.h"


class Interface
{
public:
	Interface(Field* field);
	void		printGame();
	std::string	printCell(int row, int col);
	std::string	printRow(int row);
	void		printCommandError();
	void		printHints();
	void		printWin();
	void		printLose();

private:
	Field* _field;
	std::array<std::array<std::string, 6>, 6> _literals;
	std::map<HintType, std::string> _hint_literals;
};

#endif // INTERFACE_H
