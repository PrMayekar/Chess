#include <raylib.h>
#include "resource_dir.h"
#include <iostream>
#include "mainMenu.h"
#include "game.h"

int main()
{
	/*Game game;
	game.initialize();*/
	Menu menu;
	menu.displayMenu();
	std::cin.get();
}