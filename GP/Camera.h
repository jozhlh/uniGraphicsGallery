// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Camera.h
// A class which handles camera controls and calculations

#ifndef CAMERA_H
#define CAMERA_H

/// MY CLASS INCLUDES
#include "Vector3.h"
#include "Input.h"
#include "TextureLoader.h"

#define CAMERA_SENSITIVITY		150
#define MOVEMENT_SPEED			1000
#define CAMERA_RADIUS			8
#define CAMERA_SPIN_SPEED		0.5

class Camera
{
public:
	/// PUBLIC FUNCTIONS
	void Initialise(char* skybox_filename);
	void InitialiseModelCamera();
	void RenderCamera(float dt, Input* in_, RECT* screen_rect_, HWND hwnd);
	void RenderModelCamera(float dt);

private:
	/// PRIVATE FUNCTIONS
	void Update();
	void UpdateModelCamera(float dt);
	void Skybox();
	void GetCameraInput(float dt, Input* in_, RECT* screen_rect_);

	/// PRIVATE VARIABLES
	RECT* screen_size_;
	Input* input_;
	Vector3 position, forward, up, look_at, ftemp, right;
	TextureLoader skybox;
	float roll, pitch, yaw;
	float screen_centre_x, screen_centre_y;
	float angle;
	int mouse_moved_x, mouse_moved_y;

};

#endif