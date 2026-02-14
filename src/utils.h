#pragma once

enum class PieceType
{
	NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum class PieceColor
{
	DARK, LIGHT, NONE
};

enum class STATE
{
	SELECT_PIECE, SELECT_DESTINATION
};
