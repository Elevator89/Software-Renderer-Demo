#ifndef ROTATION_H
#define ROTATION_H

#include "Common.h"
#include "Basics.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matr4.h"

class Rotation {
public:
	float Y; //рыскание
	float P; //тангаж
	float R; //крен

	Rotation(): Y( 0.0f ), P( 0.0f ), R( 0.0f ) {}
	Rotation( const float j, const float p, const float r ): Y( j ), P( p ), R( r ) {}
	Rotation( const Rotation& rot ): Y( rot.Y ), P( rot.P ), R( rot.R ) {}

	Rotation operator += ( const Rotation& rot );
	Rotation operator -= ( const Rotation& rot );
	Rotation operator *= ( float a );
	Rotation operator /= ( float a );

	Matr4 GetMatrix() const;
};

inline Rotation operator-	( const Rotation& r )						{ return Rotation( -r.Y, -r.P, -r.R ); }
inline Rotation operator+	( const Rotation& a, const Rotation& b )	{ return Rotation( a.Y + b.Y, a.P + b.P, a.R + b.R ); }
inline Rotation operator-	( const Rotation& a, const Rotation& b )	{ return Rotation( a.Y - b.Y, a.P - b.P, a.R - b.R ); }
inline Rotation operator*	( const Rotation& r, float a )				{ return Rotation( r.Y * a, r.P * a, r.R * a ); }
inline Vec3 operator*		( const Vec3& v, const Rotation& r )		{ return v * r.GetMatrix(); }
inline Vec4 operator*		( const Vec4& v, const Rotation& r )		{ return v * r.GetMatrix(); }
inline Rotation operator/	( const Rotation& r, float a )				{ return Rotation( r.Y / a, r.P / a, r.R / a ); }
inline bool operator ==	( const Rotation& a, const Rotation& b )	{ return fleq( a.Y, b.Y ) && fleq( a.P, b.P ) && fleq( a.R, b.R ); }
inline bool operator !=	( const Rotation& a, const Rotation& b )	{ return !( a == b ); }


#endif