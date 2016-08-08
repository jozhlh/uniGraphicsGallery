// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// TextureLoader.cpp
// A class which loads in and stores a texture

#include "TextureLoader.h"

void TextureLoader::LoadTexture(char* filename)
{
	texture = SOIL_load_OGL_texture
		(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y
			);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}