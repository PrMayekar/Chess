#include "tile.h"

Tile::Tile()
	:m_tileCoordinates({ 0.0,0.0,0.0,0.0 }), m_tileColor(WHITE)
{
}

Tile::Tile(Rectangle tileCoordinates, Color tileColor)
	:m_tileCoordinates(tileCoordinates), m_tileColor(tileColor)
{
}

void Tile::drawTile()
{
	DrawRectangleRec(m_tileCoordinates, m_tileColor);
}