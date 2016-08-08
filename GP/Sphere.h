// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Sphere.h
// A class which procedurally generates a sphere model and renders it

#ifndef _SPHERE_H
#define _SPHERE_H

/// INCLUDES
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>


/// MY CLASS INCLUDES
#include "Vector3.h"
#include "TextureLoader.h"

#define _USE_MATH_DEFINES
#include <math.h>

using std::vector;

class Sphere
{
public:
	/// PUBLIC FUNCTIONS
	void Initialise(float r, int latitude_intervals, int longitude_intervals, char* textureFilename, bool inverse);
	void Render();

private:
	/// PRIVATE FUNCTIONS
	Vector3 Calculate_Coordinates(float t, float d);

	/// PRIVATE VARIABLES
	vector<float> vertices, normals, tex_coords;
	float radius, theta, delta;
	float latitude_angle, longitude_angle;
	float x, y, z;
	Vector3 temp;
	TextureLoader texture;
};
#endif 

