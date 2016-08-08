// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Lighting.cpp
// A class which creates all the lights in the scene

#include "Lighting.h"

// creates a light at the centre of the sun
void Lighting::Sunlight()
{
	GLfloat Light_Ambient[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat Light_Diffuse[] = { 3.0f, 3.0f, 0.0f, 1.0f };
	GLfloat Light_Position[] = { 0.0f, 4.0f, 40.0f, 1.0f };
	GLfloat Light_Attenuation_Constant[] = { 0.7f };
	GLfloat Light_Attenuation_Linear[] = { 0.0f };
	GLfloat Light_Attenuation_Quadratic[] = { 0.06f }; // drops off past the planets

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Light_Attenuation_Constant);
	glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, Light_Attenuation_Linear);
	glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Light_Attenuation_Quadratic);

	glEnable(GL_LIGHT1);
}

// creates a light aimed at the wire frame grid
void Lighting::GridLight()
{
	GLfloat Light_Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Diffuse[] = { 0.8f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 0.0f, 8.0f, -2.0f, 1.0f };
	GLfloat spot_Direction[] = { 0.0f, 0.0f, -1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT3, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 55.0f);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
	glEnable(GL_LIGHT3);

}

// creates a light aimed at the spinning image
void Lighting::ImageLight()
{
	GLfloat Light_Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 0.0f, 8.0f, 50.0f, 1.0f };
	GLfloat spot_Direction[] = { 0.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
	glEnable(GL_LIGHT0);

}

// creates a light which rotates around the model
void Lighting::ModelLight(float dt)
{
	Vector3 result;

	model_light_angle += MODEL_LIGHT_SPEED * dt;

	model_light_pos.setX(0 + (MODEL_LIGHT_RADIUS * cosf(model_light_angle)));
	model_light_pos.setZ(12 + (MODEL_LIGHT_RADIUS * sinf(model_light_angle)));

	GLfloat Light_Ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Light_Diffuse[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { model_light_pos.getX(), model_light_pos.getY(), model_light_pos.getZ(), 1.0f };
	GLfloat spot_Direction[] = { 0, -1, 0 };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0f);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_Direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
	glEnable(GL_LIGHT2);

	model_light_pos.set(0.0, 14.0, 20.0);
	model_light_look_at.set(0.0, 6.0, 12.0);
}