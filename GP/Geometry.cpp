// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Geometry.cpp
// A class which draws basic geometry in the scene

#include "Geometry.h"

// intitialises objects
void Geometry::Initialise()
{
	// create display list for grid
	CreateCage();
	
	// load model and model texture
	model.Load("Models/teapot.obj", "Models/crate.png");

	// load other objects' textures
	image.LoadTexture("trippy.png");
	floor.LoadTexture("wood_floor_texture.png");
	wall.LoadTexture("white_wall_texture.png");
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// initialise variables
	model_rotation = 0;
	paused = false;
}

// public interface to call all drawing functions
void Geometry::DrawGeometry(float dt)
{
	DrawRoom(16.0, 16.0, 80.0);

	// disable textures for solid shapes
	glDisable(GL_TEXTURE_2D);
	DrawSolarPlinth(16.0, 2.0, 16.0);
	DrawModelPlinth(8.0, 4.0, 8.0);
	glCallList(grid_list);

	// enable textures again
	glEnable(GL_TEXTURE_2D);
	DrawImage(dt);
	DrawFrame();
	ModelReflection(dt);
}

// draws the gallery space
void Geometry::DrawRoom(float height, float width, float length)
{
	float z_negative = length / 5;
	float z_positive = length * 0.8;
	float x = 1.0;
	float y = 1.0;
	float z = 1.0;

	// walls and ceiling are solid on the inside but wireframe from the outside
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	// binds wall texture
	glBindTexture(GL_TEXTURE_2D, wall.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glPushMatrix();
	glBegin(GL_TRIANGLES);//Begin drawing state
						  //front face I
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x * -width, y * 0.0, z * -z_negative);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(x * width, y * height, z * -z_negative);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x * -width, y * height, z * -z_negative);

	//front face II
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x * -width, y * 0.0, z * -z_negative);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(x * width, y * 0.0, z * -z_negative);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(x * width, y * height, z * -z_negative);

	//top face I
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(x *-width, y * height, z * -z_negative);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(x * width, y * height, z * z_positive);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 5.0f);
	glVertex3f(x *-width, y * height, z * z_positive);

	//top face II
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(x *-width, y * height, z * -z_negative);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x * width, y * height, z * -z_negative);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(x * width, y * height, z * z_positive);

	//back face I
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(2.0f, 2.0f);
	glVertex3f(x * width, y * 0.0, z * z_positive);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x * -width, y * height, z * z_positive);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(2.0f, 1.0f);
	glVertex3f(x * width, y * height, z * z_positive);

	//back face II
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(x * width, y * 0.0, z * z_positive);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x * -width, y * 0.0, z * z_positive);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x * -width, y * height, z * z_positive);

	//left face I
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(x * -width, y * 0.0, z * z_positive);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x * -width, y * height, z * -z_negative);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0f, 1.0f);
	glVertex3f(x * -width, y * height, z * z_positive);

	//left face II
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(x * -width, y * 0.0, z * z_positive);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x * -width, y * 0.0, z * -z_negative);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x * -width, y * height, z * -z_negative);

	//right face I
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(x * width, y * 0.0, z * -z_negative);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x * width, y * height, z * z_positive);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0f, 1.0f);
	glVertex3f(x * width, y * height, z * -z_negative);

	//right face II
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f);
	glVertex3f(x * width, y * 0.0, z * -z_negative);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x * width, y * 0.0, z * z_positive);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x * width, y * height, z * z_positive);
	glEnd();

	// the floor is solid from above and below
	glPolygonMode(GL_BACK, GL_FILL);

	// bind floor texture
	glBindTexture(GL_TEXTURE_2D, floor.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_TRIANGLES);
	//bottom face I
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(x * -width, y * 0.0, z * z_positive);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(x * width, y * 0.0, z * -z_negative);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x * -width, y * 0.0, z * -z_negative);

	//bottom face II
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f);
	glVertex3f(x * -width, y * 0.0, z * z_positive);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(2.0f, 5.0f);
	glVertex3f(x * width, y * 0.0, z * z_positive);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(x * width, y * 0.0, z * -z_negative);
	glEnd();

	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// draw box beneath solar system
void Geometry::DrawSolarPlinth(float width, float height, float length)
{
	// set render mode to ensure faces are facing the correct direction
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	// set colour to white
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		// move to correct location in scene and draw
		glTranslatef(0.0, 1.0, 40.0);
		Oblong(width, height, length);
	glPopMatrix();
}

