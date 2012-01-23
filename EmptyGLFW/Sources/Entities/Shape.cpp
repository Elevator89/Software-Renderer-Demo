#include "Common.h"
#include "Shape.h"

Polygon::Polygon( const Vec3* arr, uint count ) {
	for( uint i = 0; i < count; ++i )
		Vertices[i] = arr[i];
}

Polygon::Polygon( const Polygon& polygon ):
	Vertices( polygon.Vertices )
{}

Vec3* Polygon::Array(){
	uint count = Vertices.size();
	Vec3* arr = new Vec3[ count ];
	for( uint i = 0; i < count; ++i )
		arr[i] = Vertices[i];
	return arr;
}


Shape::Shape( const Transform& pos, const Transform& vel, const Color& color, const Material& material ):
	Entity( pos, vel ),
	_color( color ),
	_material( material )
{}

Shape::Shape( const Shape& shape ):
	Entity( shape.Pos, shape.Vel ),
	_color( shape._color ),
	_material( shape._material )
{}

void Shape::DrawSelf(){
	uint size = _polygons.size();
	for( uint i = 0; i < size; ++i ){
		uint count = _polygons[i].Vertices.size();
		_renderer->DrawPolygon( _polygons[i].Array(), count, _material );
	}
}

