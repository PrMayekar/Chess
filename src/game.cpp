#include <raylib.h>
#include <iostream>
#include "resource_dir.h"
#include "game.h"
#include "utils.h"
#include "mainMenu.h"
#include "fstream"
#include <cstdio>
#include "stockfish.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

	std::ofstream gamelog("gamelog.txt");

	int kingX = -1;
	int kingY = -1;

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
					board.highlightTile(r, c);
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
							board.unHightlightTile(r, c);
							board.clearCheckFlag();
							currentState = STATE::SELECT_PIECE;
							continue;
						}

						if (board.checkForCheck(opp))
						{
							check = true;
							board.setCheckFlag();
						}
						else
						{
							check = false;
							board.clearCheckFlag();
						}

						if (!check)
						{
							if (board.checkForStaleMate(opp))
							{
								currentState = STATE::GAME_OVER;
								stalemate = true;
								continue;
							}

							if (board.promoteFlagCheck())
							{
								currentState = STATE::PAWN_PROMOTION;
								continue;
							}
						}

						if (check == true)
						{
							if (board.checkForCheckMate(opp))
							{
								currentState = STATE::GAME_OVER;
								continue;
							}
						}

						

						board.unHightlightTile(r, c);

						if (board.getEnPassantFlag()==2)
						{
							board.decEnPassant();
						}
						else if (board.getEnPassantFlag() == 1)
						{
							board.decEnPassant();
						}

						currentTurn = opp;
						currentState = STATE::SELECT_PIECE;

						gamelog << (char)(c + 97) << abs(r - 8) << (char)(nc + 97) << abs(nr - 8) << std::ends;

					}
					else
					{
						board.unHightlightTile(r, c);
						currentState = STATE::SELECT_PIECE;
					}
				}
				else
				{
					board.unHightlightTile(r, c);
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

					char promotedPiece = 'a';
					if (board.pieceType(nr, nc) == PieceType::ROOK)
						promotedPiece = 'r';
					else if(board.pieceType(nr, nc) == PieceType::KNIGHT)
						promotedPiece = 'n';
					else if (board.pieceType(nr, nc) == PieceType::BISHOP)
						promotedPiece = 'b';
					else if (board.pieceType(nr, nc) == PieceType::QUEEN)
						promotedPiece = 'q';

					gamelog << (char)(c + 97) << abs(r - 8) << (char)(nc + 97) << abs(nr - 8) << promotedPiece << std::ends;
					board.clearPromoteFlag();
				}
			}
			board.unHightlightTile(r, c);
		}
		else if (currentState == STATE::GAME_OVER)
		{

			if (stalemate)
			{
				DrawRectangle(150, 300, 500, 100, Color{ 255, 255, 255, 150 });
				DrawText("Stalemate", 150, 300, 100, BLACK);
			}
			else 
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
			}
			if (IsKeyPressed(KEY_SPACE))
			{
				gamelog.close();
				EndDrawing();
				CloseWindow();
				Menu menu;
				menu.displayMenu();
			}
			currentState = STATE::GAME_OVER;
		}
		EndDrawing();
	}
	endgame:
	gamelog.close();
	CloseWindow();
}

void Game::start() {
	
}


