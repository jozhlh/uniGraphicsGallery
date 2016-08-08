// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Lighting.h
// A class which creates all the lights in the scene

#ifndef LIGHTING_H
#define LIGHTING_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"


#define _USE_MATH_DEFINES

#include <math.h>

#define MODEL_LIGHT_SPEED 1
#define MODEL_LIGHT_RADIUS 2

class Lighting
{
public:
	/// PUBLIC FUNCTIONS
	void Sunlight();
	void GridLight();
	void ImageLight();
	void ModelLight(float dt);

private:
	/// PRIVATE FUNCTIONS
	Vector3 model_light_pos;
	Vector3 model_light_look_at;
	float model_light_angle;

};

#endif
