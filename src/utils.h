#pragma once

enum PieceType
{
	NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum PieceColor
{
	DARK, LIGHT
};

enum class STATE
{
	SELECT_PIECE, SELECT_DESTINATION
};
