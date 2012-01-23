#include "Common.h"
#include "RGBBuffer.h"

//const int RGBBuffer::MAX_WIDTH = 1600;
//const int RGBBuffer::MAX_HEIGHT = 1200;

RGBBuffer::RGBBuffer( uint width, uint height, const Color& bg ):
	_width( width ),
	_height( height ),
	_bgColor( bg )
{
	_aspect = float(_width) / float(_height);
	Clear();
}

void RGBBuffer::Clear(){
	for( int i = 0; i < _width * _height; ++i ){
		_map[i] = _bgColor;
		_z[i] = 1e10f;
	}
}

void RGBBuffer::Resize( uint width, uint height ){
	_width = width;
	_height = height;
	_aspect = float(_width) / float(_height);

	Clear();
}

void RGBBuffer::Draw(){
	float xs = -_aspect;
	float ys = 1.0f;

	float dx = 2.0f * _aspect / float(_width);
	float dy = -2.0f / float(_height);

	float xf, yf;
	yf = ys;

	glBegin( GL_POINTS );
	for( float y = 0; y <= _height; ++y ){
		xf = xs;
		for( uint x = 0; x <= _width; ++x ){
			Color col = Get( Dot(x,y) );
			glColor4f( col.R, col.G, col.B, col.A );
			glVertex2f ( xf, yf );
			xf += dx;
		}
		yf += dy;
	}
	glEnd();
	
}
