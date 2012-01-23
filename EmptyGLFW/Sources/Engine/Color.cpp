#include "Common.h"
#include "Color.h"

const Color Color::BLACK	( 0.0f, 0.0f, 0.0f, 1.0f );
const Color Color::GREY		( 0.5f, 0.5f, 0.5f, 1.0f );
const Color Color::WHITE	( 1.0f, 1.0f, 1.0f, 1.0f );
const Color Color::RED		( 1.0f, 0.0f, 0.0f, 1.0f );
const Color Color::GREEN	( 0.0f, 1.0f, 0.0f, 1.0f );
const Color Color::BLUE		( 0.0f, 0.0f, 1.0f, 1.0f );

Color Color::operator +=( const Color& c ){
	R += c.R;
	G += c.G;
	B += c.B;
	A += c.A;
	return *this;
}

Color Color::operator -=( const Color& c ){
	R -= c.R;
	G -= c.G;
	B -= c.B;
	A -= c.A;
	return *this;
}

Color Color::operator *=( const Color& c ){
	R *= c.R;
	G *= c.G;
	B *= c.B;
	A *= c.A;
	return *this;
}

Color Color::operator *=( float a ){
	R *= a;
	G *= a;
	B *= a;
	A *= a;
	return *this;
}

Color Color::operator /=( float a ){
	R /= a;
	G /= a;
	B /= a;
	A /= a;
	return *this;
}
