#include "board.h"

Board::Board()
{
	for (int i = 0; i < TILES; i++)
	{
		for (int j = 0; j < TILES; j++)
		{
			Rectangle rec = { i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE };
			Color color = ((i + j) % 2 == 0) ? GRAY : DARKGRAY;

			board[i][j] = Tile(rec, color);
			pieces[i][j] = Piece();
		}
	}

	Texture2D darkPawn = LoadTexture("assets/Chess_pdt60.png");
	Texture2D lightPawn = LoadTexture("assets/Chess_plt60.png");
	Texture2D lightRook = LoadTexture("assets/Chess_rlt60.png");
	Texture2D darkRook = LoadTexture("assets/Chess_rdt60.png");
	Texture2D lightBishop = LoadTexture("assets/Chess_blt60.png");
	Texture2D darkBishop = LoadTexture("assets/Chess_bdt60.png");
	Texture2D lightKnight = LoadTexture("assets/Chess_nlt60.png");
	Texture2D darkKnight = LoadTexture("assets/Chess_ndt60.png");
	Texture2D lightQueen = LoadTexture("assets/Chess_qlt60.png");
	Texture2D darkQueen = LoadTexture("assets/Chess_qdt60.png");
	Texture2D lightKing = LoadTexture("assets/Chess_klt60.png");
	Texture2D darkKing = LoadTexture("assets/Chess_kdt60.png");


	for (int i = 0; i < TILES; i++)
	{
		pieces[1][i] = Piece(PAWN, DARK, darkPawn, true);
	}

	for (int i = 0; i < TILES; i++)
	{
		pieces[6][i] = Piece(PAWN, LIGHT, lightPawn, true);
	}

	pieces[0][0] = Piece(ROOK, DARK, darkRook, true);
	pieces[0][7] = Piece(ROOK, DARK, darkRook, true);

	pieces[0][1] = Piece(KNIGHT, DARK, darkKnight, true);
	pieces[0][6] = Piece(KNIGHT, DARK, darkKnight, true);

	pieces[0][2] = Piece(BISHOP, DARK, darkBishop, true);
	pieces[0][5] = Piece(BISHOP, DARK, darkBishop, true);

	pieces[0][3] = Piece(QUEEN, DARK, darkQueen, true);
	pieces[0][4] = Piece(KING, DARK, darkKing, true);



	pieces[7][0] = Piece(ROOK, LIGHT, lightRook, true);
	pieces[7][7] = Piece(ROOK, LIGHT, lightRook, true);

	pieces[7][1] = Piece(KNIGHT, LIGHT, lightKnight, true);
	pieces[7][6] = Piece(KNIGHT, LIGHT, lightKnight, true);

	pieces[7][2] = Piece(BISHOP, LIGHT, lightBishop, true);
	pieces[7][5] = Piece(BISHOP, LIGHT, lightBishop, true);

	pieces[7][3] = Piece(QUEEN, LIGHT, lightQueen, true);
	pieces[7][4] = Piece(KING, LIGHT, lightKing, true);

}

void Board::drawPieces()
{
	for (int i = 0; i < TILES; i++)
	{
		for (int j = 0; j < TILES; j++)
		{
			if (pieces[i][j].isAliveFun() == true)
			{
				pieces[i][j].drawPiece(i, j);
			}
		}
	}
}



void Board::drawBoard()
{
	for (int i = 0; i < TILES; i++)
	{
		for (int j = 0; j < TILES; j++)
		{
			board[i][j].drawTile();
		}
	}
}

bool Board::pieceIsAlive(int r,int c)
{
	if (pieces[r][c].isAliveFun() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}


Texture2D Board::pieceTex(int r, int c) const
{
	return pieces[r][c].m_texFun();
}

PieceType Board::pieceType(int r, int c) const
{
	return pieces[r][c].m_typeFun();
}

PieceColor Board::pieceColor(int r, int c) const
{
	return pieces[r][c].m_colorFun();
}

void Board::updatePiecePosition(int r, int c, int or, int oc)
{
	pieces[r][c] = pieces[or][oc];
	pieces[or][oc] = Piece();
}