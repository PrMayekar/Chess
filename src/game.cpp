#include <raylib.h>
#include <iostream>
#include "resource_dir.h"
#include "game.h"
#include "utils.h"

Game::Game(){}


bool Game::checkMouseCoord(Board& board)
{
		Vector2 mouse = GetMousePosition();
		if (CheckCollisionPointRec(mouse, { 0,0,800,800 }))
		{
			int tc = (int)mouse.x / 100;
			int tr = (int)mouse.y / 100;
			if (board.pieceIsAlive(tr, tc) == true && board.pieceColor(tr, tc)==currentTurn)
			{
				r = tr; 
				c = tc; 

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
}

bool Game::checkMouseCoord2(Board& board)
{
	Vector2 mouse2 = GetMousePosition();
	if (CheckCollisionPointRec(mouse2, { 0,0,800,800 }))
	{
		int tc = (int)mouse2.x / 100;
		int tr = (int)mouse2.y / 100;
		if (board.pieceIsAlive(tr, tc) == false)
		{
			nr = tr;
			nc = tc; 
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}



void Game::initialize()
{

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 800, "Chess");

	Board board;
	currentTurn = PieceColor::LIGHT;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		board.drawBoard();
		board.drawPieces();

		if (currentState == STATE::SELECT_PIECE) {

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (checkMouseCoord(board)==true)
				{
					currentState = STATE::SELECT_DESTINATION;
				}
			}

		}
		else if (currentState == STATE::SELECT_DESTINATION)
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (checkMouseCoord2(board)==true)
				{
					board.updatePiecePosition(nr, nc, r, c);
					if (currentTurn == PieceColor::LIGHT)
					{
						currentTurn = PieceColor::DARK;
					}
					else
					{
						currentTurn = PieceColor::LIGHT;
					}
					currentState = STATE::SELECT_PIECE;
				}
			}
		}

		EndDrawing();
	}
	CloseWindow();
}

void Game::start() {
	
}