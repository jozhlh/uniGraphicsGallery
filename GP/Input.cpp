// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Input.cpp
// A class which tests for input and defines virtual key codes

#include "Input.h"

void Input::SetKeyDown(WPARAM key)
{
	keys[key] = true;
}

void Input::SetKeyUp(WPARAM key)
{
	keys[key] = false;
}

bool Input::isKeyDown(int key)
{
	return keys[key];
}

void Input::setMouseX(int pos)
{
	mouse.x = pos;
}

void Input::setMouseY(int pos)
{
	mouse.y = pos;
}

int Input::getMouseX()
{
	return mouse.x;
}

int Input:: getMouseY()
{
	return mouse.y;
}

