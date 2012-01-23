#include "Common.h"
#include "Mouse.h"

int	Mouse::_buttons[GLFW_MOUSE_BUTTON_LAST] = {};
int	Mouse::_x = 0;
int	Mouse::_y = 0;
int	Mouse::_wheel = 0;

MouseListeners Mouse::_listeners;

void GLFWCALL Mouse::CatchMousePos( int x, int y ) {
	_x = x;
	_y = y;
	for( MouseListeners::const_iterator it = Mouse::_listeners.begin(); it != Mouse::_listeners.end(); it++ )
		(*it)->OnMove( x, y );
}

void GLFWCALL Mouse::CatchMouseButtons( int button, int state ) {
	_buttons[button] = state;
	if( state )
		for( MouseListeners::const_iterator it = Mouse::_listeners.begin(); it != Mouse::_listeners.end(); it++ )
			(*it)->OnButtonPress( button );
	else
		for( MouseListeners::const_iterator it = Mouse::_listeners.begin(); it != Mouse::_listeners.end(); it++ )
			(*it)->OnButtonRelease( button );
}


void GLFWCALL Mouse::CatchMouseWheel( int wheel ) {
	_wheel = wheel;
	for( MouseListeners::const_iterator it = Mouse::_listeners.begin(); it != Mouse::_listeners.end(); it++ )
		(*it)->OnWheel( wheel );
}
