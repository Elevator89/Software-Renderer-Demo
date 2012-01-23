#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Common.h"
#include "Interfaces/Interfaces.h"

typedef std::vector<KeyboardListener*> KeyboardListeners;

class Keyboard {
protected:
	static int	_keys[GLFW_KEY_LAST];

	static KeyboardListeners _listeners;

public:
	static void GLFWCALL CatchKeyboard( int key, int state );

	static void AddListener( KeyboardListener* listener ){ _listeners.push_back( listener ); }
	Keyboard(){}
	~Keyboard(){}
};

#endif
