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

	if ((i + 1 < 8) && (pieces[i + 1][j].isAliveFun() == false))
	{
		updatePiecePosition(i + 1, oc, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i + 1, oc);
			return false;
		}
	}

	if ((j + 1 < 8) && (pieces[i][j+1].isAliveFun() == false))
	{
		updatePiecePosition(or, j+1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, or, j+1);
			return false;
		}
	}

	if ((i - 1 >= 0) && (pieces[i - 1][j].isAliveFun() == false))
	{
		updatePiecePosition(i - 1, oc, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i - 1, oc);
			return false;
		}
	}

	if ((j - 1 >= 0) && (pieces[i][j - 1].isAliveFun() == false))
	{
		updatePiecePosition(or , j - 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, or , j - 1);
			return false;
		}
	}

	if (((i + 1 < 8) && (j+1<8)) && (pieces[i+1][j + 1].isAliveFun() == false))
	{
		updatePiecePosition(i+1 , j + 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i+1 , j + 1);
			return false;
		}
	}

	if (((i + 1 < 8) && (j - 1 >= 0)) && (pieces[i + 1][j - 1].isAliveFun() == false))
	{
		updatePiecePosition(i + 1, j - 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i + 1, j - 1);
			return false;
		}
	}

	if (((i - 1 >= 0) && (j + 1 < 8)) && (pieces[i - 1][j + 1].isAliveFun() == false))
	{
		updatePiecePosition(i - 1, j + 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i - 1, j + 1);
			return false;
		}
	}

	if (((i - 1 >= 0) && (j - 1 >= 0)) && (pieces[i - 1][j - 1].isAliveFun() == false))
	{
		updatePiecePosition(i - 1, j - 1, or , oc);
		if (!checkForCheck(col))
		{
			updatePiecePosition(or , oc, i - 1, j - 1);
			return false;
		}
	}
	return true;
}
