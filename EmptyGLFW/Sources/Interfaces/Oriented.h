#ifndef ORIENTED_H
#define ORIENTED_H

#include "Common.h"
#include "Math/Math.h"
#include "Tickable.h"

class Oriented: public Tickable {
public:
	Transform Pos;
	Transform Vel;

	Oriented(): Pos(), Vel() {}
	Oriented( const Transform& pos, const Transform& vel ): Pos( pos ), Vel( vel ){}
	Oriented( const Oriented& or ): Pos( or.Pos ), Vel( or.Vel ){}

	virtual bool Tick( float dt ) { Pos += Vel * dt; return true; }
}; 

#endif