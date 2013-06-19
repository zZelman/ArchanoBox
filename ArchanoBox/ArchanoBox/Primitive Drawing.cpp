#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include "Primitive Drawing.h"

// colors
GLfloat red[] 			= { 1.0, 0.0, 0.0, 1.0 };
GLfloat green[] 		= { 0.0, 1.0, 0.0, 1.0 };
GLfloat green_light[]	= { 0.0, 1.0, 0.6, 1.0 };
GLfloat blue[] 			= { 0.0, 0.0, 1.0, 1.0 };
GLfloat white[]			= { 1.0, 1.0, 1.0, 1.0 };
GLfloat grey[]			= { 0.5, 0.5, 0.5, 1.0 };
GLfloat brown[]			= { 0.5, 0.35, 0.05, 1.0 };
GLfloat yellow[]		= { 1.0, 1.0, 0.0, 1.0 };

void drawSolidCubeCenter(GLfloat x, GLfloat y, GLfloat z,
                         GLfloat size,
                         GLfloat* color)
{
	if (sizeof(color) != 4)
	{
		std::cout << "drawSolidCube() error: color array not correct size";
		exit(0);
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glColor3f(color[0], color[1], color[2]);
		GLfloat newSize = size / 2;
		glBegin(GL_QUADS);
		{
			// drawn top left, top right, botom right, botom left

			// bottom
			glVertex3f(x - newSize, y - newSize, z - newSize);
			glVertex3f(x + newSize, y - newSize, z - newSize);
			glVertex3f(x + newSize, y - newSize, z + newSize);
			glVertex3f(x - newSize, y - newSize, z + newSize);

			// top
			glVertex3f(x - newSize, y + newSize, z - newSize);
			glVertex3f(x + newSize, y + newSize, z - newSize);
			glVertex3f(x + newSize, y + newSize, z + newSize);
			glVertex3f(x - newSize, y + newSize, z + newSize);

			// right
			glVertex3f(x + newSize, y + newSize, z - newSize);
			glVertex3f(x + newSize, y + newSize, z + newSize);
			glVertex3f(x + newSize, y - newSize, z + newSize);
			glVertex3f(x + newSize, y - newSize, z - newSize);

			// left
			glVertex3f(x - newSize, y + newSize, z - newSize);
			glVertex3f(x - newSize, y + newSize, z + newSize);
			glVertex3f(x - newSize, y - newSize, z + newSize);
			glVertex3f(x - newSize, y - newSize, z - newSize);

			// front
			glVertex3f(x - newSize, y + newSize, z + newSize);
			glVertex3f(x + newSize, y + newSize, z + newSize);
			glVertex3f(x + newSize, y - newSize, z + newSize);
			glVertex3f(x - newSize, y - newSize, z + newSize);

			// back
			glVertex3f(x - newSize, y + newSize, z - newSize);
			glVertex3f(x + newSize, y + newSize, z - newSize);
			glVertex3f(x + newSize, y - newSize, z - newSize);
			glVertex3f(x - newSize, y - newSize, z - newSize);
		}
		glEnd();
	}
	glPopMatrix();
}

void drawSolidCubeBottom(GLfloat x, GLfloat y, GLfloat z,
                         GLfloat size,
                         GLfloat* color)
{
	if (sizeof(color) != 4)
	{
		std::cout << "drawSolidCube() error: color array not correct size" << std::endl;
		exit(0);
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glColor3f(color[0], color[1], color[2]);
		GLfloat newSize = size / 2;
		glBegin(GL_QUADS);
		{
			// drawn top left, top right, botom right, botom left

			// bottom
			glVertex3f(x - newSize, y, z - newSize);
			glVertex3f(x + newSize, y, z - newSize);
			glVertex3f(x + newSize, y, z + newSize);
			glVertex3f(x - newSize, y, z + newSize);

			// top
			glVertex3f(x - newSize, y + size, z - newSize);
			glVertex3f(x + newSize, y + size, z - newSize);
			glVertex3f(x + newSize, y + size, z + newSize);
			glVertex3f(x - newSize, y + size, z + newSize);

			// right
			glVertex3f(x + newSize, y + size, z - newSize);
			glVertex3f(x + newSize, y + size, z + newSize);
			glVertex3f(x + newSize, y, z + newSize);
			glVertex3f(x + newSize, y, z - newSize);

			// left
			glVertex3f(x - newSize, y + size, z - newSize);
			glVertex3f(x - newSize, y + size, z + newSize);
			glVertex3f(x - newSize, y, z + newSize);
			glVertex3f(x - newSize, y, z - newSize);

			// front
			glVertex3f(x - newSize, y + size, z + newSize);
			glVertex3f(x + newSize, y + size, z + newSize);
			glVertex3f(x + newSize, y, z + newSize);
			glVertex3f(x - newSize, y, z + newSize);

			// back
			glVertex3f(x - newSize, y + size, z - newSize);
			glVertex3f(x + newSize, y + size, z - newSize);
			glVertex3f(x + newSize, y, z - newSize);
			glVertex3f(x - newSize, y, z - newSize);
		}
		glEnd();
	}
	glPopMatrix();
}

