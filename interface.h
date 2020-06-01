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
	std::string	printCellRow(int row);
	std::string	printHint(size_t index);
	std::string	printHintRow(size_t row);
	void		printCommandError();
	void		printWin();
	void		printLose();

private:
	Field* _field;
	std::array<std::array<std::string, 6>, 6> _literals;
	std::map<HintType, std::string> _hint_literals;
	std::vector<bool>_hints_visibility;
};

#endif // INTERFACE_H
