#ifndef LIGHT_DEF_H
#define LIGHT_DEF_H

#include "Common.h"
#include "Engine/Color.h"
#include "Interfaces/Interfaces.h"

class LightDef: public Oriented {
public:
	Color Ambient;
	Color Diffuse;
	Color Specular;
	int Index;

	Matr4 _matr;

	LightDef():
		Ambient( Color::BLACK ),
		Diffuse( Color::WHITE ),
		Specular( Color::WHITE ),
		Index( Count )
	{
		lights[ Count++ ] = this;
	}
	LightDef( const Transform& pos, const Transform& vel, const Color& ambient, const Color& diffuse, const Color& specular ):
		Oriented( pos, vel ),
		Ambient( ambient ),
		Diffuse( diffuse ),
		Specular( specular ),
		Index( Count )
	{
		lights[ Count++ ] = this;
	}
	LightDef( const LightDef& light ):
		Oriented( light.Pos, light.Vel ),
		Ambient( light.Ambient ),
		Diffuse( light.Diffuse ),
		Specular( light.Specular ),
		Index( Count )
	{
		lights[ Count++ ] = this;
	}


	static const int MAX_LIGHTS_COUNT = 64;
	static int Count;
	static LightDef* lights[ MAX_LIGHTS_COUNT ];
};

#endif
