#include "Common.h"
#include "Keyboard.h"

using namespace std;

int	Keyboard::_keys[GLFW_KEY_LAST] = {};

KeyboardListeners Keyboard::_listeners;

void GLFWCALL Keyboard::CatchKeyboard( int key, int state ){
	_keys[key] = state;
	if( state )
		for( KeyboardListeners::const_iterator it = _listeners.begin(); it != _listeners.end(); it++ )
			(*it)->OnKeyPress( key );
	else
		for( KeyboardListeners::const_iterator it = _listeners.begin(); it != _listeners.end(); it++ )
			(*it)->OnKeyRelease( key );
}
