#pragma once
#include <raylib.h>
#include <iostream>
#include "resource_dir.h"
#include "utils.h"

class Piece
{
protected:
	PieceType m_type;
	PieceColor m_color;
	Texture2D m_tex;
	bool m_isAlive;

public:
	Piece();
	Piece(PieceType type, PieceColor color, Texture2D tex, bool isAlive);
	void drawPiece(int r, int c);
	bool isAliveFun() const;
	Texture2D m_texFun() const;
	PieceType m_typeFun() const;
	PieceColor m_colorFun() const;
};