// draw box beneath model
void Geometry::DrawModelPlinth(float width, float height, float length)
{
	// set render mode to ensure faces are facing the correct direction
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	// set colour to white
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		// move to correct location in scene and draw
		glTranslatef(0.0, 2.0, 12.0);
		Oblong(width, height, length);
	glPopMatrix();
}

// creates a display list for the pink wireframe grid
void Geometry::CreateCage()
{
	// create new display list for grid with a large number of vertices
	grid_list = glGenLists(1);
	glNewList(grid_list, GL_COMPILE);

	// set to wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// set to magenta
	glColor3f(1.0f, 0.0f, 0.3f);
	glPushMatrix();
		// move to correct location in scene
		glTranslatef(1.0, 9.0, -13.05);

		// draw each box by rows and columns and a depth of 2
		for (float i = -7; i < 7; i++)
		{
			for (float j = -3; j < 3; j++)
			{
				for (float k = -1; k < 1; k++)
				{
					glPushMatrix();
						// draw box in the correct place in the grid
						glTranslatef(2 * i, 2 * j, 2 * k);
						Oblong(2.0, 2.0, 2.0);
					glPopMatrix();
				}
			}
		}
	glPopMatrix();
	// turn off wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// set colour back to white
	glColor3f(1.0f, 1.0f, 1.0f);

	// finished creating grid
	glEndList();
}

// draws a black frame around the spinning image
void Geometry::DrawFrame()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// set colour to black
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		// move to the frame's location
		glTranslatef(0.0, 0.0, 63.5);
		glPushMatrix();
			// draw the bottom side
			glTranslatef(0.0, 1.5, 0.0);
			Oblong(14.0, 1.0, 1.0);
		glPopMatrix();
		glPushMatrix();
			// draw the top side
			glTranslatef(0.0, 14.5, 0.0);
			Oblong(14.0, 1.0, 1.0);
		glPopMatrix();
		glPushMatrix();
			// draw the left side
			glTranslatef(-6.5, 8.0, 0.0);
			Oblong(1.0, 14.0, 1.0);
		glPopMatrix();
		glPushMatrix();
			// draw the right side
			glTranslatef(6.5, 8.0, 0.0);
			Oblong(1.0, 14.0, 1.0);
		glPopMatrix();
	glPopMatrix();

	// set the colour back to white
	glColor3f(1.0f, 1.0f, 1.0f);
}

// updates the rotation of the spinning image and draws it
void Geometry::DrawImage(float dt)
{
	float x = 6.5f;
	float y = 6.5f;

	// select correct texture and wrap it in the u anv v directions (s and t)
	glBindTexture(GL_TEXTURE_2D, image.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// if the user has not paused, increase the rotation of the image
	if (!paused)
	{
		rotation += (IMAGE_MOVE_SPEED) * dt;
		image_rotation += (rotation * dt);
	}

	// switch to texture matrix
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
		// apply texture transformation
		glTranslatef(1, 1, 0);
		glRotatef(image_rotation, 0, 0, 1);
		glTranslatef(-1, -1, 0);
		
		// switch back to model matrix
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			// move image to corrrect location
			glTranslatef(0.0, 8.0, 63.5);
			glBegin(GL_QUADS);
				// draw image plane
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f((x*-1.0f), y, 0.0f);

				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 2.0f);
				glVertex3f((x*-1.0f), (y*-1.0f), 0.0f);

				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(2.0f, 2.0f);
				glVertex3f(x, (y*-1.0f), 0.0f);

				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(2.0f, 0.0f);
				glVertex3f(x, y, 0.0f);
			glEnd();
		glPopMatrix();
	// switch back to texture matrix to remove the transformation matrix (so other textures are unaffected)
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

	// switch back to model matrix
	glMatrixMode(GL_MODELVIEW);
}

