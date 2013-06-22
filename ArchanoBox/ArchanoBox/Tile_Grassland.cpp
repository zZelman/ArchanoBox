#include <iostream>

#include "Tile.h"
#include "Tile_Grassland.h"
#include "Primitive Drawing.h"

Tile_Grassland::Tile_Grassland(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z)
	: Tile(grid_x, grid_y, grid_z) // call to super contructor
{
	this->movementCost 	= 0;
	this->stats_offence = 0;
	this->stats_defence = 0;
}

Tile_Grassland::Tile_Grassland() : Tile()
{
	std::cout << "Tile_Grassland - default constructor" << std::endl;
}

Tile_Grassland::~Tile_Grassland()
{

}

void Tile_Grassland::drawTile()
{
	extern GLfloat* green;
	GLfloat* color = green;

	extern GLfloat hexSize_horizontal;
	extern GLfloat hexSize_vertical;
	drawHexagon(coords_hex->operator [](0), coords_hex->operator [](1), coords_hex->operator [](2),
	            hexSize_horizontal, hexSize_vertical,
	            color);
}
