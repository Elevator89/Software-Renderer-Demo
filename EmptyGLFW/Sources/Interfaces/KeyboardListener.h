#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include "Common.h"

class KeyboardListener {
public:
	KeyboardListener(){}
	~KeyboardListener(){}

	virtual void OnKeyPress( int key ) = 0;
	virtual void OnKeyRelease( int key ) = 0;
};

#endif
