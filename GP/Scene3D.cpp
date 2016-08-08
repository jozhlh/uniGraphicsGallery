// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Scene3D.cpp
// A class which controls the OpenGL scene

#include "Scene3D.h"

bool Scene3D::CreatePixelFormat(HDC hdc) 
{ 
    PIXELFORMATDESCRIPTOR pfd = {0}; 
    int pixelformat; 
 
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// Set the size of the structure
    pfd.nVersion = 1;							// Always set this to 1
	// Pass in the appropriate OpenGL flags
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.dwLayerMask = PFD_MAIN_PLANE;			// standard mask (this is ignored anyway)
    pfd.iPixelType = PFD_TYPE_RGBA;				// RGB and Alpha pixel type
    pfd.cColorBits = COLOUR_DEPTH;				// Here we use our #define for the color bits
    pfd.cDepthBits = COLOUR_DEPTH;				// Z buffer precision for depth, (z-fighting)
    pfd.cAccumBits = 0;							// nothing for accumulation
    pfd.cStencilBits = COLOUR_DEPTH;			// Used for stencil buffer (COLOUR_DEPTH for on, 0 for off)
 
	//Gets a best match on the pixel format as passed in from device
    if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == false ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
	//sets the pixel format if its ok. 
    if (SetPixelFormat(hdc, pixelformat, &pfd) == false) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
    return true;
}

void Scene3D::ResizeGLWindow(int width, int height)// Initialize The GL Window
{
	if (height==0)// Prevent A Divide By Zero error
	{
		height=1;// Make the Height Equal One
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// calculate aspect ratio
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 1 ,150.0f);

	// reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
}

void Scene3D::InitializeOpenGL(int width, int height) 
{  
    hdc = GetDC(*hwnd);				//  sets  global HDC

    if (!CreatePixelFormat(hdc))	//  sets  pixel format
        PostQuitMessage (0);

    hrc = wglCreateContext(hdc);	//  creates  rendering context from  hdc
    wglMakeCurrent(hdc, hrc);		//	Use this HRC.

	ResizeGLWindow(width, height);	// Setup the Screen
}

void Scene3D::Init(HWND* wnd, Input* in)
{
	hwnd = wnd;
	input = in;

	GetClientRect(*hwnd, &screenRect);						// get rect into our handy global rect
	InitializeOpenGL(screenRect.right, screenRect.bottom);	// initialise openGL

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// How to clear the stencil buffer (added in for on, comment out for off)
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_COLOR_MATERIAL);						// Enables coloured geometry
	
	// initialise first person camera with skybox texture
	camera.Initialise("skybox.png");

	// initialise rotating camera
	model_camera.InitialiseModelCamera();

	// initialise solar system with textures for the sun and planets
	planets.Initialise("white_wall_texture.png", "planet_texture.png");

	// initialise other geometry
	objects.Initialise();

	// set default camera
	current_camera = 1;
}

// receives new input and calls to render
void Scene3D::Update(float dt)
{
	// if the user has paused the image
	if (input->isKeyDown(VK_SPACE))
	{
		// inform the image
		if (objects.paused)
		{
			objects.paused = false;
		}
		else
		{
			objects.paused = true;
		}
		input->SetKeyUp(VK_SPACE);
	}

	// if the user has switched camera change active camera
	if (input->isKeyDown(KEY_1))
	{
		current_camera = 1;
		input->SetKeyUp(KEY_1);
	}
	if (input->isKeyDown(KEY_2))
	{
		current_camera = 2;
		input->SetKeyUp(KEY_2);
	}
	
	// render scene
	Render(dt);
}

// draws evrything to the screen
void Scene3D::Render(float dt) 
{
	// clear the screen as well as the depth and stencil buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	// load identity matrix
	glLoadIdentity();

	// call the camera that is currently selected
	switch (current_camera)
	{
	case 1: camera.RenderCamera(dt, input, &screenRect, *hwnd);
		break;
	case 2: model_camera.RenderModelCamera(dt);
		break;
	}

	// update and display all planets
	planets.Update(3.0, dt);

	// update and display all lights
	lights.ModelLight(dt);
	lights.GridLight();
	lights.ImageLight();
	lights.Sunlight();

	// update and display all other geometry
	objects.DrawGeometry(dt);

	// set colour to white
	glColor3f(1.0f, 1.0f, 1.0f);

	// Swap the frame buffers.
	SwapBuffers(hdc);
}		

// handles user changing window size
void Scene3D::Resize()
{
	if (hwnd == NULL)
		return;

	GetClientRect(*hwnd, &screenRect);
	ResizeGLWindow(screenRect.right, screenRect.bottom);
}