// draws the model, mirror and reflection of the model
void Geometry::ModelReflection(float dt)
{
	// rotate the model
	model_rotation += (MODEL_SPIN_SPEED * dt);

	glEnable(GL_STENCIL_TEST);
	// we aren't rendering to the frame so always pass the stencil test, to write to stencil
	glStencilFunc(GL_ALWAYS, 1, 1);												
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);

	// set colour to white
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
		// move to model feature's location in scene
		glTranslatef(0.0, 4.05, 12.0);

		// draw mirror object
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-4.0f, 0.0f, -4.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(4.0f, 0.0f, -4.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(4.0f, 0.0f, 4.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-4.0f, 0.0f, 4.0f);
		glEnd();

		glEnable(GL_DEPTH_TEST);

		// only pass stencil test if value is equal to 1
		glStencilFunc(GL_EQUAL, 1, 1);

		// don't change the stencil values
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);					
					
		// draw reflection object
		glPushMatrix();
			// flip vertically
			glScalef(0.2f, -0.2f, 0.2f);
			// translate the object into the drawing plane - because the object is flipped it moves down
			glTranslatef(0, 6, 0);		
			// same as the real version of the object
			glRotatef(model_rotation, 0, 1, 0);		
			model.Render();
		glPopMatrix();

		// no longer need the stencil test
		glDisable(GL_STENCIL_TEST);

		// to combine the mirror and rendered reflection of object
		glEnable(GL_BLEND);

		// lighting not required - 100% reflective object
		glDisable(GL_LIGHTING);	
		
		// gives the mirror bluish colour and combines with reflected object
		glColor4f(0.8f, 0.8f, 1.0f, 0.8f);

		glDisable(GL_TEXTURE_2D);
		// back to white
		//glColor3f(1.0f, 1.0f, 1.0f);

		// draw mirror object again									
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-4.0f, 0.0f, -4.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(4.0f, 0.0f, -4.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(4.0f, 0.0f, 4.0f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-4.0f, 0.0f, 4.0f);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);

		// back to white
		glColor3f(1.0f, 1.0f, 1.0f);

		// draw 'real' object
		glPushMatrix();
			glScalef(0.2f, 0.2f, 0.2f);
			glTranslatef(0, 12, 0);
			glRotatef(model_rotation, 0, 1, 0);
			model.Render();
		glPopMatrix();
	glPopMatrix();
}

// draws an oblong of the given dimensions
void Geometry::Oblong(float x, float y, float z)
{
	glBegin(GL_TRIANGLES);
		//front face I  
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5 * x, -0.5 * y, 0.5 * z);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5 * x, 0.5 * y, 0.5 * z);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5 * x, 0.5 * y, 0.5 * z);

		//front face II
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5 * x, 0.5 * y, 0.5 * z);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5 * x, -0.5 * y, 0.5 * z);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.5 * x, -0.5 * y, 0.5 * z);

		//back face I
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5 * x, -0.5 * y, -0.5 * z);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5 * x, -0.5 * y, -0.5 * z);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5 * x, 0.5 * y, -0.5 * z);

		//back face II
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5 * x, 0.5 * y, -0.5 * z);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5 * x, 0.5 * y, -0.5 * z);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5 * x, -0.5 * y, -0.5 * z);

		//left face I
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5 * x, -0.5 * y, 0.5 * z);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5 * x, 0.5 * y, 0.5 * z);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5 * x, 0.5 * y, -0.5 * z);

		//left face II
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5 * x, 0.5 * y, -0.5 * z);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5 * x, -0.5 * y, -0.5 * z);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5 * x, -0.5 * y, 0.5 * z);

		//right face I
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5 * x, -0.5 * y, 0.5 * z);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5 * x, -0.5 * y, -0.5 * z);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5 * x, 0.5 * y, -0.5 * z);

		//right face II
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5 * x, 0.5 * y, -0.5 * z);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5 * x, 0.5 * y, 0.5 * z);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5 * x, -0.5 * y, 0.5 * z);

		//top face I
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5 * x, 0.5 * y, 0.5 * z);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5 * x, 0.5 * y, 0.5 * z);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5 * x, 0.5 * y, -0.5 * z);

		//top face II
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5 * x, 0.5 * y, -0.5 * z);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5 * x, 0.5 * y, -0.5 * z);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5 * x, 0.5 * y, 0.5 * z);

		//bottom face I
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5 * x, -0.5 * y, 0.5 * z);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5 * x, -0.5 * y, 0.5 * z);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5 * x, -0.5 * y, -0.5 * z);

		//bottom face II
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5 * x, -0.5 * y, -0.5 * z);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5 * x, -0.5 * y, -0.5 * z);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.5 * x, -0.5 * y, 0.5 * z);
	glEnd();
}