#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "Math/Math.h"
#include "Interfaces/Interfaces.h"

class Camera: public Oriented, public KeyboardListener, public MouseListener {
public:
	Camera();
	Camera( const Transform& pos, const Transform& vel ): Oriented( pos, vel ) {}
	~Camera();

	virtual bool Tick( float dt = DEFAULT_DT );

	virtual void OnKeyPress( int key );
	virtual void OnKeyRelease( int key );

	virtual void OnButtonPress( int button );
	virtual void OnButtonRelease( int button );
	virtual void OnMove( int x, int y );
	virtual void OnWheel( int wheel );


private:
	int dx;
	int dy;
	bool pressed;
};

#endif