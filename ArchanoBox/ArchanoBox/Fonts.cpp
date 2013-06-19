#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <string>
#include <sstream>

#include "Fonts.h"

extern GLfloat white[];

GLfloat* fontColor = white;

// all possible bitmap fonts (from OpenGL)
void* font = GLUT_BITMAP_9_BY_15; // default font if nothing is changed
void* fonts[] =
{
	GLUT_BITMAP_8_BY_13,
	GLUT_BITMAP_9_BY_15,

	GLUT_BITMAP_TIMES_ROMAN_10,
	GLUT_BITMAP_TIMES_ROMAN_24,

	GLUT_BITMAP_HELVETICA_10,
	GLUT_BITMAP_HELVETICA_12,
	GLUT_BITMAP_HELVETICA_18
};

// chooses which font to display the information from fonts[] global
// takes an index from 0-6
void selectFont(GLint newfont)
{
	font = fonts[newfont];
	glutPostRedisplay();
}

// Renders the bottom left of the string at pixel coords (x,y). (0,0) is upper left of the screen
// supports decimals
void renderText2D(GLint x, GLint y, std::string string)
{
	glColor3f(fontColor[0], fontColor[1], fontColor[2]);
	glRasterPos2f(x, y);
	for (GLint i = 0; i < string.size(); i++)
	{
		glutBitmapCharacter(font, string.at(i));
	}
}

// changes a float to a string
// 		(supports ints also)
std::string toString_float(GLfloat i)
{
	using namespace std;
	stringstream ss;
	ss << i;
	return ss.str();
}
