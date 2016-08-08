// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Geometry.h
// A class which draws basic geometry in the scene

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "TextureLoader.h"
#include "Model.h"

#define IMAGE_MOVE_SPEED 50
#define MODEL_SPIN_SPEED 5

class Geometry
{
public:
	/// PUBLIC FUNCTIONS
	void Initialise();
	void DrawGeometry(float dt);

	/// PUBLIC VAARIABLES
	bool paused;

private:
	/// PRIVATE FUNCTIONS
	void CreateCage();
	void Oblong(float x, float y, float z);
	void DrawRoom(float width, float height, float length);
	void DrawSolarPlinth(float width, float height, float length);
	void DrawModelPlinth(float width, float height, float length);
	void DrawFrame();
	void DrawImage(float dt);
	void ModelReflection(float dt);

	/// PRIVATE VARIABLES
	TextureLoader image, wall, floor;
	GLuint grid_list;
	Model model;
	float image_rotation;
	float model_rotation;
	float rotation;
};

#endif
