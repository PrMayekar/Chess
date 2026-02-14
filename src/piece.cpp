#include <raylib.h>
#include <iostream>
#include "resource_dir.h"
#include "piece.h"
#include "utils.h"

Piece::Piece()
	:m_type(PieceType::NONE), m_color(PieceColor::NONE), m_tex(), m_isAlive(false)
{
}

Piece::Piece(PieceType type, PieceColor color, Texture2D tex, bool isAlive)
	:m_type(type), m_color(color), m_tex(tex), m_isAlive(isAlive)
{
}

void Piece::drawPiece(int r, int c)
{
	Rectangle source = {
		0.0f,
		0.0f,
		m_tex.width,
		m_tex.height
	};

	Rectangle dest = {
		c * 100.0f,
		r * 100.0f,
		100.0f,
		100.0f
	};

	Vector2 origin = { 0,0 };

	DrawTexturePro(m_tex, source, dest, origin, 0.0f, WHITE);
}

bool Piece::isAliveFun() const
{
	if (m_isAlive == true)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

Texture2D Piece::m_texFun() const
{
	return m_tex;
}

PieceType Piece::m_typeFun() const
{
	return m_type;
}

PieceColor Piece::m_colorFun() const
{
	return m_color;
}