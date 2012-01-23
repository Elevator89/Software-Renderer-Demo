#ifndef THORUS_H
#define THORUS_H

#include "Common.h"
#include "Shape.h"

class Thorus: public Shape {
protected:
	float _parA;
	float _parB;
	int _det;

	void Build();
	void AltBuild();

	Vec3* _allVertices;

public:
	Thorus( const Transform& pos, const Transform& vel, float paramA, float paramB, int det, const Color& color, const Material& material );
	Thorus( const Thorus& thorus );
	
	virtual void DrawSelf();

};

#endif
