#pragma once
#include <raylib.h>
#include "resource_dir.h"
#include "piece.h"
#include "board.h"
#include "utils.h"

class Menu
{
protected:
	bool gameStarted = false;
public:
	Menu();
	void displayMenu();
	void setGameStarted();
	void clearGameStarted();
	bool getGameStarted();
};