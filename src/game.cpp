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
		if ((board.pieceIsAlive(tr, tc) == false) || ((board.pieceIsAlive(tr, tc) == true) && (board.pieceColor(tr, tc) != currentTurn)))
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

bool Game::checkMouseCoord3(Board& board)
{
	Vector2 mouse2 = GetMousePosition();
	if (CheckCollisionPointRec(mouse2, { 350,200,100,400 }))
	{
		int tc = (int)mouse2.x/100;
		int tr = (int)mouse2.y/100;
		
		if(tr==2 || tr==3 || tr==4 || tr==5)
		{
			pr = tr-2;
			pc = tc;

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

		if (currentTurn == PieceColor::DARK)
		{
			opp = PieceColor::LIGHT;
		}
		else
		{
			opp = PieceColor::DARK;
		}

		if (currentState == STATE::SELECT_PIECE) {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (checkMouseCoord(board)==true)
				{
					currentState = STATE::SELECT_DESTINATION;
				}
				else
				{
					currentState = STATE::SELECT_PIECE;
				}
			}
		}
		else if (currentState == STATE::SELECT_DESTINATION)
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (checkMouseCoord2(board)==true)
				{
					if (board.validateNewPosition(nr, nc, r, c) == true)
					{	
						if (board.pieceIsAlive(nr, nc))
						{
							capturedPiece = Piece(board.pieceType(nr, nc), board.pieceColor(nr, nc), board.pieceTex(nr, nc), true);
						}
						else
						{
							capturedPiece = Piece(board.pieceType(r, c), board.pieceColor(r, c), board.pieceTex(r, c), false);
						}
						board.updatePiecePosition(nr, nc, r, c);

						if (board.checkForCheck(currentTurn))
						{
							board.updatePiecePosition(r, c, nr, nc);
							if (capturedPiece.isAliveFun())
							{
								board.addNewPiece(nr, nc, capturedPiece);
							}
							currentState = STATE::SELECT_PIECE;
							continue;
						}

						if (board.checkForCheck(opp))
						{
							check = true;
						}
						else
						{
							check = false;
						}

						// Function call to check stalemate - (Incomplete)
						/*if (!check)
						{
							if (board.checkForStaleMate(opp))
							{
								currentState = STATE::GAME_OVER;
								continue;
							}
						}*/

						if (check == true)
						{
							if (board.checkForCheckMate(opp))
							{
								currentState = STATE::GAME_OVER;
								continue;
							}
						}

						if (board.promoteFlagCheck())
						{
							currentState = STATE::PAWN_PROMOTION;
							continue;
						}


						currentTurn = opp;
						currentState = STATE::SELECT_PIECE;

					}
					else
					{
						currentState = STATE::SELECT_PIECE;
					}
				}
				else
				{
					currentState = STATE::SELECT_PIECE;
				}
			}
		}
		else if (currentState == STATE::PAWN_PROMOTION)
		{
			board.promote(r, c, currentTurn);
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (checkMouseCoord3(board) == true)
				{
					board.updatePiecePosition2(nr, nc, pr, currentTurn);
					if (currentTurn == PieceColor::DARK)
					{
						currentTurn = PieceColor::LIGHT;
					}
					else if(currentTurn == PieceColor::LIGHT)
					{
						currentTurn = PieceColor::DARK;
					}
					currentState = STATE::SELECT_PIECE;
					board.clearPromoteFlag();
				}
			}
		}
		else if (currentState == STATE::GAME_OVER)
		{
			if (currentTurn == PieceColor::DARK)
			{
				DrawRectangle(150, 300, 500, 100, Color{ 255, 255, 255, 150 });
				DrawText("Black Won", 150, 300, 100, BLACK);
			}
			else
			{
				DrawRectangle(150, 300, 500, 100, Color{ 0, 0, 0, 150 });
				DrawText("White Won", 150, 300, 100, WHITE);
			}
			
			currentState = STATE::GAME_OVER;
		}
		EndDrawing();
	}
	endgame:
	CloseWindow();
}

void Game::start() {
	
}