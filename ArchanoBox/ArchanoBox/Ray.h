#ifndef RAY_H_INCLUDE
#define RAY_H_INCLUDE

class Ray
{
	private:
		// close to the camera (at the cliping distance)
		GLfloat close_x;
		GLfloat close_y;
		GLfloat close_z;

		// far from the camera (at the cliping distance)
		GLfloat far_x;
		GLfloat far_y;
		GLfloat far_z;

		GLfloat* color;
	public:
		Ray(GLfloat close_x, GLfloat close_y, GLfloat close_z,
		    GLfloat far_x, GLfloat far_y, GLfloat far_z);
		Ray();
		~Ray();

		GLfloat getClose_x();
		GLfloat getClose_y();
		GLfloat getClose_z();

		GLfloat getFar_x();
		GLfloat getFar_y();
		GLfloat gFar_z();

		void drawRay();
};

#endif
