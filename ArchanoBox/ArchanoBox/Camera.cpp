#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>

#include "Camera.h"

Camera::Camera(GLint x, GLint y, GLint z,
               GLint look_x, GLint look_y, GLint look_z,
               GLfloat dx, GLfloat dy, GLfloat dz,
               GLfloat angle, GLfloat dAngle)
{
	// Initial location
	this->camera_position = new Vector3f(x, y, z);

	// Initial looking at
	this->camera_looking = new Vector3f(look_x, look_y, look_z);

	// bool values to change camera angle
	isLooking_Xpos = false;
	isLooking_Xneg = false;
	isLooking_Zpos = false;
	isLooking_Zneg = false;

	// amount to change each key-press
	this->dx = dx;
	this->dy = dy;
	this->dz = dz;

	// camera angle and change amount
	this->angle = angle;
	this->dAngle = dAngle;

//	std::cout << "Camera created" << std::endl;
}

Camera::Camera()
{
	std::cout << "Camera default constructor used. Program exiting" << std::endl;
	exit(0);
}

Camera::~Camera()
{
//	std::cout << "Camera destroyed" << std::endl;
}

// end condstructor/destructors -------------------------------------------------------------------

Vector3f* Camera::getCamera_position()
{
	return this->camera_position;
}

Vector3f* Camera::getCamera_looking()
{
	return this->camera_looking;
}

GLfloat Camera::getIndex_position(GLint index)
{
	return this->camera_position->operator [](index);
}

GLfloat Camera::getIndex_looking(GLint index)
{
	return this->camera_looking->operator [](index);
}

GLfloat Camera::getAngle()
{
	return angle;
}

// end getters ------------------------------------------------------------------------------------

// looking +x
void Camera::look_Xpos()
{
	// bool values to change camera angle
	isLooking_Xpos = false;
	isLooking_Xneg = false;
	isLooking_Zpos = false;
	isLooking_Zneg = false;

	camera_looking->setValue(0, camera_position->operator [](0) + -1 / tan((double) this->angle));
	camera_looking->setValue(1, camera_position->operator [](1) - 1);
	camera_looking->setValue(2, camera_position->operator [](2));

	isLooking_Xpos = true;
}

// looking -x
void Camera::look_Xneg()
{
	// bool values to change camera angle
	isLooking_Xpos = false;
	isLooking_Xneg = false;
	isLooking_Zpos = false;
	isLooking_Zneg = false;

	camera_looking->setValue(0, camera_position->operator [](0) - -1 / tan((double) this->angle));
	camera_looking->setValue(1, camera_position->operator [](1) - 1);
	camera_looking->setValue(2, camera_position->operator [](2));

	isLooking_Xneg = true;
}

// looking -z
void Camera::look_Zneg()
{
	// bool values to change camera angle
	isLooking_Xpos = false;
	isLooking_Xneg = false;
	isLooking_Zpos = false;
	isLooking_Zneg = false;

	camera_looking->setValue(0, camera_position->operator [](0));
	camera_looking->setValue(1, camera_position->operator [](1) - 1);
	camera_looking->setValue(2, camera_position->operator [](2) - -1 / tan((double) this->angle));

	isLooking_Zneg = true;
}

// looking +z
void Camera::look_Zpos()
{
	// bool values to change camera angle
	isLooking_Xpos = false;
	isLooking_Xneg = false;
	isLooking_Zpos = false;
	isLooking_Zneg = false;

	camera_looking->setValue(0, camera_position->operator [](0));
	camera_looking->setValue(1, camera_position->operator [](1) - 1);
	camera_looking->setValue(2, camera_position->operator [](2) + -1 / tan((double) this->angle));

	isLooking_Zpos = true;

}

// increment camera angle
void Camera::look_up()
{
	angle += dAngle;

	// all other functions are dependent on angle
	// just posting a redisplay w/o more user input
	if (isLooking_Xpos)
	{
		look_Xpos();
	}
	else if (isLooking_Xneg)
	{
		look_Xneg();
	}
	else if (isLooking_Zpos)
	{
		look_Zpos();
	}
	else if (isLooking_Zneg)
	{
		look_Zneg();
	}
}

// decrement camera angle
void Camera::look_down()
{
	angle -= dAngle;

	// all other functions are dependent on angle
	// just posting a redisplay w/o more user input
	if (isLooking_Xpos)
	{
		look_Xpos();
	}
	else if (isLooking_Xneg)
	{
		look_Xneg();
	}
	else if (isLooking_Zpos)
	{
		look_Zpos();
	}
	else if (isLooking_Zneg)
	{
		look_Zneg();
	}
}

// +x strafing
void Camera::shift_Xpos()
{
	camera_position->setValue(0, camera_position->operator [](0) + dx);
	camera_looking->setValue(0, camera_looking->operator [](0) + dx);
}

// -x strafing
void Camera::shift_Xneg()
{
	camera_position->setValue(0, camera_position->operator [](0) - dx);
	camera_looking->setValue(0, camera_looking->operator [](0) - dx);
}

// +y strafing
void Camera::shift_Ypos()
{
	camera_position->setValue(1, camera_position->operator [](1) + dy);
	camera_looking->setValue(1, camera_looking->operator [](1) + dy);
}

// -y strafing
void Camera::shift_Yneg()
{
	camera_position->setValue(1, camera_position->operator [](1) - dy);
	camera_looking->setValue(1, camera_looking->operator [](1) - dy);
}

// +z strafing
void Camera::shift_Zpos()
{
	camera_position->setValue(2, camera_position->operator [](2) + dz);
	camera_looking->setValue(2, camera_looking->operator [](2) + dz);
}

// -z strafing
void Camera::shift_Zneg()
{
	camera_position->setValue(2, camera_position->operator [](2) - dz);
	camera_looking->setValue(2, camera_looking->operator [](2) - dz);
}

// debug printing
void Camera::printPosAndLook()
{
	std::cout << "Camera - printing stats:" << std::endl;
	std::cout << "   location: (" << camera_position->operator [](0) << ", " << camera_position->operator [](1) << ", " << camera_position->operator [](2) << ")" << std::endl;
	std::cout << "   looking : (" << camera_looking->operator [](0) << ", " << camera_looking->operator [](1) << ", " << camera_looking->operator [](2) << ")" << std::endl;
	std::cout << "   angle   : " << angle << std::endl << std::endl;
}
