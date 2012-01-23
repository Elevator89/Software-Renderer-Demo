#ifndef VEC4_H
#define VEC4_H

#include "Common.h"
#include "Basics.h"
#include "Vec3.h"

#pragma pack(push, 1)

class Vec4{
public:
	float X,Y,Z,W;

	Vec4(): X( 0.0f ), Y( 0.0f ), Z( 0.0f ), W( 1.0f ) {}
	Vec4( const float x, const float y, const float z, const float w ): X( x ), Y( y ), Z( z ), W( w ) {}
	Vec4( const Vec4& vec ): X( vec.X ), Y( vec.Y ), Z( vec.Z ), W( vec.W ) {}
	Vec4( const Vec3& vec, float w = 1.0f ): X( vec.X ), Y( vec.Y ), Z( vec.Z ), W( w ) {}

	Vec4 operator += ( const Vec4& v );
	Vec4 operator -= ( const Vec4& v );
	Vec4 operator *= ( float a );
	Vec4 operator /= ( float a );

	inline float Len()		const { return ( float ) sqrt( Norm() ); }
	inline float Norm()		const { return ( float ) ( X*X + Y*Y + Z*Z + W*W ); }
	inline float* Array()	const { return (float*)&X; }

	Vec4 Normalize();

	static const Vec4 ZERO_VEC;
	static const Vec4 ZERO_POINT;

	static const Vec4 UP;
	static const Vec4 DOWN;
	static const Vec4 LEFT;
	static const Vec4 RIGHT;
	static const Vec4 FORWARD;
	static const Vec4 BACK;

};

#pragma pack(pop)


inline Vec4 operator-	( const Vec4& v )					{ return Vec4( -v.X, -v.Y, -v.Z, -v.W ); }
inline Vec4 operator+	( const Vec4& a, const Vec4& b )	{ return Vec4( a.X + b.X, a.Y + b.Y, a.Z + b.Z, a.W + b.W ); }
inline Vec4 operator-	( const Vec4& a, const Vec4& b )	{ return Vec4( a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W ); }
inline Vec4 operator*	( const Vec4& v, float a )			{ return Vec4( v.X * a, v.Y * a, v.Z * a, v.W * a ); }
inline Vec4 operator/	( const Vec4& v, float a )			{ return Vec4( v.X / a, v.Y / a, v.Z / a, v.W / a ); }
inline Vec4 operator^	( const Vec4& a, const Vec4& b )	{ return Vec4( a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X, a.W ); }
inline float operator*	( const Vec4& a, const Vec4& b )	{ return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W; }
inline bool operator ==	( const Vec4& a, const Vec4& b )	{ return fleq( a.X, b.X ) && fleq( a.Y, b.Y ) && fleq( a.Z, b.Z ) && fleq( a.W, b.W ); }
inline bool operator !=	( const Vec4& a, const Vec4& b )	{ return !( a == b ); }

Vec4 ToQuat( const Vec4& rot );
Vec4 ToRot( const Vec4& quat );

#endif
