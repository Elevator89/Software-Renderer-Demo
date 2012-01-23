#ifndef MOUSE_LISTENER_H
#define MOUSE_LISTENER_H

#include "Common.h"

class MouseListener {
public:
	MouseListener(){}
	~MouseListener(){}

	virtual void OnButtonPress( int button ) = 0;
	virtual void OnButtonRelease( int button ) = 0;
	virtual void OnMove( int x, int y ) = 0;
	virtual void OnWheel( int wheel ) = 0;
};

#endif
