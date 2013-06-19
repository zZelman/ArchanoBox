#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

#include "Vector3f.h"

using namespace std;

Vector3f::Vector3f()
{

}

Vector3f::Vector3f(GLfloat x, GLfloat y, GLfloat z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

//float& Vector_3f::operator[](GLint index) // see .h for explanation on comment
//{
//	return v[index];
//}

GLfloat Vector3f::operator[](GLint index) const
{
	return v[index];
}

void Vector3f::setValue(int index, float value)
{
	v[index] = value;
}

Vector3f Vector3f::operator*(GLfloat scale) const
{
	return Vector3f(v[0] * scale, v[1] * scale, v[2] * scale);
}

Vector3f Vector3f::operator/(GLfloat scale) const
{
	return Vector3f(v[0] / scale, v[1] / scale, v[2] / scale);
}

Vector3f Vector3f::operator+(const Vector3f& other) const
{
	return Vector3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vector3f Vector3f::operator-(const Vector3f& other) const
{
	return Vector3f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vector3f Vector3f::operator-() const
{
	return Vector3f(-v[0], -v[1], -v[2]);
}

const Vector3f& Vector3f::operator*=(GLfloat scale)
{
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Vector3f& Vector3f::operator/=(GLfloat scale)
{
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Vector3f& Vector3f::operator+=(const Vector3f& other)
{
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Vector3f& Vector3f::operator-=(const Vector3f& other)
{
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}

GLfloat Vector3f::magnitude() const
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

GLfloat Vector3f::magnitudeSquared() const
{
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vector3f Vector3f::normalize() const
{
	GLfloat m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return Vector3f(v[0] / m, v[1] / m, v[2] / m);
}

GLfloat Vector3f::dot(const Vector3f& other) const
{
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vector3f Vector3f::cross(const Vector3f& other) const
{
	return Vector3f(v[1] * other.v[2] - v[2] * other.v[1],
	                v[2] * other.v[0] - v[0] * other.v[2],
	                v[0] * other.v[1] - v[1] * other.v[0]);
}

GLfloat Vector3f::distance(Vector3f* other)
{
	return sqrt(pow((v[0] - other->operator [](0)), 2) +
	            pow((v[1] - other->operator [](1)), 2) +
	            pow((v[2] - other->operator [](2)), 2));
}

bool Vector3f::equals(Vector3f* other)
{
	if (v[0] == other->v[0] &&
	        v[1] == other->v[1] &&
	        v[2] == other->v[2])
	{
		return true;
	}
	return false;
}

void Vector3f::printStats()
{
	cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')' << endl;
}

// not a class function
Vector3f operator*(GLfloat scale, const Vector3f& v)
{
	return v * scale;
}

// not a class function
ostream& operator<<(ostream& output, const Vector3f& v)
{
	cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
	return output;
}
