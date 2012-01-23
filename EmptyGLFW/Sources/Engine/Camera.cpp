#include "Common.h"
#include "Camera.h"

int _x = 0;
int _y = 0;

Vec3 velVec;

const float CAM_SPEED = 5.0f;
const float ROT_SPEED = 0.01f;

Camera::Camera(): Oriented() {
	glfwGetMousePos( &_x, &_y );
	dx = 0;
	dy = 0;
	pressed = false;
}

bool Camera::Tick( float dt ) {

	Vel.Vec = velVec * CAM_SPEED * Pos.Rot;
	Vel.Rot.Y =  float(dx) * ROT_SPEED / dt;
	Vel.Rot.P = -float(dy) * ROT_SPEED / dt;

	dx = 0;
	dy = 0;

	return Oriented::Tick( dt );
}


void Camera::OnKeyPress( int key ){
	if( key == GLFW_KEY_LEFT  || key == 'A' )	velVec += Vec3::LEFT;
	if( key == GLFW_KEY_RIGHT || key == 'D' )	velVec += Vec3::RIGHT;
	if( key == GLFW_KEY_UP    || key == 'W' )	velVec += Vec3::FORWARD;
	if( key == GLFW_KEY_DOWN  || key == 'S' )	velVec += Vec3::BACK;
}

void Camera::OnKeyRelease( int key ){
	if( key == GLFW_KEY_LEFT  || key == 'A' )	velVec -= Vec3::LEFT;
	if( key == GLFW_KEY_RIGHT || key == 'D' )	velVec -= Vec3::RIGHT;
	if( key == GLFW_KEY_UP    || key == 'W' )	velVec -= Vec3::FORWARD;
	if( key == GLFW_KEY_DOWN  || key == 'S' )	velVec -= Vec3::BACK;
}

void Camera::OnButtonPress( int button ){
	pressed = true;
}

void Camera::OnButtonRelease( int button ){
	pressed = false;
}

void Camera::OnMove( int x, int y ){
	if( pressed ){
		dx = x - _x;
		dy = y - _y;
	}
	_x = x;
	_y = y;
}

void Camera::OnWheel( int wheel ){}
