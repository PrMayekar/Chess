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
		pieces[1][i] = Piece(PieceType::PAWN, PieceColor::DARK, darkPawn, true);
	}

	for (int i = 0; i < TILES; i++)
	{
		pieces[6][i] = Piece(PieceType::PAWN, PieceColor::LIGHT, lightPawn, true);
	}

	pieces[0][0] = Piece(PieceType::ROOK, PieceColor::DARK, darkRook, true);
	pieces[0][7] = Piece(PieceType::ROOK, PieceColor::DARK, darkRook, true);

	pieces[0][1] = Piece(PieceType::KNIGHT, PieceColor::DARK, darkKnight, true);
	pieces[0][6] = Piece(PieceType::KNIGHT, PieceColor::DARK, darkKnight, true);

	pieces[0][2] = Piece(PieceType::BISHOP, PieceColor::DARK, darkBishop, true);
	pieces[0][5] = Piece(PieceType::BISHOP, PieceColor::DARK, darkBishop, true);

	pieces[0][3] = Piece(PieceType::QUEEN, PieceColor::DARK, darkQueen, true);
	pieces[0][4] = Piece(PieceType::KING, PieceColor::DARK, darkKing, true);



	pieces[7][0] = Piece(PieceType::ROOK, PieceColor::LIGHT, lightRook, true);
	pieces[7][7] = Piece(PieceType::ROOK, PieceColor::LIGHT, lightRook, true);

	pieces[7][1] = Piece(PieceType::KNIGHT, PieceColor::LIGHT, lightKnight, true);
	pieces[7][6] = Piece(PieceType::KNIGHT, PieceColor::LIGHT, lightKnight, true);

	pieces[7][2] = Piece(PieceType::BISHOP, PieceColor::LIGHT, lightBishop, true);
	pieces[7][5] = Piece(PieceType::BISHOP, PieceColor::LIGHT, lightBishop, true);

	pieces[7][3] = Piece(PieceType::QUEEN, PieceColor::LIGHT, lightQueen, true);
	pieces[7][4] = Piece(PieceType::KING, PieceColor::LIGHT, lightKing, true);

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

bool Board::validateNewPosition(int r, int c, int or , int oc)
{
	PieceType selectedPiece = pieceType(or , oc);

	if (selectedPiece == PieceType::ROOK)
	{
		if (r!=or && c != oc)
		{
			return false;
		}

		int stepR = 0;
		int stepC=0;
		
		if (r==or)
			stepC = (c > oc) ? 1 : -1;
		else
			stepR = (r > or ) ? 1 : -1;

		int i = or + stepR;
		int j = oc + stepC;

		while (i != r || j != c)
		{
			if (pieces[i][j].isAliveFun())
				return false;

			i += stepR;
			j += stepC;
		}
		return true;
	}
	else if (selectedPiece == PieceType::BISHOP)
	{
		if (abs(r - or ) != abs(c - oc))
			return false;

		int stepR = (r > or ) ? 1 : -1;
		int stepC = (c > oc) ? 1 : -1;

		int i = or +stepR;
		int j = oc + stepC;

		while (i != r)
		{
			if (pieces[i][j].isAliveFun())
				return false;

			i += stepR;
			j += stepC;
		}

		return true;
	}


	else if (selectedPiece == PieceType::KNIGHT)
	{ 
		if ((abs(c - oc) == 2 && abs(r - or ) == 1) || (abs(c - oc) == 1 && abs(r - or ) == 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (selectedPiece == PieceType::QUEEN)
	{
		if (r==or || c == oc)
		{
			int stepR = 0;
			int stepC = 0;

			if (r==or)
				stepC = (c > oc) ? 1 : -1;
			else
				stepR = (r > or ) ? 1 : -1;

			int i = or +stepR;
			int j = oc + stepC;

			while (i != r || j != c)
			{
				if (pieces[i][j].isAliveFun())
					return false;

				i += stepR;
				j += stepC;
			}
			return true;
		}
		else if (abs(r - or ) == abs(c - oc))
		{
			int stepR = (r > or ) ? 1 : -1;
			int stepC = (c > oc) ? 1 : -1;

			int i = or +stepR;
			int j = oc + stepC;

			while (i != r)
			{
				if (pieces[i][j].isAliveFun())
					return false;

				i += stepR;
				j += stepC;
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else if (selectedPiece == PieceType::KING)
	{
		int i = or ;
		int j = oc ;

		if ((i - 1 >= 0 && j - 1 >= 0) && (i - 1 == r && j - 1 == c))
		{
			return true;
		}
		else if ((i + 1 < 8 && j - 1 >= 0) && (i + 1 == r && j - 1 == c))
		{
			return true;
		}
		else if ((i - 1 >= 0 && j + 1 < 8) && (i - 1 == r && j + 1 == c))
		{
			return true;
		}
		else if ((i + 1 < 8 && j + 1 < 8) && (i + 1 == r && j + 1 == c))
		{
			return true;
		}
		else if ((i - 1 >= 0 && i - 1 == r) && (j == c))
		{
			return true;
		}
		else if ((i + 1 < 8 && i + 1 == r) && (j==c))
		{
			return true;
		}
		else if ((j - 1 >= 0 && j - 1 == c) && (i==r))
		{
			return true;
		}
		else if ((j + 1 < 8 && j + 1 == c) && (i==r))
		{
			return true;
		}
		return false;
	}
	else if (selectedPiece == PieceType::PAWN)
	{
		if (c == oc)
		{
			if (pieces[or ][oc].m_colorFun() == PieceColor::LIGHT)
			{
				if (((r==or-1) || ((or==6) && (r==or-2))) && (pieces[r][c].isAliveFun()==false))
					return true;
				else
					return false;
			}
			else
			{
				if (((r==or+1) || ((or == 1) && (r==or+2))) && (pieces[r][c].isAliveFun() == false))
					return true;
				else
					return false;
			}
		}
		else
		{
			if (abs(r - or ) == 1 && abs(c - oc) == 1)
			{
				if (pieces[or][oc].m_colorFun() == PieceColor::LIGHT)
				{
					if ((r < or ) && ((pieces[r][c].isAliveFun() == true) && (pieces[r][c].m_colorFun() == PieceColor::DARK)))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (pieces[or ][oc].m_colorFun() == PieceColor::DARK)
				{
					if ((r > or ) && ((pieces[r][c].isAliveFun() == true) && (pieces[r][c].m_colorFun() == PieceColor::LIGHT)))
					{
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
			else
			{
				return false;
			}
		}
	}
}
