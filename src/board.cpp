#include "board.h"

void Board::promote(int r, int c, PieceColor col)
{
	int x = 2;
	for (int i = 0; i < 4; i++)
	{
		promotionTiles[i].drawTile();
		if (col == PieceColor::DARK)
		{
			darkPromotion[i].drawPiece(x, 3.5);
		}
		else if (col == PieceColor::LIGHT)
		{
			lightPromotion[i].drawPiece(x,3.5);
		}
		x += 1;
	}
}

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

	promotionTiles[0] = Tile({ 350,200,100,100 }, Color{ 255, 255, 255, 100 });
	promotionTiles[1] = Tile({ 350,300,100,100 }, Color{ 255, 255, 255, 150 });
	promotionTiles[2] = Tile({ 350,400,100,100 }, Color{ 255, 255, 255, 100 });
	promotionTiles[3] = Tile({ 350,500,100,100 }, Color{ 255, 255, 255, 150 });


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


    // Promotion window intialization


	lightPromotion[0] = Piece(PieceType::ROOK, PieceColor::LIGHT, lightRook, true);
	lightPromotion[1] = Piece(PieceType::KNIGHT, PieceColor::LIGHT, lightKnight, true);
	lightPromotion[2] = Piece(PieceType::BISHOP, PieceColor::LIGHT, lightBishop, true);
	lightPromotion[3] = Piece(PieceType::QUEEN, PieceColor::LIGHT, lightQueen, true);

	darkPromotion[0] = Piece(PieceType::ROOK, PieceColor::DARK, darkRook, true);
	darkPromotion[1] = Piece(PieceType::KNIGHT, PieceColor::DARK, darkKnight, true);
	darkPromotion[2] = Piece(PieceType::BISHOP, PieceColor::DARK, darkBishop, true);
	darkPromotion[3] = Piece(PieceType::QUEEN, PieceColor::DARK, darkQueen, true);

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

void Board::updatePiecePosition2(int r, int c, int nr, PieceColor col)
{
	if (col == PieceColor::DARK)
	{
		pieces[r][c] = darkPromotion[nr];
	}
	else if (col == PieceColor::LIGHT)
	{
		pieces[r][c] = lightPromotion[nr];
	}
}

void Board::addNewPiece(int r, int c, Piece piece)
{
	pieces[r][c] = piece;
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
				if (((r==or-1) || ((pieces[or -1][oc].isAliveFun() == false) && ((or==6) && (r==or-2)))) && (pieces[r][c].isAliveFun() == false))
				{
					if (r == 0)
					{
						promoteFlag = true;
					}
					return true;
				}	
				else
				{
					return false;
				}
			}
			else
			{
				if (((r==or+1) || ((pieces[or +1][oc].isAliveFun() == false) && ((or == 1) && (r==or+2)))) && (pieces[r][c].isAliveFun() == false))
				{
					if (r == 7)
					{
						promoteFlag = true;
					}
					return true;
				}
				else
				{
					return false;
				}
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
						if (r == 0)
						{
							promoteFlag = true;
						}
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
						if (r == 7)
						{
							promoteFlag = true;
						}
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
	return false;
}

