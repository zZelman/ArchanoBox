#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>

#include "Calculations.h"

// initializations in main.cpp
extern GLfloat hexSize_horizontal;
extern GLfloat offset;
extern GLfloat zOffset;
extern GLfloat distEdge;
extern GLfloat startCoords_x;
extern GLfloat startCoords_z;

// manipulates the values of (x,y,z) from hex to grid coords
// after this function is called, the (x,y,z) are in grid coords (because they are referenced)
// Note: too many successive translations may result in a rounding error
void translate_HexToGrid_XYZ(GLfloat& x, GLfloat& y, GLfloat& z)
{
	translate_HexToGrid_X(x);
	translate_HexToGrid_Y(y);
	translate_HexToGrid_Z(z);
}

void translate_HexToGrid_X(GLfloat& x)
{
	x = (cos(0.523598776) * x - startCoords_x) / (2 * hexSize_horizontal * offset);
}

void translate_HexToGrid_Y(GLfloat& y)
{
//	std::cout<< "Calculations: algorithum to set y not determined" << std::endl;
}

void translate_HexToGrid_Z(GLfloat& z)
{
	z = (cos(0.523598776) * z - startCoords_x) / (2 * hexSize_horizontal * offset * zOffset);
}

// end translating hex->grid ----------------------------------------------------------------------

// manipulates the values of (x,y,z) from grid to hex coords
// after this function is called, the (x,y,z) are in hex coords (because they are referenced)
// Note: too many successive translations may result in a rounding error

// formula: [starting point] + (([current index from starting] * 2) * ([size of hex to vertex] / cos(0.523598776))) * offSet
// 0.523598776 because cos is done in radians (that equals 30 degrees)

void translate_GridToHex_XYZ(GLfloat& x, GLfloat& y, GLfloat& z)
{
	translate_GridToHex_X(x);
	translate_GridToHex_Y(y);
	translate_GridToHex_Z(z);
}

void translate_GridToHex_X(GLfloat& x)
{
	x = (startCoords_x) + ((x * 2) * distEdge) * offset;
}

void translate_GridToHex_Y(GLfloat& y)
{
//	std::cout << "Calculations: algorithum to set y not determined" << std::endl;
}

void translate_GridToHex_Z(GLfloat& z)
{
	z = (startCoords_z) + ((z * 2) * distEdge) * zOffset * offset;
}

// end translating grid->hex ----------------------------------------------------------------------
