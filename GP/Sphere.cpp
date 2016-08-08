// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Sphere.cpp
// A class which procedurally generates a sphere model and renders it

#include "Sphere.h"

// generate sphere
void Sphere::Initialise(float r, int latitude_intervals, int longitude_intervals, char* textureFilename, bool inverse)
{
	// load the texture to apply to the sphere
	texture.LoadTexture(textureFilename);

	// calculate intermediates from received arguments
	radius = r;
	latitude_angle = (2 * M_PI) / latitude_intervals;
	longitude_angle = M_PI / longitude_intervals;
	float t_x_interval = 1 / latitude_intervals;
	float t_y_interval = 1 / longitude_intervals;

	// for each longitudinal band
	for (int longitude = 0; longitude < longitude_intervals; longitude++)
	{ 
		// for each latitudal band
		for (int latitude = 0; latitude < latitude_intervals; latitude++)
		{
			// for each vertex of the face (quads so 4 vertices)
			int iterator = 0;
			while (iterator < 4)
			{
				float tX, tY;
				// calculate theta values and texture coordinates
				if ((iterator == 0) | (iterator == 3))
				{
					theta = latitude_angle * latitude;
					tX = t_x_interval * latitude;
					tX = 0;
				}
				else
				{
					theta = latitude_angle * (latitude + 1);
					tX = t_x_interval * (latitude + 1);
					tX = 1;
				}

				// calculate delta values and texture cordinates
				if (iterator < 2)
				{
					delta = longitude_angle * longitude;
					tY = t_y_interval * longitude;
					tY = 0;
				}
				else
				{
					delta = longitude_angle * (longitude + 1);
					tY = t_y_interval * (longitude + 1);
					tY = 1;
				}
				
				// add texture coordinates to tec array
				tex_coords.push_back(tX);
				tex_coords.push_back(tY);

				// calculate vertex position
				temp = Calculate_Coordinates(theta, delta);

				// store vertex position
				vertices.push_back(temp.getX());
				vertices.push_back(temp.getY());
				vertices.push_back(temp.getZ());

				// normalise vertex position for normal
				temp.normalise();

				// if sphere emits light
				if (inverse)
				{
					// store negative normal
					normals.push_back(-temp.getX());
					normals.push_back(-temp.getY());
					normals.push_back(-temp.getZ());
				}
				else
				{
					// store correct normal
					normals.push_back(temp.getX());
					normals.push_back(temp.getY());
					normals.push_back(temp.getZ());
				}
				// nove to the next vertex
				iterator++;
			}
		}
	}
}

// calculate vertex position using parametric equation of a sphere
Vector3 Sphere::Calculate_Coordinates(float t, float d)
{
	x = (radius * cosf(t)) * (sinf(d));
	y = (radius * cosf(d));
	z = (radius * sinf(t)) * sinf(d);

	return Vector3(x, y, z);
}

// render stored vertex arrays
void Sphere::Render()
{
	// make sure correct texture is bound
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coords.data());
	glVertexPointer(3, GL_FLOAT, 0, vertices.data());

	glDrawArrays(GL_QUADS, 0, (vertices.size() / 3));

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}