#pragma once
#include "tile.h"
#include "piece.h"
#include "utils.h"
#include <raylib.h>
#include "resource_dir.h"
#define TILES 8
#define TILESIZE 100

class Board
{
protected:
	bool check = false;
	bool promoteFlag = false;
	bool darkCastleFlag = true;
	bool lightCastleFlag = true;
	int enPassant = 0;
	int enPassantRow = -1;
	int enPassantCol = -1;
	Piece pieces[TILES][TILES];
	Tile board[TILES][TILES];
	Piece lightPromotion[4];
	Piece darkPromotion[4];
	Tile promotionTiles[4];

public:
	Board();
	void drawBoard();
	void drawPieces();
	void addNewPiece(int r, int c, Piece piece);
	bool pieceIsAlive(int r, int c);
	Texture2D pieceTex(int r, int c) const;
	PieceType pieceType(int r, int c) const;
	PieceColor pieceColor(int r, int c) const;
	void updatePiecePosition(int r, int c, int or, int oc);
	void updatePiecePosition2(int r, int c, int nr, PieceColor col);
	bool validateNewPosition(int r, int c, int or , int oc);
	bool checkForCheck(PieceColor col);
	bool checkChecker(Piece p,int or,int oc,int i, int j, PieceColor opp);
	void promote(int r, int c, PieceColor col);
	bool promoteFlagCheck();
	void setPromoteFlag();
	void clearPromoteFlag();
	bool checkForCheckMate(PieceColor col);
	bool checkForStaleMate(PieceColor col);
	bool staleChecker(int pr, int pc, Piece p);
	void highlightTile(int i, int j);
	void unHightlightTile(int j, int i);
	Vector2 findKingPosition(PieceColor col);
	bool getDarkCastleFlag();
	void clearDarkCastleFlag();
	bool getLightCastleFlag();
	void clearLightCastleFlag();
	void setLightCastleFlag();
	void setDarkCastleFlag();
	bool getCheckFlag();
	void setCheckFlag();
	void clearCheckFlag();
	int getEnPassantFlag();
	void setEnPassantFlag();
	void clearEnPassantFlag();
	void decEnPassant();
	void updateBlackBotCastle(int r, int c, int or , int oc);
};
