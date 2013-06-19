#ifndef TILE_H_INCLUDE
#define TILE_H_INCLUDE

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Vector3f.h"

class Tile
{
	protected:
		GLfloat movementCost;
		GLfloat stats_defence;
		GLfloat stats_offence;

		Vector3f* coords_hex;
		// the position in grid coordinates
		// IMPORTANT NOTE: these coords do not map directly onto the Cartesian system,
		// 		instead they represent where on the BOARD the piece is.
		//		Top left is the origin @ (0,0,0) if there is only one tile.
		//		0 in the y represents the base tile.
		//		THESE VALUES CANNOT BE NEGITIVE, AND MUST BE WHOLE NUMBERS
		Vector3f* coords_grid;

	public:
		Tile(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z); // all other stats are taken care of by the sub class (hard coded)
		Tile();
		virtual ~Tile();

		GLfloat getMovementCost();
		GLfloat getStats_defence();
		GLfloat getStats_offence();

		Vector3f* getCoords_hex();
		Vector3f* getCoords_grid();

		GLfloat getIndex_grid(GLint index);
		GLfloat getIndex_hex(GLint index);

		GLfloat getSize_horizontal();
		GLfloat getSize_vertical();


		GLfloat randomFloat();
		Tile* returnThis();

		bool intersection(Vector3f A, Vector3f B);	// returns true if ray from A to B intersects this tile
		bool equals(Tile other); // checks the values of grid coords for equality
		void printStats();

		// TODO: have each subclass draw their own blender-model tile
		virtual void drawTile();
};

#endif
