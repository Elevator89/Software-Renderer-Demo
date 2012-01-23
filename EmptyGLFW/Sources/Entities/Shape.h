#ifndef SHAPE_H
#define SHAPE_H

#include "Common.h"
#include "Entity.h"

struct Polygon {
	std::vector<Vec3> Vertices;
	
	Polygon(){}
	Polygon( const Vec3* arr, uint count );
	Polygon( const Polygon& polygon );

	Vec3* Array();
	void AddVertex( const Vec3& vertex ) { Vertices.push_back( vertex ); }
};

class Shape: public Entity {
protected:
	Material _material;
	Color _color;
	std::vector<Polygon> _polygons;
public:
	Shape( const Transform& pos, const Transform& vel, const Color& color, const Material& material );
	Shape( const Shape& shape );

	void AddPolygon( const Polygon& polygon ){ _polygons.push_back( polygon ); }
	virtual void DrawSelf();
};

#endif
