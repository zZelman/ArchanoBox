#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "Ray.h"
#include "Primitive Drawing.h"

// Initializations in primitive drawing.cpp
extern GLfloat yellow[];
extern GLfloat white[];

Ray::Ray(GLfloat close_x, GLfloat close_y, GLfloat close_z,
         GLfloat far_x, GLfloat far_y, GLfloat far_z)
{
	this->close_x = close_x;
	this->close_y = close_y;
	this->close_z = close_z;

	this->far_x = far_x;
	this->far_y = far_y;
	this->far_z = far_z;

//	std::cout << "Ray: created" << std::endl;
}

Ray::Ray()
{
	std::cout << "Ray: default constructor used, program exiting" << std::endl;
	exit(0);
}

Ray::~Ray()
{
//	std::cout << "Ray: destroyed" << std::endl;
}

// end constructors/destructors -------------------------------------------------------------------

GLfloat Ray::getClose_x()
{
	return close_x;
}

GLfloat Ray::getClose_y()
{
	return close_y;
}

GLfloat Ray::getClose_z()
{
	return close_z;
}


GLfloat Ray::getFar_x()
{
	return far_x;
}

GLfloat Ray::getFar_y()
{
	return far_y;
}

GLfloat Ray::gFar_z()
{
	return far_z;
}

// end getters ------------------------------------------------------------------------------------

void Ray::drawRay()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glColor3f(1, 1, 0); // yellow
			glVertex3f(close_x, close_y, close_z);
			glVertex3f(far_x, far_y, far_z);
		}
		glEnd();

		drawSolidCubeCenter(close_x, close_y, close_z,
		                    0.03,
		                    yellow);
		drawSolidCubeCenter(far_x, far_y, far_z,
		                    0.03,
		                    white);
	}
	glPopMatrix();
}

