#pragma once
#include <raylib.h>
#include <iostream>
#include "resource_dir.h"

class Tile
{
protected:
	Rectangle m_tileCoordinates;
	Color m_tileColor;

public:
	Tile();
	Tile(Rectangle tileCoordinates, Color tileColor);
	void drawTile();
};
