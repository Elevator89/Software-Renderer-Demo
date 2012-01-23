#ifndef MATR4_H
#define MATR4_H

#include "Common.h"
#include "Basics.h"
#include "Vec3.h"
#include "Vec4.h"

#pragma pack(push, 1)

class Matr4
{
public:
	Vec4 col1, col2, col3, col4;

	Matr4():
		col1( 1.0f, 0.0f, 0.0f, 0.0f ),
		col2( 0.0f, 1.0f, 0.0f, 0.0f ),
		col3( 0.0f, 0.0f, 1.0f, 0.0f ),
		col4( 0.0f, 0.0f, 0.0f, 1.0f )
		{}
	Matr4( const Matr4& m ):
		col1( m.col1 ),
		col2( m.col2 ),
		col3( m.col3 ),
		col4( m.col4 )
		{}
	Matr4( const Vec4& Col1, const Vec4& Col2, const Vec4& Col3, const Vec4& Col4 ):
		col1( Col1 ),
		col2( Col2 ),
		col3( Col3 ),
		col4( Col4 )
		{}

	Matr4 operator += ( const Matr4& v );
	Matr4 operator -= ( const Matr4& v );
	Matr4 operator *= ( const Matr4& m );
	Matr4 operator *= ( float a );
	Matr4 operator /= ( float a );

	float Det() const;
	Matr4 Transpose();
	Matr4 GetTransposed();
	inline float* Array() const { return (float*)&col1; }


	static const Matr4 ZERO;
	static const Matr4 IDENTITY;
};

#pragma pack(pop)

inline Matr4 operator-	( const Matr4& v )					{ return Matr4( -v.col1, -v.col2, -v.col3, -v.col4 ); }
inline Matr4 operator+	( const Matr4& a, const Matr4& b )	{ return Matr4( a.col1 + b.col1, a.col2 + b.col2, a.col3 + b.col3, a.col4 + b.col4 ); }
inline Matr4 operator-	( const Matr4& a, const Matr4& b )	{ return Matr4( a.col1 - b.col1, a.col2 - b.col2, a.col3 - b.col3, a.col4 - b.col4 ); }
inline Matr4 operator*	( const Matr4& m, float a )			{ return Matr4( m.col1 * a, m.col2 * a, m.col3 * a, m.col4 * a ); }
inline Matr4 operator/	( const Matr4& m, float a )			{ return Matr4( m.col1 / a, m.col2 / a, m.col3 / a, m.col4 / a ); }
inline bool operator ==	( const Matr4& a, const Matr4& b )	{ return a.col1 == b.col1 && a.col2 == b.col2 && a.col3 == b.col3 && a.col4 == b.col4; }
inline bool operator !=	( const Matr4& a, const Matr4& b )	{ return !( a == b ); }

inline Matr4 operator*	( const Matr4& a, const Matr4& b ){
	return Matr4(
		Vec4(
			a.col1.X * b.col1.X + a.col2.X * b.col1.Y + a.col3.X * b.col1.Z + a.col4.X * b.col1.W,
			a.col1.Y * b.col1.X + a.col2.Y * b.col1.Y + a.col3.Y * b.col1.Z + a.col4.Y * b.col1.W,
			a.col1.Z * b.col1.X + a.col2.Z * b.col1.Y + a.col3.Z * b.col1.Z + a.col4.Z * b.col1.W,
			a.col1.W * b.col1.X + a.col2.W * b.col1.Y + a.col3.W * b.col1.Z + a.col4.W * b.col1.W
		),
		Vec4(
			a.col1.X * b.col2.X + a.col2.X * b.col2.Y + a.col3.X * b.col2.Z + a.col4.X * b.col2.W,
			a.col1.Y * b.col2.X + a.col2.Y * b.col2.Y + a.col3.Y * b.col2.Z + a.col4.Y * b.col2.W,
			a.col1.Z * b.col2.X + a.col2.Z * b.col2.Y + a.col3.Z * b.col2.Z + a.col4.Z * b.col2.W,
			a.col1.W * b.col2.X + a.col2.W * b.col2.Y + a.col3.W * b.col2.Z + a.col4.W * b.col2.W
		),
		Vec4(
			a.col1.X * b.col3.X + a.col2.X * b.col3.Y + a.col3.X * b.col3.Z + a.col4.X * b.col3.W,
			a.col1.Y * b.col3.X + a.col2.Y * b.col3.Y + a.col3.Y * b.col3.Z + a.col4.Y * b.col3.W,
			a.col1.Z * b.col3.X + a.col2.Z * b.col3.Y + a.col3.Z * b.col3.Z + a.col4.Z * b.col3.W,
			a.col1.W * b.col3.X + a.col2.W * b.col3.Y + a.col3.W * b.col3.Z + a.col4.W * b.col3.W
		),
		Vec4(
			a.col1.X * b.col4.X + a.col2.X * b.col4.Y + a.col3.X * b.col4.Z + a.col4.X * b.col4.W,
			a.col1.Y * b.col4.X + a.col2.Y * b.col4.Y + a.col3.Y * b.col4.Z + a.col4.Y * b.col4.W,
			a.col1.Z * b.col4.X + a.col2.Z * b.col4.Y + a.col3.Z * b.col4.Z + a.col4.Z * b.col4.W,
			a.col1.W * b.col4.X + a.col2.W * b.col4.Y + a.col3.W * b.col4.Z + a.col4.W * b.col4.W
		)
	);
}

inline Vec4 operator*	( const Vec4& v, const Matr4& m ){
	return Vec4(
		m.col1.X * v.X + m.col1.Y * v.Y + m.col1.Z * v.Z + m.col1.W * v.W,
		m.col2.X * v.X + m.col2.Y * v.Y + m.col2.Z * v.Z + m.col2.W * v.W,
		m.col3.X * v.X + m.col3.Y * v.Y + m.col3.Z * v.Z + m.col3.W * v.W,
		m.col4.X * v.X + m.col4.Y * v.Y + m.col4.Z * v.Z + m.col4.W * v.W
	);
}

inline Vec4 operator*	( const Matr4& m, const Vec4& v ){
	return Vec4(
		m.col1.X * v.X + m.col2.X * v.Y + m.col3.X * v.Z + m.col4.X * v.W,
		m.col1.Y * v.X + m.col2.Y * v.Y + m.col3.Y * v.Z + m.col4.Y * v.W,
		m.col1.Z * v.X + m.col2.Z * v.Y + m.col3.Z * v.Z + m.col4.Z * v.W,
		m.col1.W * v.X + m.col2.W * v.Y + m.col3.W * v.Z + m.col4.W * v.W
	);
}

inline Vec3 operator*	( const Vec3& v, const Matr4& m ){
	return Vec3(
		m.col1.X * v.X + m.col1.Y * v.Y + m.col1.Z * v.Z,
		m.col2.X * v.X + m.col2.Y * v.Y + m.col2.Z * v.Z,
		m.col3.X * v.X + m.col3.Y * v.Y + m.col3.Z * v.Z
	);
}

inline Vec3 operator*	( const Matr4& m, const Vec3& v ){
	return Vec3(
		m.col1.X * v.X + m.col2.X * v.Y + m.col3.X * v.Z,
		m.col1.Y * v.X + m.col2.Y * v.Y + m.col3.Y * v.Z,
		m.col1.Z * v.X + m.col2.Z * v.Y + m.col3.Z * v.Z
	);
}



#endif
