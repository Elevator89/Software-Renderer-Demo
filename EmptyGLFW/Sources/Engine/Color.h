#ifndef COLOR_H
#define COLOR_H

#include "Common.h"
#include "Math/Basics.h"

#pragma pack(push, 1)
struct Color {
	float R,G,B,A;

	Color(): R( 0.0f ), G( 0.0f ), B( 0.0f ), A( 1.0f ) {}
	Color( float r, float g, float b ): R( r ), G( g ), B( b ), A( 1.0f ) {}
	Color( float r, float g, float b, float a ): R( r ), G( g ), B( b ), A( a ) {}

	Color operator += ( const Color& v );
	Color operator -= ( const Color& v );
	Color operator *= ( const Color& v );
	Color operator *= ( float a );
	Color operator /= ( float a );

	inline float* Array() const { return (float*)&R; }

	static const Color BLACK;
	static const Color GREY;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
};
#pragma pack(pop)

inline Color operator+	( const Color& a, const Color& b )	{ return Color( a.R + b.R, a.G + b.G, a.B + b.B, a.A + b.A ); }
inline Color operator-	( const Color& a, const Color& b )	{ return Color( a.R - b.R, a.G - b.G, a.B - b.B, a.A - b.A ); }
inline Color operator*	( const Color& a, const Color& b )	{ return Color( a.R * b.R, a.G * b.G, a.B * b.B, a.A * b.A );  }
inline Color operator*	( const Color& v, float a )			{ return Color( v.R * a, v.G * a, v.B * a, v.A * a ); }
inline Color operator/	( const Color& v, float a )			{ return Color( v.R / a, v.G / a, v.B / a, v.A / a ); }
inline bool operator ==	( const Color& a, const Color& b )	{ return fleq( a.R, b.R ) && fleq( a.G, b.G ) && fleq( a.B, b.B ) && fleq( a.A, b.A ); }
inline bool operator !=	( const Color& a, const Color& b )	{ return !( a == b ); }

struct Material{
	Color Ambt;
	Color Diff;
	Color Spec;
	float Shin;

	Material(): 
		Ambt( Color::BLACK ), Diff( Color::GREY ), Spec( Color::WHITE ), Shin( 1.0f ) {}
	
	Material( const Color& ambt, const Color& diff, const Color& spec, float shin ): 
		Ambt( ambt ), Diff( diff ), Spec( spec ), Shin( shin ) {}
};



#endif
