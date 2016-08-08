// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// TextureLoader.h
// A class which loads in and stores a texture

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <windows.h>
#include "SOIL.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <cstdio>

class TextureLoader
{
public:
	void LoadTexture(char* filename);
	GLuint texture;
};

#endif