void Game::vsComAsWhite()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 800, "Chess");

	std::ofstream gamelog("gamelog.txt");
	
	Stockfish stf;
	if (!stf.initialize())
	{
		goto endgame;
	}

	int kingX = -1;
	int kingY = -1;

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

		if (currentTurn == PieceColor::LIGHT)
		{

			if (currentState == STATE::SELECT_PIECE) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					if (checkMouseCoord(board) == true)
					{
						currentState = STATE::SELECT_DESTINATION;
						board.highlightTile(r, c);
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
					if (checkMouseCoord2(board) == true)
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
								board.unHightlightTile(r, c);
								board.clearCheckFlag();
								currentState = STATE::SELECT_PIECE;
								continue;
							}

							if (board.checkForCheck(opp))
							{
								check = true;
								board.setCheckFlag();
							}
							else
							{
								check = false;
								board.clearCheckFlag();
							}

							if (!check)
							{
								if (board.checkForStaleMate(opp))
								{
									currentState = STATE::GAME_OVER;
									stalemate = true;
									continue;
								}

								if (board.promoteFlagCheck())
								{
									currentState = STATE::PAWN_PROMOTION;
									continue;
								}
							}

							if (check == true)
							{
								if (board.checkForCheckMate(opp))
								{
									currentState = STATE::GAME_OVER;
									continue;
								}
							}

							board.unHightlightTile(r, c);

							if (board.getEnPassantFlag() == 2)
							{
								board.decEnPassant();
							}
							else if (board.getEnPassantFlag() == 1)
							{
								board.decEnPassant();
							}

							currentTurn = opp;
							currentState = STATE::SELECT_PIECE;

							gamelog << (char)(c + 97) << abs(r - 8) << (char)(nc + 97) << abs(nr - 8) << std::ends;
							char move[6] = { (char)(c + 97) ,(char)(abs(r - 8) + 48) ,(char)(nc + 97), (char)(abs(nr - 8) + 48), '\0' };
							if ((strlen(stf.positionCommand) + strlen(move) + 2) < BUFSIZE)
							{
								strcat(stf.positionCommand, " ");
								strcat(stf.positionCommand, move);
							}
							else
							{
								goto endgame;
							}
						}
						else
						{
							board.unHightlightTile(r, c);
							currentState = STATE::SELECT_PIECE;
						}
					}
					else
					{
						board.unHightlightTile(r, c);
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
						else if (currentTurn == PieceColor::LIGHT)
						{
							currentTurn = PieceColor::DARK;
						}
						currentState = STATE::SELECT_PIECE;

						char promotedPiece = 'a';
						if (board.pieceType(nr, nc) == PieceType::ROOK)
							promotedPiece = 'r';
						else if (board.pieceType(nr, nc) == PieceType::KNIGHT)
							promotedPiece = 'n';
						else if (board.pieceType(nr, nc) == PieceType::BISHOP)
							promotedPiece = 'b';
						else if (board.pieceType(nr, nc) == PieceType::QUEEN)
							promotedPiece = 'q';

						gamelog << (char)(c + 97) << abs(r - 8) << (char)(nc + 97) << abs(nr - 8) << promotedPiece << std::ends;
						char move[6] = { (char)(c + 97) ,(char)(abs(r - 8) + 48) ,(char)(nc + 97), (char)(abs(nr - 8) + 48),promotedPiece , '\0' };
						board.clearPromoteFlag();


						if ((strlen(stf.positionCommand) + strlen(move) + 2) < BUFSIZE)
						{
							strcat(stf.positionCommand, " ");
							strcat(stf.positionCommand, move);
						}
						else
						{
							goto endgame;
						}
					}
				}
				board.unHightlightTile(r, c);
			}
			else if (currentState == STATE::GAME_OVER)
			{

				if (stalemate)
				{
					DrawRectangle(150, 300, 500, 100, Color{ 255, 255, 255, 150 });
					DrawText("Stalemate", 150, 300, 100, BLACK);
				}
				else
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
				}
				if (IsKeyPressed(KEY_SPACE))
				{
					gamelog.close();
					EndDrawing();
					CloseWindow();
					Menu menu;
					menu.displayMenu();
				}
				currentState = STATE::GAME_OVER;
			}
		}

		else if (currentTurn == PieceColor::DARK)
		{
			if (!stf.requestBestMove())
			{
				goto endgame;
			}

			char move[6] = { 0 };
			stf.getBestMove();
			
			if (strlen(stf.movemove) == 4)
			{
				c = stf.movemove[0] - 'a';
				r = 8 - (stf.movemove[1] - '0');
				nc = stf.movemove[2] - 'a';
				nr = 8 - (stf.movemove[3] - '0');

				gamelog << "\n Computer Move: " << stf.movemove << "\n";

				if (board.validateNewPosition(nr, nc, r, c) == true)
				{
					board.updatePiecePosition(nr, nc, r, c);
				}
				else
				{
					goto endgame;
				}
			}
			else if (strlen(stf.movemove) == 5)
			{
				c = stf.movemove[0] - 'a';
				r = 8 - (stf.movemove[1] - '0');
				nc = stf.movemove[2] - 'a';
				nr = 8 - (stf.movemove[3] - '0');
				char promotedPiece = stf.movemove[4];
				
				board.updatePiecePosition(nr, nc, r, c);

				gamelog << "\n Computer Move: " << stf.movemove << "\n";

				if(promotedPiece == 'r')
				{
					board.updatePiecePosition2(nr, nc, 0, PieceColor::DARK);
				}
				else if (promotedPiece == 'n')
				{
					board.updatePiecePosition2(nr, nc, 1, PieceColor::DARK);
				}
				else if (promotedPiece == 'b')
				{
					board.updatePiecePosition2(nr, nc, 2, PieceColor::DARK);
				}
				else if (promotedPiece == 'q')
				{
					board.updatePiecePosition2(nr, nc, 3, PieceColor::DARK);
				}
			}
			else
			{
				goto endgame;
			}
			
			if ((strlen(stf.positionCommand) + strlen(stf.movemove) + 2) < BUFSIZE)
			{
				strcat(stf.positionCommand, " ");
				strcat(stf.positionCommand, stf.movemove);
			}
			else
			{
				goto endgame;
			}

			if (board.checkForCheck(PieceColor::LIGHT))
			{
				check = true;
				board.setCheckFlag();
			}
			else
			{
				check = false;
				board.clearCheckFlag();
			}

			if (!check)
			{
				if (board.checkForStaleMate(PieceColor::LIGHT))
				{
					currentState = STATE::GAME_OVER;
					stalemate = true;
					continue;
				}
			}

			if (check == true)
			{
				if (board.checkForCheckMate(PieceColor::LIGHT))
				{
					currentState = STATE::GAME_OVER;
					continue;
				}
				check = false;
			}
			
			currentTurn = PieceColor::LIGHT;
			currentState = STATE::SELECT_PIECE;
		}

		EndDrawing();
	}
