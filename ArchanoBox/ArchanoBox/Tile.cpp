#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib>

#include "Tile.h"
#include "Primitive Drawing.h"
#include "Calculations.h"
#include "Vector3f.h"

extern GLfloat distEdge;
extern GLfloat hexSize_horizontal;
extern GLfloat hexSize_vertical;

Tile::Tile(GLfloat grid_x, GLfloat grid_y, GLfloat grid_z)
{
	coords_grid = new Vector3f(grid_x, grid_y, grid_z);

	GLfloat temp_x = grid_x;
	GLfloat temp_y = grid_y;
	GLfloat temp_z = grid_z;

	translate_GridToHex_XYZ(temp_x, temp_y, temp_z);

	if (((int) grid_z) % 2 == 0)  // even row
	{
		temp_x += distEdge;
	}

	coords_hex = new Vector3f(temp_x, temp_y, temp_z);
}

Tile::Tile()
{
	std::cout << "Default constructor used: program will now exit" << std::endl;
	exit(0);
}

Tile::~Tile()
{

}

// end condstructor/destructors -------------------------------------------------------------------

GLfloat Tile::getMovementCost()
{
	return this->movementCost;
}

GLfloat Tile::getStats_defence()
{
	return this->stats_defence;
}

GLfloat Tile::getStats_offence()
{
	return this->stats_offence;
}

Vector3f* Tile::getCoords_hex()
{
	return this->coords_hex;
}

Vector3f* Tile::getCoords_grid()
{
	return this->coords_grid;
}

GLfloat Tile::getIndex_grid(GLint index)
{
	return this->coords_grid->operator [](index);
}

GLfloat Tile::getIndex_hex(GLint index)
{
	return this->coords_hex->operator [](index);
}

// end getters ------------------------------------------------------------------------------------

// Return a random float in the range 0.0 to 1.0.
GLfloat Tile::randomFloat()
{
	return (GLfloat)rand() / RAND_MAX;
}

Tile* Tile::returnThis()
{
	return this;
}

// returns the closest point between near and far vectors AND the coords_hex of this tile
bool Tile::intersection(Vector3f A, Vector3f B) // near = A, far = B
{
	// referance: http://www.gamedev.net/topic/221071-simple-raysphere-collision/
	Vector3f AB 		= B.operator - (A);
	GLfloat ab2 		= AB.dot(AB);
	Vector3f AP 		= coords_hex->operator -(A);
	GLfloat ap_dot_ab 	= AP.dot(AB);
	float t         	= ap_dot_ab / ab2; // the projection parameter on the line

	// clamp parameter to segment extremities
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	else if (t > 1.0f)
	{
		t = 1.0f;
	}

	// calculate the closest point
	Vector3f Q = A.operator + (AB.operator * (t));

	/* P represents the hex coords center of the tile in 3D space (inside of the hexagon)
	 *
	 * NOTE: this simplistic collision testing may cause errors if the hexagons are small in height
	 * 		and large in width because the circle is a perfect one, so their will be projections
	 * 		into space above and below the hex!
	 */
	Vector3f* P = new Vector3f(coords_hex->operator [](0), (coords_hex->operator [](1) - 0.5 * hexSize_vertical), coords_hex->operator [](2));
	Vector3f PQ = Q.operator - (*P);
	GLfloat pq2 = PQ.dot(PQ);

	GLfloat r2 = distEdge * distEdge; // size from the center to the edges ( it is < the size to the vertices)
	if (pq2 > r2)
	{
		return false;
	}
	else
	{
		return true;
	}

}

// only checks grid coords!
bool Tile::equals(Tile other)
{
	if (this->coords_grid->operator [](0) == other.coords_grid->operator [](0) &&
	        this->coords_grid->operator [](1) == other.coords_grid->operator [](1) &&
	        this->coords_grid->operator [](2) == other.coords_grid->operator [](2))
	{
		return true;
	}
	return false;
}

// prints variables for debuging purposes
void Tile::printStats()
{
	using namespace std;
	cout << "Tile - Printing stats:" << endl;
	cout << "   location_grid    : (" << coords_grid->operator [](0) << ", " << coords_grid->operator [](1) << ", " << coords_grid->operator [](2) << ")" << endl;
	cout << "   location_hex     : (" << coords_hex->operator [](0) << ", " << coords_hex->operator [](1) << ", " << coords_hex->operator [](2) << ")" << endl;
	cout << "   sizes: horizontal: " << hexSize_horizontal << ", vertical: " << hexSize_vertical << endl;
	cout << "   movementCost     : " << movementCost << endl;
	cout << "   Defense          : " << stats_defence << endl;
	cout << "   Offense          : " << stats_offence << endl << endl;
}

void Tile::drawTile()
{
	std::cout << "tile" << std::endl;
}
