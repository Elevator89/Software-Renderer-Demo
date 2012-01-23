#ifndef TICKABLE_H
#define TICKABLE_H

#include "Common.h"

static const float DEFAULT_DT = 0.015f;

class Tickable {
protected:
	float startTime;
	float time;

public:
	Tickable( float aStartTime = 0.0f ): startTime( aStartTime ) {}
	Tickable( const Tickable& tickable ): startTime( tickable.startTime ), time( tickable.time ) {}
	~Tickable(){}

	virtual bool Tick( float dt = DEFAULT_DT ) = 0;

};

#endif
