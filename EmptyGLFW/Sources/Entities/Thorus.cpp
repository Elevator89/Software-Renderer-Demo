#include "Common.h"
#include "Thorus.h"

Thorus::Thorus( const Transform& pos, const Transform& vel, float paramA, float paramB, int det, const Color& color, const Material& material ):
	Shape( pos, vel, color, material ),
	_parA( paramA ),
	_parB( paramB ),
	_det( det )
{
	Build();
}

Thorus::Thorus( const Thorus& thorus ):
	Shape( thorus.Pos, thorus.Vel, thorus._color, thorus._material ),
	_parA( thorus._parA ),
	_parB( thorus._parB ),
	_det( thorus._det )
{
	Build();
}

void Thorus::Build(){
	float du = (float)( 2 * PI / _det );
	float dv = (float)( 2 * PI / _det );
	float u = 0.0;
	float v = 0.0;


	float cU = cos( u );
	float sU = sin( u );
	float cV = cos( v );
	float sV = sin( v );
	float cUDU = cos( u + du );
	float sUDU = sin( u + du );
	float cVDV = cos( v + dv );
	float sVDV = sin( v + dv );


	float a_b = _parA + _parB;
	for( int i = 0; i < _det; i++, v += dv, u = 0.0 )
		for( int j = 0; j < _det; j++, u += du){

			cU = cos( u );
			sU = sin( u );
			cV = cos( v );
			sV = sin( v );
			cUDU = cos( u + du );
			sUDU = sin( u + du );
			cVDV = cos( v + dv );
			sVDV = sin( v + dv );

			Polygon polygon;
			polygon.AddVertex( Vec3( ( _parA + _parB * cU ) * cV,		( _parA + _parB * cU ) * sV,		_parB * sU ) );
			polygon.AddVertex( Vec3( ( _parA + _parB * cU ) * cVDV,		( _parA + _parB * cU ) * sVDV,		_parB * sU ) );
			polygon.AddVertex( Vec3( ( _parA + _parB * cUDU ) * cVDV,	( _parA + _parB * cUDU ) * sVDV,	_parB * sUDU ) );
			polygon.AddVertex( Vec3( ( _parA + _parB * cUDU ) * cV,		( _parA + _parB * cUDU ) * sV,		_parB * sUDU ) );
			_polygons.push_back( polygon );
		}

	uint polyCount = _det * _det;
	_allVertices = new Vec3[ polyCount * 4 ];

	for( uint i = 0; i < polyCount; ++i ){
		for ( uint j = 0; j < 4; ++j ){
			_allVertices[ i * 4 + j ] = _polygons[i].Vertices[j];
		}
	}
}

void Thorus::DrawSelf(){
	_renderer->DrawPolygons( _allVertices, _det*_det, 4, _material );
}
