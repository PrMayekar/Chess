#include <raylib.h>
#include "resource_dir.h"
#include <iostream>
#include "game.h"

int main()
{
	Game game;
	game.initialize();
	std::cin.get();
}