bool Board::checkForCheck(PieceColor col)
{

	PieceColor oppositeColor;
	if (col == PieceColor::DARK)
	{
		oppositeColor = PieceColor::LIGHT;
	}
	else if(col == PieceColor::LIGHT)
	{
		oppositeColor = PieceColor::DARK;
	}
	int or =-1;
	int oc =-1; 
	for (int i = 0; i < TILES; i++)
	{
		for (int j = 0; j < TILES; j++)
		{
			if (pieces[i][j].m_typeFun() == PieceType::KING && pieces[i][j].m_colorFun() == col)
			{
				or = i;
				oc = j;
				goto checkpoint;
			}
		}
	}

	checkpoint:

	if (col == PieceColor::DARK)
	{
		if (((or +1 < 8 && pieces[or +1][oc].m_typeFun() == PieceType::KING) && (pieces[or +1][oc].m_colorFun() == PieceColor::LIGHT))
			|| ((or -1 >= 0 && pieces[or -1][oc].m_typeFun() == PieceType::KING) && (pieces[or -1][oc].m_colorFun() == PieceColor::LIGHT))
			|| ((oc + 1 < 8 && pieces[or ][oc + 1].m_typeFun() == PieceType::KING) && (pieces[or][oc+1].m_colorFun() == PieceColor::LIGHT))
			|| ((oc - 1 >= 0 && pieces[or ][oc - 1].m_typeFun() == PieceType::KING) && (pieces[or][oc-1].m_colorFun() == PieceColor::LIGHT))
			|| (((or +1 < 8 && oc + 1 < 8) && (pieces[or +1][oc + 1].m_typeFun() == PieceType::KING)) && (pieces[or +1][oc+1].m_colorFun() == PieceColor::LIGHT))
			|| (((or +1 < 8 && oc - 1 >= 0) && (pieces[or +1][oc - 1].m_typeFun() == PieceType::KING)) && (pieces[or +1][oc-1].m_colorFun() == PieceColor::LIGHT))
			|| (((or -1 >= 0 && oc + 1 < 8) && (pieces[or -1][oc + 1].m_typeFun() == PieceType::KING)) && (pieces[or -1][oc+1].m_colorFun() == PieceColor::LIGHT))
			|| (((or -1 >= 0 && oc - 1 >= 0) && (pieces[or -1][oc - 1].m_typeFun() == PieceType::KING))) && (pieces[or -1][oc-1].m_colorFun() == PieceColor::LIGHT))
		{
			return true;
		}
		if ((or +1 < 8 && oc + 1 < 8) && (pieces[or +1][oc + 1].m_colorFun() == PieceColor::LIGHT && pieces[or +1][oc + 1].m_typeFun() == PieceType::PAWN))
		{
			return true;
		}
		if ((or +1 < 8 && oc - 1 >=0) && (pieces[or +1][oc - 1].m_colorFun() == PieceColor::LIGHT && pieces[or +1][oc - 1].m_typeFun() == PieceType::PAWN))
		{
			return true;
		}
		if (((or +2 < 8 && oc + 1 < 8) && (pieces[or +2][oc + 1].m_typeFun() == PieceType::KNIGHT && pieces[or +2][oc + 1].m_colorFun() == PieceColor::LIGHT))
			|| ((or -2 >= 0 && oc + 1 < 8) && (pieces[or -2][oc + 1].m_typeFun() == PieceType::KNIGHT && pieces[or -2][oc + 1].m_colorFun() == PieceColor::LIGHT))
			|| ((or +2 < 8 && oc - 1 >= 0) && (pieces[or +2][oc - 1].m_typeFun() == PieceType::KNIGHT && pieces[or +2][oc - 1].m_colorFun() == PieceColor::LIGHT))
			|| ((or -2 >= 0 && oc - 1 >= 0) && (pieces[or -2][oc - 1].m_typeFun() == PieceType::KNIGHT && pieces[or -2][oc - 1].m_colorFun() == PieceColor::LIGHT))
			|| ((or +1 < 8 && oc +2 < 8) && (pieces[or +1][oc + 2].m_typeFun() == PieceType::KNIGHT && pieces[or +1][oc + 2].m_colorFun() == PieceColor::LIGHT))
			|| ((or +1 < 8 && oc - 2 >= 0) && (pieces[or +1][oc - 2].m_typeFun() == PieceType::KNIGHT && pieces[or +1][oc - 2].m_colorFun() == PieceColor::LIGHT))
			|| ((or -1 >= 0 && oc + 2 < 8) && (pieces[or -1][oc + 2].m_typeFun() == PieceType::KNIGHT && pieces[or -1][oc + 2].m_colorFun() == PieceColor::LIGHT))
			|| ((or -1 >= 0 && oc - 2 >= 0) && (pieces[or -1][oc - 2].m_typeFun() == PieceType::KNIGHT && pieces[or -1][oc - 2].m_colorFun() == PieceColor::LIGHT)))
		{
			return true;
		}
		int x = or -1;
		int y = oc ;
			while (x>=0)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				x--;
			}
	
		x = or +1;
		y = oc;
		
			while (x < 8)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				x++;
			}
		
		x = or ;
		y = oc -1;
		
			while (y >= 0)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				y--;
			}
		
		x = or ;
		y = oc +1;
		
			while (y < 8)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				y++;
			}
		

		x = or -1;
		y = oc +1;

		while (x >= 0 && y < 8)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x--;
			y++;
		}

		x = or-1 ;
		y = oc-1 ;

		while (x >= 0 && y >= 0)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x--;
			y--;
		}

		x = or +1;
		y = oc -1;

		while (x < 8 && y >= 0)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x++;
			y--;
		}

		x = or+1 ;
		y = oc+1 ;

		while (x < 8 && y < 8)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::DARK) || (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::LIGHT && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x++;
			y++;
		}
		return false;
	}		
	else if (col == PieceColor::LIGHT)
	{
		if (((or +1 < 8 && pieces[or +1][oc].m_typeFun() == PieceType::KING) && (pieces[or +1][oc].m_colorFun() == PieceColor::DARK))
			|| ((or -1 >= 0 && pieces[or -1][oc].m_typeFun() == PieceType::KING) && (pieces[or -1][oc].m_colorFun() == PieceColor::DARK))
			|| ((oc + 1 < 8 && pieces[or ][oc + 1].m_typeFun() == PieceType::KING) && (pieces[or ][oc + 1].m_colorFun() == PieceColor::DARK)
			|| ((oc - 1 >= 0 && pieces[or ][oc - 1].m_typeFun() == PieceType::KING) && (pieces[or ][oc - 1].m_colorFun() == PieceColor::DARK))
			|| (((or +1 < 8 && oc + 1 < 8) && (pieces[or +1][oc + 1].m_typeFun() == PieceType::KING)) && (pieces[or +1][oc + 1].m_colorFun() == PieceColor::DARK))
			|| (((or +1 < 8 && oc - 1 >= 0) && (pieces[or +1][oc - 1].m_typeFun() == PieceType::KING)) && (pieces[or +1][oc - 1].m_colorFun() == PieceColor::DARK))
			|| (((or -1 >= 0 && oc + 1 < 8) && (pieces[or -1][oc + 1].m_typeFun() == PieceType::KING)) && (pieces[or -1][oc + 1].m_colorFun() == PieceColor::DARK))
			|| (((or -1 >= 0 && oc - 1 >= 0) && (pieces[or -1][oc - 1].m_typeFun() == PieceType::KING))) && (pieces[or -1][oc - 1].m_colorFun() == PieceColor::DARK)))
		{
			return true;
		}
		if ((or -1 >= 0 && oc + 1 < 8) && (pieces[or -1][oc + 1].m_colorFun() == PieceColor::DARK && pieces[or -1][oc + 1].m_typeFun() == PieceType::PAWN))
		{
			return true;
		}
		if ((or -1 >= 0 && oc - 1 >= 0) && (pieces[or -1][oc - 1].m_colorFun() == PieceColor::DARK && pieces[or -1][oc - 1].m_typeFun() == PieceType::PAWN))
		{
			return true;
		}
		if (((or +2 < 8 && oc + 1 < 8) && (pieces[or +2][oc + 1].m_typeFun() == PieceType::KNIGHT && pieces[or +2][oc + 1].m_colorFun() == PieceColor::DARK))
			|| ((or -2 >= 0 && oc + 1 < 8) && (pieces[or -2][oc + 1].m_typeFun() == PieceType::KNIGHT && pieces[or -2][oc + 1].m_colorFun() == PieceColor::DARK))
			|| ((or +2 < 8 && oc - 1 >= 0) && (pieces[or +2][oc - 1].m_typeFun() == PieceType::KNIGHT && pieces[or +2][oc - 1].m_colorFun() == PieceColor::DARK))
			|| ((or -2 >= 0 && oc - 1 >= 0) && (pieces[or -2][oc - 1].m_typeFun() == PieceType::KNIGHT && pieces[or -2][oc - 1].m_colorFun() == PieceColor::DARK))
			|| ((or +1 < 8 && oc + 2 < 8) && (pieces[or +1][oc + 2].m_typeFun() == PieceType::KNIGHT && pieces[or +1][oc + 2].m_colorFun() == PieceColor::DARK))
			|| ((or +1 < 8 && oc - 2 >= 0) && (pieces[or +1][oc - 2].m_typeFun() == PieceType::KNIGHT && pieces[or +1][oc - 2].m_colorFun() == PieceColor::DARK))
			|| ((or -1 >= 0 && oc + 2 < 8) && (pieces[or -1][oc + 2].m_typeFun() == PieceType::KNIGHT && pieces[or -1][oc + 2].m_colorFun() == PieceColor::DARK))
			|| ((or -1 >= 0 && oc - 2 >= 0) && (pieces[or -1][oc - 2].m_typeFun() == PieceType::KNIGHT && pieces[or -1][oc - 2].m_colorFun() == PieceColor::DARK)))
		{
			return true;
		}
		int x = or-1;
		int y = oc;
		if (x != 0)
		{
			while (x >= 0)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::DARK) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				x--;
			}
		}
		x = or +1;
		y = oc;
		if (x != 7)
		{
			while (x < 8)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::DARK) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				x++;
			}
		}
		x = or ;
		y = oc-1;
		if (y != 0)
		{
			while (y >= 0)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::DARK) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				y--;
			}
		}
		x = or ;
		y = oc+1;
		if (y != 7)
		{
			while (y < 8)
			{
				if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::ROOK && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
				{
					break;
				}
				else if ((pieces[x][y].m_colorFun() == PieceColor::DARK) && (pieces[x][y].m_typeFun() == PieceType::ROOK || pieces[x][y].m_typeFun() == PieceType::QUEEN))
				{
					return true;
				}
				y++;
			}
		}

		x = or -1;
		y = oc+1;

		while (x >= 0 && y < 8)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x--;
			y++;
		}

		x = or -1;
		y = oc-1;

		while (x >= 0 && y >= 0)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x--;
			y--;
		}

		x = or +1;
		y = oc-1;

		while (x < 8 && y >= 0)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x++;
			y--;
		}

		x = or +1;
		y = oc+1;

		while (x < 8 && y < 8)
		{
			if ((pieces[x][y].m_colorFun() == PieceColor::LIGHT) || (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() != PieceType::BISHOP && pieces[x][y].m_typeFun() != PieceType::QUEEN)))
			{
				break;
			}
			else if (pieces[x][y].m_colorFun() == PieceColor::DARK && (pieces[x][y].m_typeFun() == PieceType::BISHOP || pieces[x][y].m_typeFun() == PieceType::QUEEN))
			{
				return true;
			}
			x++;
			y++;
		}
		return false;
	}
	else
	{
		return false;
	}
}

