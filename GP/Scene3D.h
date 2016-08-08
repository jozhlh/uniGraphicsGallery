// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Scene3D.h
// A class which controls the OpenGL scene

#ifndef SCENE3D_H
#define SCENE3D_H

/// INCLUDES
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <list>
#include <gl/gl.h>
#include <gl/glu.h>

/// MY CLASS INCLUDES
#include "Input.h"
#include "Vector3.h"
#include "Camera.h"
#include "Model.h"
#include "Sphere.h"
#include "Lighting.h"
#include "SolarSystem.h"
#include "Geometry.h"

#define _USE_MATH_DEFINES

#include <math.h>

#define COLOUR_DEPTH 16

using std::list;

class Scene3D
{
public:
	/// PUBLIC FUNCTIONS
	void Init(HWND* hwnd, Input* in);
	void Update(float dt);
	void Resize();
	
protected:
	/// PRIVATE FUNCTIONS
	bool CreatePixelFormat(HDC hdc);
	void ResizeGLWindow(int width, int height);
	void InitializeOpenGL(int width, int height);
	void Render(float dt);
	
	/// PRIVATE VARIABLES
	Geometry objects;
	SolarSystem planets;
	Lighting lights;
	Camera camera;
	Camera model_camera;
	RECT screenRect;
	HWND* hwnd;
	Input* input;
	HDC	hdc;
	HGLRC hrc;			//hardware RENDERING CONTEXT
	int current_camera;
};

#endif