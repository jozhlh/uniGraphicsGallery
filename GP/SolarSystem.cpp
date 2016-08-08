// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// SolarSystem.cpp
// A class which creates, updates and renders the solar system model

#include "SolarSystem.h"

// generates the planets and gives them textures
void SolarSystem::Initialise(char* sun_textureFilename, char* planet_textureFilename)
{
	sun.Initialise(0.2, 20, 20, sun_textureFilename, true);
	planet.Initialise(0.2, 20, 20, planet_textureFilename, false);
}

// updates the rotation and position of the planets
void SolarSystem::Update(float scale, float dt)
{
	rotation[0] += (PLANET_MOVE_SPEED * 6) * dt;					
	rotation[1] += (PLANET_MOVE_SPEED * 2) * dt;
	rotation[2] += (PLANET_MOVE_SPEED * 0.7f) * dt;
	planet_spin += PLANET_SPIN_SPEED*dt;

	glPushMatrix();	// remember where we are - the sun
					// render the sun
		glTranslatef(0, 4.0, 40.0);
		glScalef(scale, scale, scale);
		glColor3f(1.0f, 0.9f, 0.0f);
		sun.Render();
		glPushMatrix();
			// render planet 1
			glRotatef(rotation[0], 0, 1, 0);
			glTranslatef(0.5, 0, 0);
			glScalef(0.1, 0.1, 0.1);
			glRotatef(rotation[0], 0, 1, 0);
			glColor3f(0.8f, 0.1f, 0.1f);
			planet.Render();
		glPopMatrix();	// GO BACK TO SUN
		glPushMatrix(); // REMEMBER WHERE WE ARE
						// Render planet 2
			glRotatef(rotation[1], 0, 1, 0);
			glTranslatef(0.75, 0, 0);
			glScalef(0.3, 0.3, 0.3);
			glRotatef(rotation[1], 0, 1, 0);
			glColor3f(0.1f, 0.3f, 1.0f);
			planet.Render();
			glPushMatrix(); // REMEMBER WHERE WE ARE
							// Render a moon around planet 2
				glRotatef((rotation[1] * 2.0), 0, 1, 0);
				glTranslatef(0.75, 0, 0);
				glScalef(0.3, 0.3, 0.3);
				glRotatef((rotation[1] * 2.0), 0, 1, 0);
				glColor3f(0.8f, 0.8f, 0.8f);
				planet.Render();
			glPopMatrix();
		glPopMatrix();	// GO BACK TO SUN
		glPushMatrix();
			//render planet 3
			glRotatef(rotation[2], 0, 1, 0);
			glTranslatef(1.9, 0, 0);
			glScalef(0.6, 0.6, 0.6);
			glRotatef(rotation[2], 0, 1, 0);
			glColor3f(0.2f, 0.8f, 0.1f);
			planet.Render();
			glPushMatrix(); // REMEMBER WHERE WE ARE
							// Render a moon around planet 3
				glRotatef((rotation[2] * 4.5), 0, 1, 0);
				glTranslatef(0.5, 0, 0);
				glScalef(0.3, 0.3, 0.3);
				glRotatef((rotation[2] * 4.5), 0, 1, 0);
				glColor3f(0.1f, 0.8f, 0.8f);
				planet.Render();
				glPushMatrix();	// REMEMBER WHERE WE ARE
								// Render a moon around moon 1
					glRotatef((rotation[2] * 7), 0, 1, 0);
					glTranslatef(0.5, 0, 0);
					glScalef(0.6, 0.6, 0.6);
					glRotatef((rotation[2] * 7), 0, 1, 0);
					glColor3f(0.8f, 0.3f, 0.3f);
					planet.Render();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix(); // REMEMBER WHERE WE ARE
							// Render a moon around planet 3
				glRotatef((rotation[2] * 4.0), 0, 0, 1);
				glTranslatef(0.75, 0, 0);
				glScalef(0.1, 0.1, 0.1);
				glRotatef((rotation[2] * 4.0), 0, 0, 1);
				glColor3f(1.0f, 0.1f, 0.8f);
				planet.Render();
			glPopMatrix();
		glPopMatrix();//GO BACK TO SUN
	glPopMatrix();

	// reset colour
	glColor3f(1.0f, 1.0f, 1.0f);
}