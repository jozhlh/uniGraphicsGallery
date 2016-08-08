// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Model.h
// A class which handles model importing and rendering

#ifndef _MODEL_H_
#define _MODEL_H_

/// INCLUDES
#include <Windows.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>

/// MY CLASS INCLUDES
#include "TokenStream.h"
#include "Vector3.h"
#include "TextureLoader.h"

using namespace std;

class Model
{
public:
	/// PUBLIC FUNCTIONS
	bool Load(char*, char*);
	void Render();
	
private:
	/// PRIVATE FUNCTIONS
	bool LoadModel(char*);
	
	/// PRIVATE VARIABLES
	int vertex_count;
	TextureLoader texture;
	vector<float> vertex, normals, tex_coords;
};

#endif