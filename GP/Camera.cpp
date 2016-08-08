// Josh Hale - 1402439
// Graphics Programming Coursework Gallery
// Camera.cpp
// A class which handles camera controls and calculations

#include "Camera.h"

// initial values for first person camera
void Camera::Initialise(char* skybox_filename)
{
	skybox.LoadTexture(skybox_filename);

	position = { 0, 5, 20 };
	look_at = { 0, 5, 0 };
	up = { 0, 1, 0 };

	yaw = 0;
	pitch = 10;
	roll = 0;
	angle = 0;
}

// initial values for rotating camera
void Camera::InitialiseModelCamera()
{
	position = { 0, 14, 6 };
	look_at = { 0, 6, 12.0 };

	angle = 3.1415;
}

// updates and displays the camera viewport
void Camera::RenderCamera(float dt, Input* in_, RECT* screen_rect_, HWND hwnd)
{
	// get input for camera controls
	GetCameraInput(dt, in_, screen_rect_);

	// set the cursor to the centre of the screen
	POINT point;
	point.x = (screen_rect_->right / 2);
	point.y = (screen_rect_->bottom / 2);
	ClientToScreen(hwnd, &point);
	SetCursorPos(point.x, point.y);

	// update the camera look at
	Update();
	gluLookAt(position.getX(), position.getY(), position.getZ(),
		look_at.getX(), look_at.getY(), look_at.getZ(),
		up.getX(), up.getY(), up.getZ());

	// draw the skybox
	Skybox();
}

// updates and displays the camera viewport
void Camera::RenderModelCamera(float dt)
{
	// update the camera look at
	UpdateModelCamera(dt);
	gluLookAt(position.getX(), position.getY(), position.getZ(),
		look_at.getX(), look_at.getY(), look_at.getZ(),
		up.getX(), up.getY(), up.getZ()); //Where we are, What we look at, and which way is up
}

// recalculates position, up and look at values for first person camera
void Camera::Update()
{
	// temp values for sin/cos values
	float cosR, cosP, cosY;		
	float sinR, sinP, sinY;

	// mass calculate trigonometric intermediates for speed
	cosY = cosf(yaw * 3.1415 / 180);
	cosP = cosf(pitch * 3.1415 / 180);
	cosR = cosf(roll * 3.1415 / 180);
	sinY = sinf(yaw * 3.1415 / 180);
	sinP = sinf(pitch * 3.1415 / 180);
	sinR = sinf(roll * 3.1415 / 180);

	// calculate forward vector using parametric equation of a sphere
	forward.setX(sinY * cosP);
	forward.setY(sinP);
	forward.setZ(cosP * (-1 * cosY));

	// calculate up vector using parametric equation of a sphere
	up.setX(((-1 * cosY) * sinR) - (sinY * sinP * cosR));
	up.setY(cosP * cosR);
	up.setZ(((-1 * sinY) * sinR) - (sinP * cosR * (-1 * cosY)));

	// calculate right vector for strafing
	ftemp = forward;
	right = ftemp.cross(up);

	// calculate look at from position and forward
	look_at = position + forward;
}

// recieves input for first person camera
void Camera::GetCameraInput(float dt, Input* in_, RECT* screen_rect_)
{
	input_ = in_;
	Vector3 temp = forward;

	// if 'W' pressed move forward
	if (input_->isKeyDown(W_KEY))
	{
		position.setX(position.getX() + (dt * MOVEMENT_SPEED * temp.getX()));
		position.setY(position.getY() + (dt * MOVEMENT_SPEED * temp.getY()));
		position.setZ(position.getZ() + (dt * MOVEMENT_SPEED * temp.getZ()));
		input_->SetKeyUp(W_KEY);
	}
	// if 'S' pressed move backward
	else if (input_->isKeyDown(S_KEY))
	{
		position.setX(position.getX() - (dt * MOVEMENT_SPEED * temp.getX()));
		position.setY(position.getY() - (dt * MOVEMENT_SPEED * temp.getY()));
		position.setZ(position.getZ() - (dt * MOVEMENT_SPEED * temp.getZ()));
		input_->SetKeyUp(S_KEY);
	}
	// if 'A' pressed move left
	if (input_->isKeyDown(A_KEY))
	{
		position.setX(position.getX() - (dt * MOVEMENT_SPEED * right.getX()));
		position.setY(position.getY() - (dt * MOVEMENT_SPEED * right.getY()));
		position.setZ(position.getZ() - (dt * MOVEMENT_SPEED * right.getZ()));
		input_->SetKeyUp(A_KEY);
	}
	// if 'D' pressed move right
	else if (input_->isKeyDown(D_KEY))
	{
		position.setX(position.getX() + (dt * MOVEMENT_SPEED * right.getX()));
		position.setY(position.getY() + (dt * MOVEMENT_SPEED * right.getY()));
		position.setZ(position.getZ() + (dt * MOVEMENT_SPEED * right.getZ()));
		input_->SetKeyUp(D_KEY);
	}
	// if 'up' pressed move up
	if (input_->isKeyDown(VK_UP))
	{
		position.setX(position.getX() + (dt * MOVEMENT_SPEED * up.getX()));
		position.setY(position.getY() + (dt * MOVEMENT_SPEED * up.getY()));
		position.setZ(position.getZ() + (dt * MOVEMENT_SPEED * up.getZ()));
		input_->SetKeyUp(VK_UP);
	}
	// if 'down' pressed move down
	else if (input_->isKeyDown(VK_DOWN))
	{
		position.setX(position.getX() - (dt * MOVEMENT_SPEED * up.getX()));
		position.setY(position.getY() - (dt * MOVEMENT_SPEED * up.getY()));
		position.setZ(position.getZ() - (dt * MOVEMENT_SPEED * up.getZ()));
		input_->SetKeyUp(VK_DOWN);
	}
	
	// reset mouse movement this frame
	mouse_moved_y = 0;
	mouse_moved_x = 0;
	
	// get pointer to the screen and calculate centre
	screen_size_ = screen_rect_;
	screen_centre_x = screen_size_->right / 2;
	screen_centre_y = screen_size_->bottom / 2;

	// calculate how far mouse has moved from the centre
	mouse_moved_x = ((input_->getMouseX()) - screen_centre_x);
	mouse_moved_y = ((input_->getMouseY()) - screen_centre_y);

	// update yaw and pitch according to mouse movements
	yaw += mouse_moved_x * dt * CAMERA_SENSITIVITY;
	pitch -= mouse_moved_y * dt * CAMERA_SENSITIVITY;
}

