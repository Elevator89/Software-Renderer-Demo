#ifndef VEC3_H
#define VEC3_H

#include "Common.h"
#include "Basics.h"

enum Coord{ X = 0, Y = 1, Z = 2, W = 3};

class Vec3{
public:
	float v[3];

	Vec3(){ v[X] = 0.0f; v[Y] = 0.0f; v[Z] = 0.0f; }
	Vec3( const float x, const float y, const float z ){ v[X] = x; v[Y] = y; v[Z] = z; }
	Vec3( const Vec3& vec ){ v[X] = vec.v[X]; v[Y] = vec.v[Y]; v[Z] = vec.v[Z]; }

	Vec3 operator += ( const Vec3& v );
	Vec3 operator -= ( const Vec3& v );
	Vec3 operator *= ( float a );
	Vec3 operator /= ( float a );

	inline float Len()	const { return ( float ) sqrt( Norm() ); }
	inline float Norm()	const { return ( float ) ( v[X]*v[X] + v[Y]*v[Y] + v[Z]*v[Z] ); }
	Vec3 Normalize();


	static const Vec3 ZERO;
	static const Vec3 UP;
	static const Vec3 DOWN;
	static const Vec3 LEFT;
	static const Vec3 RIGHT;
	static const Vec3 FORWARD;
	static const Vec3 BACK;

};

inline Vec3 operator-	( const Vec3& v )					{ return Vec3( -v[X], -v[Y], -v[Z] ); }
inline Vec3 operator+	( const Vec3& a, const Vec3& b )	{ return Vec3( a.v.[X] + b.v[X], a.v[Y] + b.v[Y], a.v[Z] + b.v[Z] ); }
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
