#ifndef MOUSE_H
#define MOUSE_H

#include "Common.h"
#include "Interfaces/Interfaces.h"

typedef std::vector<MouseListener*> MouseListeners;

class Mouse {
protected:
	static int	_buttons[GLFW_MOUSE_BUTTON_LAST];
	static int	_x;
	static int	_y;
	static int	_wheel;

	static MouseListeners _listeners;

public:

	static void GLFWCALL CatchMousePos( int x, int y );
	static void GLFWCALL CatchMouseButtons( int button, int state );
	static void GLFWCALL CatchMouseWheel( int wheel );

	static void AddListener( MouseListener* listener ){ _listeners.push_back( listener ); }
	
	Mouse(){}
	~Mouse(){}
};

#endif