endgame:
	stf.closeHandles();
	gamelog.close();
	CloseWindow();
}





void Game::vsComAsBlack()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 800, "Chess");

	std::ofstream gamelog("gamelog.txt");

	Stockfish stf;
	if (!stf.initialize())
	{
		goto endgame;
	}

	int kingX = -1;
	int kingY = -1;

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

		if (currentTurn == PieceColor::DARK)
		{
			if (currentState == STATE::SELECT_PIECE) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					if (checkMouseCoord(board) == true)
					{
						currentState = STATE::SELECT_DESTINATION;
						board.highlightTile(r, c);
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
					if (checkMouseCoord2(board) == true)
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
								board.unHightlightTile(r, c);
								board.clearCheckFlag();
								currentState = STATE::SELECT_PIECE;
								continue;
							}

							if (board.checkForCheck(opp))
							{
								check = true;
								board.setCheckFlag();
							}
							else
							{
								check = false;
								board.clearCheckFlag();
							}

							if (!check)
							{
								if (board.checkForStaleMate(opp))
								{
									currentState = STATE::GAME_OVER;
									stalemate = true;
									continue;
								}

								if (board.promoteFlagCheck())
								{
									currentState = STATE::PAWN_PROMOTION;
									continue;
								}
							}

							if (check == true)
							{
								if (board.checkForCheckMate(opp))
								{
									currentState = STATE::GAME_OVER;
									continue;
								}
							}

							board.unHightlightTile(r, c);

							if (board.getEnPassantFlag() == 2)
							{
								board.decEnPassant();
							}
							else if (board.getEnPassantFlag() == 1)
							{
								board.decEnPassant();
							}

							currentTurn = opp;
							currentState = STATE::SELECT_PIECE;

							gamelog << (char)(c + 97) << abs(r - 8) << (char)(nc + 97) << abs(nr - 8) << std::ends;
							char move[6] = { (char)(c + 97) ,(char)(abs(r - 8) + 48) ,(char)(nc + 97), (char)(abs(nr - 8) + 48), '\0' };
							if ((strlen(stf.positionCommand) + strlen(move) + 2) < BUFSIZE)
							{
								strcat(stf.positionCommand, " ");
								strcat(stf.positionCommand, move);
							}
							else
							{
								goto endgame;
							}
						}
						else
						{
							board.unHightlightTile(r, c);
							currentState = STATE::SELECT_PIECE;
						}
					}
					else
					{
						board.unHightlightTile(r, c);
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
						else if (currentTurn == PieceColor::LIGHT)
						{
							currentTurn = PieceColor::DARK;
						}
						currentState = STATE::SELECT_PIECE;

						char promotedPiece = 'a';
						if (board.pieceType(nr, nc) == PieceType::ROOK)
							promotedPiece = 'r';
						else if (board.pieceType(nr, nc) == PieceType::KNIGHT)
							promotedPiece = 'n';
						else if (board.pieceType(nr, nc) == PieceType::BISHOP)
							promotedPiece = 'b';
						else if (board.pieceType(nr, nc) == PieceType::QUEEN)
							promotedPiece = 'q';

						gamelog << (char)(c + 97) << abs(r - 8) << (char)(nc + 97) << abs(nr - 8) << promotedPiece << std::ends;
						char move[6] = { (char)(c + 97) ,(char)(abs(r - 8) + 48) ,(char)(nc + 97), (char)(abs(nr - 8) + 48),promotedPiece , '\0' };
						board.clearPromoteFlag();


						if ((strlen(stf.positionCommand) + strlen(move) + 2) < BUFSIZE)
						{
							strcat(stf.positionCommand, " ");
							strcat(stf.positionCommand, move);
						}
						else
						{
							goto endgame;
						}
					}
				}
				board.unHightlightTile(r, c);
			}
			else if (currentState == STATE::GAME_OVER)
			{

				if (stalemate)
				{
					DrawRectangle(150, 300, 500, 100, Color{ 255, 255, 255, 150 });
					DrawText("Stalemate", 150, 300, 100, BLACK);
				}
				else
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
				}
				if (IsKeyPressed(KEY_SPACE))
				{
					gamelog.close();
					EndDrawing();
					CloseWindow();
					Menu menu;
					menu.displayMenu();
				}
				currentState = STATE::GAME_OVER;
			}
		}

		else if (currentTurn == PieceColor::LIGHT)
		{
			if (!stf.requestBestMove())
			{
				goto endgame;
			}

			char move[6] = { 0 };
			stf.getBestMove();

			if (strlen(stf.movemove) == 4)
			{
				c = stf.movemove[0] - 'a';
				r = 8 - (stf.movemove[1] - '0');
				nc = stf.movemove[2] - 'a';
				nr = 8 - (stf.movemove[3] - '0');

				gamelog << "\n Computer Move: " << stf.movemove << "\n";

				if (board.validateNewPosition(nr, nc, r, c) == true)
				{
					board.updatePiecePosition(nr, nc, r, c);
				}
				else
				{
					goto endgame;
				}
			}
			else if (strlen(stf.movemove) == 5)
			{
				c = stf.movemove[0] - 'a';
				r = 8 - (stf.movemove[1] - '0');
				nc = stf.movemove[2] - 'a';
				nr = 8 - (stf.movemove[3] - '0');
				char promotedPiece = stf.movemove[4];

				board.updatePiecePosition(nr, nc, r, c);

				gamelog << "\n Computer Move: " << stf.movemove << "\n";

				if (promotedPiece == 'r')
				{
					board.updatePiecePosition2(nr, nc, 0, PieceColor::LIGHT);
				}
				else if (promotedPiece == 'n')
				{
					board.updatePiecePosition2(nr, nc, 1, PieceColor::LIGHT);
				}
				else if (promotedPiece == 'b')
				{
					board.updatePiecePosition2(nr, nc, 2, PieceColor::LIGHT);
				}
				else if (promotedPiece == 'q')
				{
					board.updatePiecePosition2(nr, nc, 3, PieceColor::LIGHT);
				}
			}
			else
			{
				goto endgame;
			}

			if ((strlen(stf.positionCommand) + strlen(stf.movemove) + 2) < BUFSIZE)
			{
				strcat(stf.positionCommand, " ");
				strcat(stf.positionCommand, stf.movemove);
			}
			else
			{
				goto endgame;
			}

			if (board.checkForCheck(PieceColor::DARK))
			{
				check = true;
				board.setCheckFlag();
			}
			else
			{
				check = false;
				board.clearCheckFlag();
			}

			if (!check)
			{
				if (board.checkForStaleMate(PieceColor::DARK))
				{
					currentState = STATE::GAME_OVER;
					stalemate = true;
					continue;
				}
			}

			if (check == true)
			{
				if (board.checkForCheckMate(PieceColor::DARK))
				{
					currentState = STATE::GAME_OVER;
					continue;
				}
				check = false;
			}

			currentTurn = PieceColor::DARK;
			currentState = STATE::SELECT_PIECE;
		}
		EndDrawing();
	}
endgame:
	stf.closeHandles();
	gamelog.close();
	CloseWindow();
}