#ifndef VECTOR3F_H_INCLUDED
#define VECTOR3F_H_INCLUDED

#include <iostream>

class Vector3f
{
	private:
		float v[3];
	public:
		Vector3f();
		Vector3f(float x, float y, float z);

//		float& operator[](int index); // returns a reference, dangerous! if you want to use this, change name!
		float operator[](int index) const;
		void setValue(int index, float value);

		/* the const after the function means that the function is not allowed to change any
		 * member data fields (no instance variables can be changed by the func), UNLESS that field
		 * is explicitly marked as "mutable"
		 *
		 * http://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
		 */
		Vector3f operator*(float scale) const;
		Vector3f operator/(float scale) const;
		Vector3f operator+(const Vector3f& other) const;
		Vector3f operator-(const Vector3f& other) const;
		Vector3f operator-() const;

		const Vector3f& operator*=(float scale);
		const Vector3f& operator/=(float scale);
		const Vector3f& operator+=(const Vector3f& other);
		const Vector3f& operator-=(const Vector3f& other);

		float magnitude() const;
		float magnitudeSquared() const;
		Vector3f normalize() const;
		float dot(const Vector3f& other) const;
		Vector3f cross(const Vector3f& other) const;
		float distance(Vector3f* other);
		bool equals(Vector3f* other);

		void printStats();
};

Vector3f operator*(float scale, const Vector3f& v);
std::ostream& operator<<(std::ostream& output, const Vector3f& v);

#endif
