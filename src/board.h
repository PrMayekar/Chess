#pragma once
#include "tile.h"
#include "piece.h"
#include "utils.h"
#define TILES 8
#define TILESIZE 100

class Board
{
protected:
	Piece pieces[TILES][TILES];
	Tile board[TILES][TILES];

public:
	Board();
	void drawBoard();
	void drawPieces();
	bool pieceIsAlive(int r, int c);
	Texture2D pieceTex(int r, int c) const;
	PieceType pieceType(int r, int c) const;
	PieceColor pieceColor(int r, int c) const;
	void updatePiecePosition(int r, int c, int or, int oc);
	bool validateNewPosition(int r, int c, int or , int oc);
};
