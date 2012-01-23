#ifndef LIGHT_H
#define LIGHT_H

#include "Common.h"
#include "Entity.h"
#include "LightDef.h"

class Light: public Entity {
public:
	LightDef Def;

	Light( const Transform& pos, const Transform& vel, const Color& ambient, const Color& diffuse, const Color& specular );
	Light( const Light& light );

	virtual void DrawSelf();

protected:
	bool added;
};

#endif
