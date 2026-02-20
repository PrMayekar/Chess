#pragma once
#include <raylib.h>
#include "resource_dir.h"
#include "piece.h"
#include "board.h"
#include "utils.h"

class Game
{
protected:
	STATE currentState = STATE::SELECT_PIECE;
	bool flag = false;
	int r;
	int c;
	int nr;
	int nc;
	int pr;
	int pc;
	bool nextFlag = false;
	Piece selectPiece;
	Piece capturedPiece;
	PieceColor currentTurn;
	bool check = false;
	bool choosePromotion = false;

public:
	Game();
	bool checkMouseCoord3(Board& board);
	bool checkMouseCoord2(Board& board);
	bool checkMouseCoord(Board& board);
	void initialize();
	void start();
};
