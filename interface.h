﻿#ifndef INTERFACE_H
#define INTERFACE_H

#include "field.h"
#include "hints.h"

enum class CursorZone { field, hints};

class Cursor
{
public:
	Cursor();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	size_t  getHintNo();

	void draw();

	size_t		row;
	size_t		col;
	size_t		subvalue;

	CursorZone	zone;
private:
	size_t		hintNo;
	size_t		hintRow;
	size_t		hintCol;
};

class Interface
{
public:
	Interface(Field* field);
	void		printGame();
	std::string	printCell(int row, int col);
	void		printAllCells();
	std::string	printHint(size_t index);
	void		changeVisibilityOfHint(size_t index);
	void		hideUselessHints();
	void		printAllHints();
	void		printCommandError();
	void		printWin();
	void		printLose();
	void		printHelp();
	void		switchHintAutoHide();

	Cursor cursor;

private:
	Field* _field;
	std::array<std::array<std::string, 6>, 6> _literals;
	std::map<HintType, std::string> _hint_literals;
	std::vector<bool>_hints_visibility;
	bool _hintAutoHide;

};

#endif // INTERFACE_H
