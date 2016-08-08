// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Vector.h
// A class which provides geometrical vector functionality

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>
#include <cmath>
 
class Vector3{

public:
    Vector3(float x = 0, float y = 0, float z = 0);
    Vector3 copy();
 
 
    void set(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

	float getX();
	float getY();
	float getZ();
 
    void add(const Vector3& v1, float scale=1.0);
    void subtract(const Vector3& v1, float scale=1.0);
    void scale(float scale);
 
    float dot(const Vector3& v2);
    Vector3 cross(const Vector3& v2);
 
    void normalise();
    float length();
    float lengthSquared();
 
    bool equals(const Vector3& v2, float epsilon);
	bool equals(const Vector3& v2);
 
    Vector3 operator+(const Vector3& v2);
    Vector3 operator-(const Vector3& v2);
 
    Vector3& operator+=(const Vector3& v2);
    Vector3& operator-=(const Vector3& v2);

private:
    float x;
	float y;
	float z;
};

#endif