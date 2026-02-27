#include "tile.h"
#define TILES 8
#define TILESIZE 100

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

void Tile::hightlightSelectedPiece(int i, int j)
{
	DrawRectangleRec({ (float)j * TILESIZE, (float)i * TILESIZE,TILESIZE,TILESIZE }, Color{ 253, 249, 0, 100 });
}