bool Board::promoteFlagCheck()
{
	if (promoteFlag == true)
		return true;
	else
		return false;
}

void Board::setPromoteFlag()
{
	promoteFlag = true;
}

void Board::clearPromoteFlag()
{
	promoteFlag = false;
}

bool Board::checkForCheckMate(PieceColor col)
{
	Piece capturedPiece = Piece();
	PieceColor opponent;
	int or = -1;
	int oc = -1;
	if (col == PieceColor::DARK)
	{
		opponent = PieceColor::LIGHT;
	}
	else
	{
		opponent = PieceColor::DARK;
	}
	
	for (int i = 0; i < TILES; i++)
	{
		for (int j = 0; j < TILES; j++)
		{
			if (pieces[i][j].m_typeFun() == PieceType::KING && pieces[i][j].m_colorFun() == col)
			{
				or = i;
				oc = j;
			}
		}
	}

	int i = or ;
	int j = oc ;

	if ((i + 1 < 8) && (pieces[i + 1][j].isAliveFun() == false || pieces[i + 1][j].m_colorFun()==opponent))
	{
		if (pieces[i + 1][j].m_colorFun() == opponent)
		{
			capturedPiece = pieces[i + 1][j];
		}
		updatePiecePosition(i + 1, oc, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i + 1, oc);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i + 1, oc, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, i + 1, oc);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i + 1, oc, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}

	if ((j + 1 < 8) && (pieces[i][j+1].isAliveFun() == false || pieces[i][j+1].m_colorFun() == opponent))
	{
		capturedPiece = pieces[i][j + 1];
		updatePiecePosition(or, j+1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, or, j+1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(or, j+1, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, or , j + 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(or , j + 1, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}

	if ((i - 1 >= 0) && (pieces[i - 1][j].isAliveFun() == false || pieces[i-1][j].m_colorFun() == opponent))
	{
		capturedPiece = pieces[i - 1][j];
		updatePiecePosition(i - 1, oc, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i - 1, oc);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i-1 , oc, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, i - 1, oc);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i - 1, oc, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}

	if ((j - 1 >= 0) && (pieces[i][j - 1].isAliveFun() == false || pieces[i][j-1].m_colorFun() == opponent))
	{
		capturedPiece = pieces[i][j - 1];
		updatePiecePosition(or , j - 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, or , j - 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(or , j - 1, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, or , j - 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(or , j - 1, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}

	if (((i + 1 < 8) && (j+1<8)) && (pieces[i+1][j + 1].isAliveFun() == false || pieces[i+1][j+1].m_colorFun()==opponent))
	{
		capturedPiece = pieces[i+1][j+1];
		updatePiecePosition(i+1 , j + 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i+1 , j + 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i + 1, j + 1, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, i + 1, j + 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i + 1, j + 1, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}

	if (((i + 1 < 8) && (j - 1 >= 0)) && (pieces[i + 1][j - 1].isAliveFun() == false || pieces[i + 1][j - 1].m_colorFun()==opponent))
	{
		capturedPiece = pieces[i + 1][j - 1];
		updatePiecePosition(i + 1, j - 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i + 1, j - 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i + 1, j - 1, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, i + 1, j - 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i + 1, j - 1, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}

	if (((i - 1 >= 0) && (j + 1 < 8)) && (pieces[i - 1][j + 1].isAliveFun() == false || pieces[i - 1][j + 1].m_colorFun() == opponent))
	{
		capturedPiece = pieces[i - 1][j + 1];
		updatePiecePosition(i - 1, j + 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i - 1, j + 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i - 1, j + 1, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, i - 1, j + 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i - 1, j + 1, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}

	if (((i - 1 >= 0) && (j - 1 >= 0)) && (pieces[i - 1][j - 1].isAliveFun() == false || pieces[i - 1][j - 1].m_colorFun() == opponent))
	{
		capturedPiece = pieces[i - 1][j - 1];
		updatePiecePosition(i - 1, j - 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i - 1, j - 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i - 1, j - 1, capturedPiece);
				capturedPiece = Piece();
			}
			return false;
		}
		else
		{
			updatePiecePosition(or , oc, i - 1, j - 1);
			if (capturedPiece.isAliveFun())
			{
				addNewPiece(i - 1, j - 1, capturedPiece);
				capturedPiece = Piece();
			}
		}
	}



	for (int i = 0; i < TILES; i++)
	{
		for (int j = 0; j < TILES; j++)
		{
			if (pieces[i][j].isAliveFun() == true && (pieces[i][j].m_colorFun() == col && pieces[i][j].m_typeFun()!=PieceType::KING))
			{
				if (checkChecker(pieces[i][j], or,oc,i,j,opponent))
				{
					return false;
				}
			}
		}
	}


	return true;
}

bool Board::checkChecker(Piece p, int kr, int kc, int pr, int pc, PieceColor opp)
{
	Piece capturedPiece = Piece();
	if (p.m_typeFun() == PieceType::ROOK || p.m_typeFun() == PieceType::QUEEN)
	{
		if (pr < 7)
		{
			int i = pr + 1;
			int j = pc;
			while (i < 8)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}

				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}

				updatePiecePosition(i, j, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					break;
				}
				i++;
				capturedPiece = Piece();
			}
		}

		if (pr > 0)
		{
			int i = pr - 1;
			int j = pc;
			while (i >= 0)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}
				updatePiecePosition(i, j, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					break;
				}
				i--;
				capturedPiece = Piece();
			}
		}

		if (pc < 7)
		{
			int i = pr;
			int j = pc+1;
			while (j < 8)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}
				updatePiecePosition(i, j, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					break;
				}
				j++;
				capturedPiece = Piece();
			}
		}

		if (pc > 0)
		{
			int i = pr;
			int j = pc - 1;
			while (j >= 0)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}

				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}
				updatePiecePosition(i, j, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					return true;
				}
				else 
				{
					updatePiecePosition(pr, pc, i, j);
					if (capturedPiece.isAliveFun())
					{
						addNewPiece(i, j, capturedPiece);
					}
					break;
				}
				j--;
				capturedPiece = Piece();
			}
		}
	}

	if (p.m_typeFun() == PieceType::KNIGHT)
	{
		Piece capturedPiece = Piece();

		if ((pr + 2 < 8 && pc + 1 < 8))
		{
			if (pieces[pr + 2][pc + 1].isAliveFun() == true && pieces[pr + 2][pc + 1].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr + 2][pc + 1];
			}
			else if (pieces[pr + 2][pc + 1].isAliveFun() == true && pieces[pr + 2][pc + 1].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr + 2, pc + 1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 2, pc + 1);
						addNewPiece(pr + 2, pc + 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 2, pc + 1);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 2, pc + 1);
						addNewPiece(pr + 2, pc + 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 2, pc + 1);
					capturedPiece = Piece();
				}
			}
		}

		if ((pr - 2 >= 0 && pc + 1 < 8))
		{
			if (pieces[pr - 2][pc + 1].isAliveFun() == true && pieces[pr - 2][pc + 1].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr - 2][pc + 1];
			}
			else if (pieces[pr - 2][pc + 1].isAliveFun() == true && pieces[pr - 2][pc + 1].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr - 2, pc + 1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 2, pc + 1);
						addNewPiece(pr - 2, pc + 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 2, pc + 1);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 2, pc + 1);
						addNewPiece(pr - 2, pc + 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 2, pc + 1);
					capturedPiece = Piece();
				}
			}
		}

		if ((pr + 2 < 8 && pc - 1 >= 0))
		{
			if (pieces[pr + 2][pc - 1].isAliveFun() == true && pieces[pr + 2][pc - 1].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr + 2][pc - 1];
			}
			else if (pieces[pr + 2][pc - 1].isAliveFun() == true && pieces[pr + 2][pc - 1].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr + 2, pc - 1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 2, pc - 1);
						addNewPiece(pr + 2, pc - 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 2, pc - 1);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 2, pc - 1);
						addNewPiece(pr + 2, pc - 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 2, pc - 1);
					capturedPiece = Piece();
				}
			}
		}

		if ((pr - 2 >= 0 && pc - 1 >= 0))
		{
			if (pieces[pr - 2][pc - 1].isAliveFun() == true && pieces[pr - 2][pc - 1].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr - 2][pc - 1];
			}
			else if (pieces[pr - 2][pc - 1].isAliveFun() == true && pieces[pr - 2][pc - 1].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr - 2, pc - 1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 2, pc - 1);
						addNewPiece(pr - 2, pc - 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 2, pc - 1);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 2, pc - 1);
						addNewPiece(pr - 2, pc - 1, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 2, pc - 1);
					capturedPiece = Piece();
				}
			}
		}

		if ((pr + 1 < 8 && pc + 2 < 8))
		{
			if (pieces[pr + 1][pc + 2].isAliveFun() == true && pieces[pr + 1][pc + 2].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr + 1][pc + 2];
			}
			else if (pieces[pr + 1][pc + 2].isAliveFun() == true && pieces[pr + 1][pc + 2].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr + 1, pc + 2, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 1, pc + 2);
						addNewPiece(pr + 1, pc + 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 1, pc + 2);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 1, pc + 2);
						addNewPiece(pr + 1, pc + 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 1, pc + 2);
					capturedPiece = Piece();
				}
			}
		}

		if ((pr + 1 < 8 && pc - 2 >= 0))
		{
			if (pieces[pr + 1][pc - 2].isAliveFun() == true && pieces[pr + 1][pc - 2].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr + 1][pc - 2];
			}
			else if (pieces[pr + 1][pc - 2].isAliveFun() == true && pieces[pr + 1][pc - 2].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr + 1, pc - 2, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 1, pc - 2);
						addNewPiece(pr + 1, pc - 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 1, pc - 2);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr + 1, pc - 2);
						addNewPiece(pr + 1, pc - 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr + 1, pc - 2);
					capturedPiece = Piece();
				}
			}
		}

		if ((pr - 1 >= 0 && pc + 2 < 8))
		{
			if (pieces[pr - 1][pc + 2].isAliveFun() == true && pieces[pr - 1][pc + 2].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr - 1][pc + 2];
			}
			else if (pieces[pr - 1][pc + 2].isAliveFun() == true && pieces[pr - 1][pc + 2].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr - 1, pc + 2, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 1, pc + 2);
						addNewPiece(pr - 1, pc + 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 1, pc + 2);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 1, pc + 2);
						addNewPiece(pr - 1, pc + 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 1, pc + 2);
					capturedPiece = Piece();
				}
			}
		}

		if ((pr - 1 >= 0 && pc - 2 >= 0))
		{
			if (pieces[pr - 1][pc - 2].isAliveFun() == true && pieces[pr - 1][pc - 2].m_colorFun() == opp)
			{
				capturedPiece = pieces[pr - 1][pc - 2];
			}
			else if (pieces[pr - 1][pc - 2].isAliveFun() == true && pieces[pr - 1][pc - 2].m_colorFun() == p.m_colorFun())
			{

			}
			else
			{
				updatePiecePosition(pr - 1, pc - 2, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 1, pc - 2);
						addNewPiece(pr - 1, pc - 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 1, pc - 2);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					if (capturedPiece.isAliveFun())
					{
						updatePiecePosition(pr, pc, pr - 1, pc - 2);
						addNewPiece(pr - 1, pc - 2, capturedPiece);
					}
					updatePiecePosition(pr, pc, pr - 1, pc - 2);
					capturedPiece = Piece();
				}
			}
		}
	}

	if (p.m_typeFun() == PieceType::BISHOP || p.m_typeFun() == PieceType::QUEEN)
	{
		Piece capturedPiece = Piece();
		if (pr < 7 && pc < 7)
		{
			int i = pr + 1;
			int j = pc + 1;

			while (i < 8 && j < 8)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}
				else if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}
				else
				{
					updatePiecePosition(i, j, pr, pc);
					if (!checkForCheck(p.m_colorFun()))
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							return true;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
						return true;
					}
					else
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							break;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
					}
				}
				i++;
				j++;
			}
		}

		if (pr < 7 && pc > 0)
		{
			int i = pr + 1;
			int j = pc - 1;

			while (i < 8 && j >= 0)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}
				else if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}
				else
				{
					updatePiecePosition(i, j, pr, pc);
					if (!checkForCheck(p.m_colorFun()))
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							return true;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
						return true;
					}
					else
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							break;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
					}
				}
				i++;
				j--;
			}
		}

		if (pr > 0 && pc < 7)
		{
			int i = pr - 1;
			int j = pc + 1;

			while (i >= 0 && j < 8)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}
				else if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}
				else
				{
					updatePiecePosition(i, j, pr, pc);
					if (!checkForCheck(p.m_colorFun()))
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							return true;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
						return true;
					}
					else
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							break;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
					}
				}
				i--;
				j++;
			}
		}

		if (pr > 0 && pc > 0)
		{
			int i = pr - 1;
			int j = pc - 1;

			while (i >= 0 && j >= 0)
			{
				if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == opp)
				{
					capturedPiece = pieces[i][j];
				}
				else if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == p.m_colorFun())
				{
					break;
				}
				else
				{
					updatePiecePosition(i, j, pr, pc);
					if (!checkForCheck(p.m_colorFun()))
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							return true;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
						return true;
					}
					else
					{
						if (capturedPiece.isAliveFun())
						{
							updatePiecePosition(pr, pc, i, j);
							addNewPiece(i, j, capturedPiece);
							capturedPiece = Piece();
							break;
						}
						updatePiecePosition(pr, pc, i, j);
						capturedPiece = Piece();
					}
				}
				i--;
				j--;
			}
		}
	}

	if (p.m_typeFun() == PieceType::PAWN)
	{
		Piece capturedPiece = Piece();
		if (p.m_colorFun() == PieceColor::DARK && pr<7)
		{
			if (pr == 1 && (pieces[pr+1][pc].isAliveFun()==false && pieces[pr + 2][pc].isAliveFun() == false))
			{
				updatePiecePosition(pr + 2, pc, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition( pr, pc,pr + 2, pc);
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr + 2, pc);
				}
			}
			if(pieces[pr + 1][pc].isAliveFun() == false)
			{
				updatePiecePosition(pr + 1, pc, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, pr + 1, pc);
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr + 1, pc);
				}
			}
			if ((pc < 7) && (pieces[pr+1][pc+1].m_colorFun()==opp))
			{
				capturedPiece = pieces[pr + 1][pc + 1];
				updatePiecePosition(pr + 1, pc+1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, pr + 1, pc+1);
					addNewPiece(pr + 1, pc + 1, capturedPiece);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr + 1, pc+1);
					addNewPiece(pr + 1, pc + 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
			if ((pc > 0) && (pieces[pr + 1][pc - 1].m_colorFun() == opp))
			{
				capturedPiece = pieces[pr + 1][pc - 1];
				updatePiecePosition(pr + 1, pc - 1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, pr + 1, pc - 1);
					addNewPiece(pr + 1, pc - 1, capturedPiece);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr + 1, pc - 1);
					addNewPiece(pr + 1, pc - 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if (p.m_colorFun() == PieceColor::LIGHT && pr > 0)
		{
			if (pr == 6 && (pieces[pr - 1][pc].isAliveFun() == false && pieces[pr - 2][pc].isAliveFun() == false))
			{
				updatePiecePosition(pr - 2, pc, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, pr - 2, pc);
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr - 2, pc);
				}
			}
			if (pieces[pr - 1][pc].isAliveFun() == false)
			{
				updatePiecePosition(pr - 1, pc, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, pr - 1, pc);
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr - 1, pc);
				}
			}
			if ((pc < 7) && (pieces[pr - 1][pc + 1].m_colorFun() == opp))
			{
				capturedPiece = pieces[pr - 1][pc + 1];
				updatePiecePosition(pr - 1, pc + 1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, pr - 1, pc + 1);
					addNewPiece(pr - 1, pc + 1, capturedPiece);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr - 1, pc + 1);
					addNewPiece(pr - 1, pc + 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
			if ((pc > 0) && (pieces[pr - 1][pc - 1].m_colorFun() == opp))
			{
				capturedPiece = pieces[pr - 1][pc - 1];
				updatePiecePosition(pr - 1, pc - 1, pr, pc);
				if (!checkForCheck(p.m_colorFun()))
				{
					updatePiecePosition(pr, pc, pr - 1, pc - 1);
					addNewPiece(pr - 1, pc - 1, capturedPiece);
					capturedPiece = Piece();
					return true;
				}
				else
				{
					updatePiecePosition(pr, pc, pr - 1, pc - 1);
					addNewPiece(pr - 1, pc - 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

	}

	return false;
}

bool Board::checkForStaleMate(PieceColor col)
{
	for (int i = 0; i < TILES; i++)
	{
		for (int j = 0; j < TILES; j++)
		{
			if (pieces[i][j].isAliveFun() == true && pieces[i][j].m_colorFun() == col)
			{
				if (staleChecker(i,j, pieces[i][j]))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Board::staleChecker(int pr, int pc, Piece p)  // returns true if player has atleast one possible move, else false
{
	PieceColor opp;
	if (p.m_colorFun() == PieceColor::DARK)
	{
		opp = PieceColor::LIGHT;
	}
	else if (p.m_colorFun() == PieceColor::LIGHT)
	{
		opp = PieceColor::DARK;
	}

	if (p.m_typeFun() == PieceType::ROOK || p.m_typeFun() == PieceType::QUEEN)
	{
		if (pr + 1 < 8 && (pieces[pr + 1][pc].isAliveFun() == false || pieces[pr+1][pc].m_colorFun() == opp))
		{
			return true;
		}

		if (pr - 1 >= 0 && (pieces[pr - 1][pc].isAliveFun() == false || pieces[pr - 1][pc].m_colorFun() == opp))
		{
			return true;
		}

		if (pc + 1 < 8 && (pieces[pr][pc + 1].isAliveFun() == false || pieces[pr][pc + 1].m_colorFun() == opp))
		{
			return true;
		}

		if (pc - 1 >= 0 && (pieces[pr][pc - 1].isAliveFun() == false || pieces[pr][pc - 1].m_colorFun() == opp))
		{
			return true;
		}
	}

	if (p.m_typeFun() == PieceType::BISHOP || p.m_typeFun() == PieceType::QUEEN)
	{
		if ((pr + 1 < 8 && pc + 1 < 8) && (pieces[pr + 1][pc + 1].isAliveFun() == false || pieces[pr + 1][pc + 1].m_colorFun() == opp))
		{
			return true;
		}

		if ((pr + 1 < 8 && pc - 1 >= 0) && (pieces[pr + 1][pc - 1].isAliveFun() == false || pieces[pr + 1][pc - 1].m_colorFun() == opp))
		{
			return true;
		}

		if ((pr - 1 >= 0 && pc + 1 < 8) && (pieces[pr - 1][pc + 1].isAliveFun() == false || pieces[pr - 1][pc + 1].m_colorFun() == opp))
		{
			return true;
		}

		if ((pr - 1 >= 0 && pc - 1 >= 0) && (pieces[pr - 1][pc - 1].isAliveFun() == false || pieces[pr - 1][pc - 1].m_colorFun() == opp))
		{
			return true;
		}
	}

	if (p.m_typeFun() == PieceType::KNIGHT)
	{
		if (((pr + 2 < 8 && pc + 1 < 8) && (pieces[pr + 2][pc + 1].isAliveFun() == false || pieces[pr + 2][pc + 1].m_colorFun() == opp))
			|| ((pr -2 >= 0 && pc + 1 < 8) && (pieces[pr -2][pc + 1].isAliveFun() == false || pieces[pr -2][pc + 1].m_colorFun() == opp))
			|| ((pr +2 < 8 && pc - 1 >= 0) && (pieces[pr +2][pc - 1].isAliveFun() == false || pieces[pr +2][pc - 1].m_colorFun() == opp))
			|| ((pr -2 >= 0 && pc - 1 >= 0) && (pieces[pr -2][pc - 1].isAliveFun() == false || pieces[pr -2][pc - 1].m_colorFun() == opp))
			|| ((pr +1 < 8 && pc + 2 < 8) && (pieces[pr +1][pc + 2].isAliveFun() == false || pieces[pr +1][pc + 2].m_colorFun() == opp))
			|| ((pr -1 >= 0 && pc + 2 < 8) && (pieces[pr -1][pc + 2].isAliveFun() == false || pieces[pr -1][pc + 2].m_colorFun() == opp))
			|| ((pr -1 >= 0 && pc - 2 >= 0) && (pieces[pr -1][pc - 2].isAliveFun() == false || pieces[pr -1][pc - 2].m_colorFun() == opp)))
		{
			return true;
		}
	}

	if (p.m_typeFun() == PieceType::PAWN)
	{
		if (p.m_colorFun() == PieceColor::DARK)
		{
			if (pr + 1 < 8 && pieces[pr + 1][pc].isAliveFun() == false)
			{
				return true;
			}
			
			if ((pr == 1) && (pieces[pr + 1][pc].isAliveFun() == false && pieces[pr + 2][pc].isAliveFun() == false))
			{
				return true;
			}

			if ((pr + 1 < 8 && pc + 1 < 8) && (pieces[pr + 1][pc + 1].m_colorFun() == opp))
			{
				return true;
			}

			if ((pr + 1 < 8 && pc - 1 >= 0) && (pieces[pr + 1][pc - 1].m_colorFun() == opp))
			{
				return true;
			}
		}

		if (p.m_colorFun() == PieceColor::LIGHT)
		{
			if (pr - 1 < 8 && pieces[pr - 1][pc].isAliveFun() == false)
			{
				return true;
			}

			if ((pr == 6) && (pieces[pr - 1][pc].isAliveFun() == false && pieces[pr - 2][pc].isAliveFun() == false))
			{
				return true;
			}

			if ((pr - 1 < 8 && pc + 1 < 8) && (pieces[pr - 1][pc + 1].m_colorFun() == opp))
			{
				return true;
			}

			if ((pr - 1 >= 0 && pc - 1 >= 0) && (pieces[pr - 1][pc - 1].m_colorFun() == opp))
			{
				return true;
			}
		}
	}

	Piece capturedPiece = Piece();

	int i = pr;
	int j = pc;
	int or = pr;
	int oc = pc;

	PieceColor col = p.m_colorFun();
	PieceColor opponent = opp;


	if (p.m_typeFun() == PieceType::KING)
	{
		if ((i + 1 < 8) && (pieces[i + 1][j].isAliveFun() == false || pieces[i + 1][j].m_colorFun() == opponent))
		{
			if (pieces[i + 1][j].m_colorFun() == opp)
			{
				capturedPiece = pieces[i + 1][j];
			}
			updatePiecePosition(i + 1, oc, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, i + 1, oc);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i + 1, oc, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, i + 1, oc);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i + 1, oc, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if ((j + 1 < 8) && (pieces[i][j + 1].isAliveFun() == false || pieces[i][j + 1].m_colorFun() == opponent))
		{
			capturedPiece = pieces[i][j + 1];
			updatePiecePosition(or , j + 1, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, or , j + 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(or , j + 1, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, or , j + 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(or , j + 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if ((i - 1 >= 0) && (pieces[i - 1][j].isAliveFun() == false || pieces[i - 1][j].m_colorFun() == opponent))
		{
			capturedPiece = pieces[i - 1][j];
			updatePiecePosition(i - 1, oc, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, i - 1, oc);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i - 1, oc, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, i - 1, oc);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i - 1, oc, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if ((j - 1 >= 0) && (pieces[i][j - 1].isAliveFun() == false || pieces[i][j - 1].m_colorFun() == opponent))
		{
			capturedPiece = pieces[i][j - 1];
			updatePiecePosition(or , j - 1, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, or , j - 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(or , j - 1, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, or , j - 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(or , j - 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if (((i + 1 < 8) && (j + 1 < 8)) && (pieces[i + 1][j + 1].isAliveFun() == false || pieces[i + 1][j + 1].m_colorFun() == opponent))
		{
			capturedPiece = pieces[i + 1][j + 1];
			updatePiecePosition(i + 1, j + 1, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, i + 1, j + 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i + 1, j + 1, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, i + 1, j + 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i + 1, j + 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if (((i + 1 < 8) && (j - 1 >= 0)) && (pieces[i + 1][j - 1].isAliveFun() == false || pieces[i + 1][j - 1].m_colorFun() == opponent))
		{
			capturedPiece = pieces[i + 1][j - 1];
			updatePiecePosition(i + 1, j - 1, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, i + 1, j - 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i + 1, j - 1, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, i + 1, j - 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i + 1, j - 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if (((i - 1 >= 0) && (j + 1 < 8)) && (pieces[i - 1][j + 1].isAliveFun() == false || pieces[i - 1][j + 1].m_colorFun() == opponent))
		{
			capturedPiece = pieces[i - 1][j + 1];
			updatePiecePosition(i - 1, j + 1, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, i - 1, j + 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i - 1, j + 1, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, i - 1, j + 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i - 1, j + 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}

		if (((i - 1 >= 0) && (j - 1 >= 0)) && (pieces[i - 1][j - 1].isAliveFun() == false || pieces[i - 1][j - 1].m_colorFun() == opponent))
		{
			updatePiecePosition(i - 1, j - 1, or , oc);
			if (!checkForCheck(col))
			{
				updatePiecePosition(or , oc, i - 1, j - 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i - 1, j - 1, capturedPiece);
					capturedPiece = Piece();
				}
				return true;
			}
			else
			{
				updatePiecePosition(or , oc, i - 1, j - 1);
				if (capturedPiece.isAliveFun())
				{
					addNewPiece(i - 1, j - 1, capturedPiece);
					capturedPiece = Piece();
				}
			}
		}
	}



	return false;
}