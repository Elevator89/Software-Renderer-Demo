#ifndef QUAT_H
#define QUAT_H

#include "Common.h"
#include "Basics.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matr4.h"

class Quat{
public:
	Vec3 vec;
	float w;

	Quat(): vec(), w( 1.0f ) {}
	Quat( const float X, const float Y, const float Z, const float W ): vec( X, Y, Z ), w( W ) {}
	Quat( const Vec3& Vec, const float W = 0.0f ): vec( Vec ), w( W ) {}
	Quat( const Vec4& Vec, const float W = 0.0f ): vec( Vec.X, Vec.Y, Vec.Z ), w( W ) {}
	Quat( const Quat& quat ): vec( quat.vec ), w( quat.w ) {}

	Quat operator += ( const Quat& v );
	Quat operator -= ( const Quat& v );
	Quat operator *= ( float a );
	Quat operator /= ( float a );
	Quat operator *= ( const Quat& q );

	inline float Len()	const { return sqrt( Norm() ); }
	inline float Norm()	const { return vec*vec + w*w; }
	Matr4 GetMatrix() const;

	Quat Normalize();
	Quat Invert();
	Quat Conjugate();

	void GetAxisRot( Vec3& axis, float& angle ) const;

	static const Quat IDENTITY;
	static Quat CreateQuat( const Vec3& axis, float angle );
};

inline Quat Vec3ToQuat( const Vec3& vec )	{ return Quat( vec ); }
inline Quat Vec4ToQuat( const Vec4& vec )	{ return Quat( vec ); }
inline Vec3 QuatToVec3( const Quat& quat )	{ return Vec3( quat.vec ); }
inline Vec4 QuatToVec4( const Quat& quat )	{ return Vec4( quat.vec.X, quat.vec.Y, quat.vec.Z, 0.0f ); }

inline float Inner( const Quat& a, const Quat& b )		{ return a.vec * b.vec + a.w * b.w; }

inline Quat operator-	( const Quat& q )					{ return Quat( -q.vec, -q.w ); }
inline Quat operator+	( const Quat& a, const Quat& b )	{ return Quat( a.vec + b.vec, a.w + b.w ); }
inline Quat operator-	( const Quat& a, const Quat& b )	{ return Quat( a.vec - b.vec, a.w - b.w ); }
inline Quat operator*	( const Quat& q, float a )			{ return Quat( q.vec * a, q.w * a ); }
inline Quat operator/	( const Quat& q, float a )			{ return Quat( q.vec / a, q.w / a ); }
inline Quat operator*	( const Quat& a, const Quat& b )	{ 
	//Vec3 b1 = b.vec * a.w;
	//Vec3 a1 = a.vec * b.w;
	//Vec3 ab = a.vec ^ b.vec;
	//Vec3 res = a1 + b1 + ab;
	//Vec3 xxx = b.vec * a.w + a.vec * b.w + ( a.vec ^ b.vec );

	return Quat(a.w*b.vec.X + a.vec.X*b.w + a.vec.Y*b.vec.Z - a.vec.Z*b.vec.Y,
				a.w*b.vec.Y + a.vec.Y*b.w + a.vec.Z*b.vec.X - a.vec.X*b.vec.Z,
				a.w*b.vec.Z + a.vec.Z*b.w + a.vec.X*b.vec.Y - a.vec.Y*b.vec.X,
				a.w*b.w - a.vec.X*b.vec.X - a.vec.Y*b.vec.Y - a.vec.Z*b.vec.Z );

	//return Quat( a.vec.X*b.vec.X - a.vec.Y*b.vec.Y - a.vec.Z*b.vec.Z - a.w*b.w,
	//			 a.vec.X*b.vec.Y + b.vec.X*a.vec.Y + a.vec.Z*b.w	 - b.vec.Z*a.w,
	//			 a.vec.X*b.vec.Z + b.vec.X*a.vec.Z + a.w*b.vec.Y	 - a.vec.Y*b.w,
	//			 a.vec.X*b.w	 + b.vec.X*a.w	   + a.vec.Y*b.vec.Z - a.vec.Z*b.vec.Y );
}
inline Vec3 operator*	( const Vec3& b, const Quat& a )	{ Quat _a = a; return QuatToVec3( a * Vec3ToQuat( b ) * _a.Invert() ); }
inline Vec4 operator*	( const Vec4& b, const Quat& a )	{ Quat _a = a; return QuatToVec4( a * Vec4ToQuat( b ) * _a.Invert() ); }

inline bool operator ==	( const Quat& a, const Quat& b )	{ return a.vec == b.vec && fleq( a.w, b.w ); }
inline bool operator !=	( const Quat& a, const Quat& b )	{ return !( a == b ); }

Quat Slerp( const Quat& a, const Quat& b, float t );

#endif