// recalculates position, up and look at values for rotating camera
void Camera::UpdateModelCamera(float dt)
{
	// temp values for sin/cos values
	float cosR, cosP, cosY;		
	float sinR, sinP, sinY;
	
	// camera always looks at the same point
	look_at.setX(0.0);
	look_at.setY(6.0);
	look_at.setZ(12.0);

	// used for translating between radians and degrees
	float deg = (3.1415 / 180);
	
	// update angle each frame for continuous movement
	angle -= CAMERA_SPIN_SPEED * dt;
	
	// height is always the same, x and z calculated from parametric eqn of circle
	position.setY(10.0);
	position.setX(0 + (CAMERA_RADIUS * cosf(angle)));
	position.setZ(12 + (CAMERA_RADIUS * sinf(angle)));

	// calculate the forward vector
	forward = look_at - position;

	// calculate pitch from forward vector, yaw and roll remain the same
	pitch = asinf(forward.getY() * deg);
	yaw = 0;
	roll = 0;

	// mass calculate trigonometric intermediates for speed
	cosY = cosf(yaw);
	cosP = cosf(pitch);
	cosR = cosf(roll);
	sinY = sinf(yaw);
	sinP = sinf(pitch);
	sinR = sinf(roll);

	// calculate up vector using parametric equation of a sphere
	up.setX(((-1 * cosY) * sinR) - (sinY * sinP * cosR));
	up.setY(cosP * cosR);
	up.setZ(((-1 * sinY) * sinR) - (sinP * cosR * (-1 * cosY)));
}

// renders the skybox around the first person camera
void Camera::Skybox()
{
	glBindTexture(GL_TEXTURE_2D, skybox.texture);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glTranslatef(position.getX(), position.getY(), position.getZ());
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		//Begin drawing state
		glBegin(GL_QUADS);

			// front face
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.251f, 0.501f);
			glVertex3f(-2, -2, 2);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.499f, 0.501f);
			glVertex3f(2, -2, 2);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.499f, 0.749f);
			glVertex3f(2, 2, 2);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.251f, 0.749f);
			glVertex3f(-2, 2, 2);

			// right face
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.501f, 0.501f);
			glVertex3f(2, -2, 2);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.749f, 0.501f);
			glVertex3f(2, -2, -2);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.749f, 0.749f);
			glVertex3f(2, 2, -2);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.501f, 0.749f);
			glVertex3f(2, 2, 2);

			// rear face
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.751f, 0.501f);
			glVertex3f(2, -2, -2);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.909f, 0.501f);
			glVertex3f(-2, -2, -2);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.999f, 0.749f);
			glVertex3f(-2, 2, -2);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.751f, 0.749f);
			glVertex3f(2, 2, -2);

			// left face
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.001f, 0.501f);
			glVertex3f(-2, -2, -2);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.249f, 0.501f);
			glVertex3f(-2, -2, 2);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.249f, 0.749f);
			glVertex3f(-2, 2, 2);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.001f, 0.749f);
			glVertex3f(-2, 2, -2);

			// top face
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.251f, 0.751f);
			glVertex3f(-2, 2, 2);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.499f, 0.751f);
			glVertex3f(2, 2, 2);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.499f, 0.999f);
			glVertex3f(2, 2, -2);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.251f, 0.999f);
			glVertex3f(-2, 2, -2);

			// bottom face
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.251f, 0.251f);
			glVertex3f(-2, -2, -2);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.499f, 0.251f);
			glVertex3f(2, -2, -2);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.499f, 0.499f);
			glVertex3f(2, -2, 2);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.251f, 0.499f);
			glVertex3f(-2, -2, 2);
		glEnd();

	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}