#ifndef TILE_GRASSLAND_H_INCLUDE
#define TILE_GRASSLAND_H_INCLUDE

#include "Tile.h"

class Tile_Grassland: public Tile
{
	private:
	public:
		Tile_Grassland(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z);
		Tile_Grassland();
		~Tile_Grassland();

		void drawTile();
};

#endif
