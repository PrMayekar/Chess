#pragma once
#include "tile.h"
#include "piece.h"
#define TILES 8
#define TILESIZE 100

class Board : public Piece
{
protected:
	Piece pieces[TILES][TILES];
	Tile board[TILES][TILES];

public:
	Board();
	void drawBoard();
	void drawPieces();
};
