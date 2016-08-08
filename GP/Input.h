// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Input.h
// A class which tests for input and defines virtual key codes

#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

/// VIRTUAL KEY CODES
#define W_KEY 0x57
#define A_KEY 0x41
#define S_KEY 0x53
#define D_KEY 0x44
#define KEY_1 0x31
#define KEY_2 0x32

class Input
{
	typedef struct Mouse
	{
		int x,y;
		bool left, right;
	};

public:
	/// GETTERS AND SETTERS
	void SetKeyDown(WPARAM);
	void SetKeyUp(WPARAM);
	bool isKeyDown(int);
	void setMouseX(int);
	void setMouseY(int);
	int getMouseX();
	int getMouseY();

private:
	/// PRIVATE VARIABLES
	bool keys[256];
	Mouse mouse;

};

#endif