// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// SolarSystem.h
// A class which creates, updates and renders the solar system model

#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "TextureLoader.h"
#include "Sphere.h"

#define PLANET_SPIN_SPEED 2
#define PLANET_MOVE_SPEED 15.0

class SolarSystem
{
public:
	/// PUBLIC FUNCTIONS
	void Initialise(char* sun_textureFilename, char* planet_textureFilename);
	void Update(float scale, float dt);

private:
	/// PRIVATE VARIABLES
	Sphere sun;
	Sphere planet;
	float planet_spin;
	float rotation[3];

};

#endif