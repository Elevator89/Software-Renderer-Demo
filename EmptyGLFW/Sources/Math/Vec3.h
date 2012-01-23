#ifndef VEC3_H
#define VEC3_H

#include "Common.h"
#include "Basics.h"

#pragma pack(push, 1)

class Vec3{
public:
	float X,Y,Z;

	Vec3(): X( 0.0f ), Y( 0.0f ), Z( 0.0f ) {}
	Vec3( const float x, const float y, const float z ): X( x ), Y( y ), Z( z ) {}
	Vec3( const Vec3& vec ): X( vec.X ), Y( vec.Y ), Z( vec.Z ) {}

	Vec3 operator += ( const Vec3& v );
	Vec3 operator -= ( const Vec3& v );
	Vec3 operator *= ( float a );
	Vec3 operator /= ( float a );

	inline float Len()		const { return ( float ) sqrt( Norm() ); }
	inline float Norm()		const { return ( float ) ( X*X + Y*Y + Z*Z ); }
	inline float* Array()	const { return (float*)&X; }

	Vec3 Normalize();


	static const Vec3 ZERO;
	static const Vec3 UP;
	static const Vec3 DOWN;
	static const Vec3 LEFT;
	static const Vec3 RIGHT;
	static const Vec3 FORWARD;
	static const Vec3 BACK;

};

#pragma pack(pop)


inline Vec3 operator-	( const Vec3& v )					{ return Vec3( -v.X, -v.Y, -v.Z ); }
inline Vec3 operator+	( const Vec3& a, const Vec3& b )	{ return Vec3( a.X + b.X, a.Y + b.Y, a.Z + b.Z ); }
inline Vec3 operator-	( const Vec3& a, const Vec3& b )	{ return Vec3( a.X - b.X, a.Y - b.Y, a.Z - b.Z ); }
inline Vec3 operator*	( const Vec3& v, float a )			{ return Vec3( v.X * a, v.Y * a, v.Z * a ); }
inline Vec3 operator/	( const Vec3& v, float a )			{ return Vec3( v.X / a, v.Y / a, v.Z / a ); }
																			//az*by-ay*bz; ax*bz-az*bx; cz = ay*bx-ax*by;
inline Vec3 operator^	( const Vec3& a, const Vec3& b )	{ return Vec3( a.Z * b.Y - a.Y * b.Z, a.X * b.Z - a.Z * b.X, a.Y * b.X - a.X * b.Y ); }
//inline Vec3 operator^	( const Vec3& a, const Vec3& b )	{ return Vec3( a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X ); }
inline float operator*	( const Vec3& a, const Vec3& b )	{ return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }
inline bool operator ==	( const Vec3& a, const Vec3& b )	{ return fleq( a.X, b.X ) && fleq( a.Y, b.Y ) && fleq( a.Z, b.Z ); }
inline bool operator !=	( const Vec3& a, const Vec3& b )	{ return !( a == b ); }

#endif
