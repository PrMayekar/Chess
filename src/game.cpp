#include <raylib.h>
#include <iostream>
#include "resource_dir.h"
#include "game.h"

Game::Game() {}

void Game::initialize()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1600, 800, "Chess");

	Board board;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		board.drawBoard();
		board.drawPieces();


		EndDrawing();
	}
	CloseWindow();
}

void Game::start() {}