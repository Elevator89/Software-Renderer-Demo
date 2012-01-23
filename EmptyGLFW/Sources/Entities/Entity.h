#ifndef ENTITY_H
#define ENTITY_H

#include "Common.h"
#include "Math/Math.h"
#include "Interfaces/Interfaces.h"
#include "Engine/Renderer.h"

class Entity: public Oriented {
public:
	Entity( const Transform& pos, const Transform& vel ): Oriented( pos, vel ){}
	Entity( const Entity& entity ): Oriented( entity.Pos, entity.Vel ) {}
	~Entity() {}

	void Draw( Renderer* renderer ) {
		if( _renderer != renderer )	_renderer = renderer;
		_renderer->Push();
		_renderer->Mult( Pos.GetMatrix() );
		DrawSelf();
		_renderer->Pop();
	}

protected:
	Renderer* _renderer;

	virtual void DrawSelf() = 0;
};

#endif