// draw axises x,y,z
// draw coord markers on the axis
void drawGrid()
{
	GLfloat posLineSize	= 10000;
	GLfloat negLineSize = -10000;
	GLfloat markSize	= .08;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
    	   /* There should be a colored axis system.
    		* Red is x, Green is y, and Blue is z.
    		* 
    		* White  markers mean positive axis
    		* Brown markers mean negative axis
    		*/

			// x axis
			glColor3f(red[0], red[1], red[2]);
			glVertex3f(negLineSize, 0, 0);
			glVertex3f(posLineSize, 0, 0);

			// y axis
			glColor3f(green[0], green[1], green[2]);
			glVertex3f(0, negLineSize, 0);
			glVertex3f(0, posLineSize, 0);

			// z axis
			glColor3f(blue[0], blue[1], blue[2]);
			glVertex3f(0, 0, negLineSize);
			glVertex3f(0, 0, posLineSize);
		}
		glEnd();

		// coord markers
		for (GLfloat i = 0; i <= posLineSize; ++i) // positive axis
		{
			drawSolidCubeCenter(i, 0, 0, markSize, white);
			drawSolidCubeCenter(0, i, 0, markSize, white);
			drawSolidCubeCenter(0, 0, i, markSize, white);
		}

		drawSolidCubeCenter(0, 0, 0, markSize, white); // origin

		for (GLfloat i = 0; i >= negLineSize; --i) // negitive axis
		{
			drawSolidCubeCenter(i, 0, 0, markSize, brown);
			drawSolidCubeCenter(0, i, 0, markSize, brown);
			drawSolidCubeCenter(0, 0, i, markSize, brown);
		}
	}
	glPopMatrix();
}

// draws a pointy-topped hexagon at (x,y,z) with <size> and <height>
// <size> is from the center to the corners, <height> is from the top hex to the bottom hex (rectangles form the walls)
// drawn in the x-z plane with y as the height
// the given coordinates represent the center of the bottom 2D hexagon, the top is drawn <height> away from it in the y direction
void drawHexagon(GLfloat center_x, GLfloat center_y, GLfloat center_z,
                 GLfloat size, GLfloat height,
                 GLfloat* color)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glColor3f(color[0], color[1], color[2]);
		GLfloat firstHex[6][3];
		GLfloat secondHex[6][3];
		glBegin(GL_POLYGON);
		{
			for (GLint i = 0; i < 6; i++)
			{
				GLfloat angle = 2 * PI / 6 * (i + 0.5);
				GLfloat x_tempVertex = center_x + size * cos(angle);
				GLfloat z_tempVertex = center_z + size * sin(angle);
				firstHex[i][0] = x_tempVertex;
				firstHex[i][1] = center_y;
				firstHex[i][2] = z_tempVertex;
				glVertex3f(x_tempVertex, center_y, z_tempVertex);
			}
		}
		glEnd();

		glBegin(GL_POLYGON);
		{
			for (GLint i = 0; i < 6; i++)
			{
				GLfloat angle = 2 * PI / 6 * (i + 0.5);
				GLfloat x_tempVertex = center_x + size * cos(angle);
				GLfloat z_tempVertex = center_z + size * sin(angle);
				secondHex[i][0] = x_tempVertex;
				secondHex[i][1] = center_y - height;
				secondHex[i][2] = z_tempVertex;
				glVertex3f(x_tempVertex, center_y - height, z_tempVertex);
			}
		}
		glEnd();

		// Begin filling the rectangles between the two hexagons
		// drawing begins at ( 0, 0, 0 ) and moves clockwise
		//					 ( 0, 0, 1 ) [the mid single coord in each set represents the middle point up/down respectivly]
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		{
			for (GLint i = 0; i < 5; i++)
			{
				glVertex3f(firstHex[i][0], firstHex[i][1], firstHex[i][2]); // top left
				glVertex3f(secondHex[i][0], secondHex[i][1], secondHex[i][2]); // bottom left
				glVertex3f(secondHex[i + 1][0], secondHex[i + 1][1], secondHex[i + 1][2]); // top right
				glVertex3f(firstHex[i + 1][0], firstHex[i + 1][1], firstHex[i + 1][2]); // bottom right
			}

			// corner case (connecting the end to the beginning)
			glVertex3f(firstHex[5][0], firstHex[5][1], firstHex[5][2]); // top left
			glVertex3f(secondHex[5][0], secondHex[5][1], secondHex[5][2]); // bottom left
			glVertex3f(secondHex[0][0], secondHex[0][1], secondHex[0][2]); // top right
			glVertex3f(firstHex[0][0], firstHex[0][1], firstHex[0][2]); // bottom right
		}
		glEnd();
	}
	glPopMatrix();
}

// colored triangle test
void drawTestTriangle()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glBegin(GL_POLYGON);
		{
			glColor3f(1, 0, 0);
			glVertex3f(-0.6, -0.75, 0.5);

			glColor3f(0, 1, 0);
			glVertex3f(0.6, -0.75, 0);

			glColor3f(0, 0, 1);
			glVertex3f(0, 0.75, 0);
		}
		glEnd();
	}
	glPopMatrix();
}
