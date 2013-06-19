#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Vector3f.h"

class Camera
{
	private:
		// current position
		Vector3f* camera_position;

		// looking At
		Vector3f* camera_looking;

		// bool values to change camera angle
		bool isLooking_Xpos, isLooking_Xneg,
		     isLooking_Zpos, isLooking_Zneg;

		// camera angle & change
		GLfloat angle, dAngle;

		// move amounts
		GLfloat dx, dy, dz;
	public:
		// Initial location and change amount
		Camera(GLint camera_x, GLint camera_y, GLint camera_z,
		       GLint look_x, GLint look_y, GLint look_z,
		       GLfloat dx, GLfloat dy, GLfloat dz,
		       GLfloat angle, GLfloat dAngle);
		~Camera();
		Camera();

		// getters
		Vector3f* getCamera_position();
		Vector3f* getCamera_looking();

		GLfloat getIndex_position(GLint index);
		GLfloat getIndex_looking(GLint index);
		GLfloat getAngle();

		// camera control - fixed positions based off of camera->angle
		void look_Xpos();		// looking +x
		void look_Xneg();		// looking -x
		void look_Zneg();		// looking -z
		void look_Zpos();		// looking +z
		void look_up();			// looking +y
		void look_down();		// looking -y

		// camera control - strafing
		void shift_Xpos();		// +x strafing
		void shift_Xneg();		// -x strafing
		void shift_Ypos();		// +y strafing
		void shift_Yneg();		// -y strafing
		void shift_Zpos();		// +z strafing
		void shift_Zneg();		// -z strafing

		// debug printing
		void printPosAndLook();
};


#endif
