#include "game.h"

Game::Game()
	: field (Field::Instance())
	, hints (Hints::Instance())
	, gameStatus(GameStatus::gameContinues)
{

}

Game::~Game()
{

}

void	Game::initPuzzle()
{
	hints.createFullSetOfHints();
	field.resetSubValues();
}

void	Game::start()
{
	//main cycle: print game| read and parse commands | use commands
	int ch;
	interface.printGame();
	while (gameStatus == GameStatus::gameContinues)
	{
		interface.printGame();
		ch = getch();
		command.parse(ch);

		switch (command.type)
		{
			case CommandType::error:
			{
			}break;
			case CommandType::quit:
			{
				gameStatus = GameStatus::gameLost;
			}break;
			case CommandType::move_up:
			{
				interface.cursor.moveUp();
			}break;
			case CommandType::move_down:
			{
				interface.cursor.moveDown();
			}break;
			case CommandType::move_left:
			{
				interface.cursor.moveLeft();
			}break;
			case CommandType::move_right:
			{
				interface.cursor.moveRight();
			}break;
			case CommandType::claim:
			{
				bool res = field.tryValue(interface.cursor.row, interface.cursor.col, interface.cursor.subvalue);
				if (!res)
				{
					gameStatus = GameStatus::gameLost;
				}
			}break;
			case CommandType::dismiss:
			{
				if (interface.cursor.zone == CursorZone::field)
				{
					bool res = field.switchOffSubValue(interface.cursor.row, interface.cursor.col, interface.cursor.subvalue);
					if (!res)
					{
						gameStatus = GameStatus::gameLost;
					}
				}else
				if (interface.cursor.zone == CursorZone::hints)
				{
					size_t index = interface.cursor.getHintNo();
					interface.changeVisibilityOfHint(index);
				}
			}break;
			case CommandType::help:
			{
				interface.printHelp();
				getch();
			}break;
			case CommandType::about:
			{
				interface.printAbout();
				getch();
			}break;
			case CommandType::toggle_autohide:
			{
				interface.switchHintAutoHide();
			}break;
		}

		if (field.isWin())
		{
			gameStatus = GameStatus::gameWon;
		}
	}

	switch (gameStatus)
	{
		case GameStatus::gameContinues:
		{
			// Impossible situation
		}break;
		case GameStatus::gameWon:
		{
			interface.printWin();
			getch();
		}break;
		case GameStatus::gameLost:
		{
			interface.printLose();
			getch();
		}break;
	}

}
