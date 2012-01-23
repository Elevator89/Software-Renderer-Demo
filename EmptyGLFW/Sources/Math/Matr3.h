#ifndef MATR3_H
#define MATR3_H

#include "Common.h"
#include "Basics.h"
#include "Vec3.h"

#pragma pack(push, 1)

class Matr3
{
public:
	Vec3 col1, col2, col3;

	Matr3():
		col1( 1.0f, 0.0f, 0.0f ),
		col2( 0.0f, 1.0f, 0.0f ),
		col3( 0.0f, 0.0f, 1.0f )
		{}
	Matr3( const Matr3& m ):
		col1( m.col1 ),
		col2( m.col2 ),
		col3( m.col3 )
		{}
	Matr3( const Vec3& Col1, const Vec3& Col2, const Vec3& Col3 ):
		col1( Col1 ),
		col2( Col2 ),
		col3( Col3 )
		{}

	Matr3 operator += ( const Matr3& v );
	Matr3 operator -= ( const Matr3& v );
	Matr3 operator *= ( float a );
	Matr3 operator /= ( float a );

	float Det() const;
	inline float* Array() const { (float*)&col1; }

	Matr3 Transpose();
	Matr3 GetTransposed();

	static const Matr3 ZERO;
	static const Matr3 IDENTITY;
};

#pragma pack(pop)


inline Matr3 operator-	( const Matr3& v )					{ return Matr3( -v.col1, -v.col2, -v.col3 ); }
inline Matr3 operator+	( const Matr3& a, const Matr3& b )	{ return Matr3( a.col1 + b.col1, a.col2 + b.col2, a.col3 + b.col3 ); }
inline Matr3 operator-	( const Matr3& a, const Matr3& b )	{ return Matr3( a.col1 - b.col1, a.col2 - b.col2, a.col3 - b.col3 ); }
inline Matr3 operator*	( const Matr3& m, float a )			{ return Matr3( m.col1 * a, m.col2 * a, m.col3 * a ); }
inline Matr3 operator/	( const Matr3& m, float a )			{ return Matr3( m.col1 / a, m.col2 / a, m.col3 / a ); }
inline bool operator ==	( const Matr3& a, const Matr3& b )	{ return a.col1 == b.col1 && a.col2 == b.col2 && a.col3 == b.col3; }
inline bool operator !=	( const Matr3& a, const Matr3& b )	{ return !( a == b ); }

inline Matr3 operator*	( const Matr3& a, const Matr3& b ){
	return Matr3(
		Vec3(
			a.col1.X * b.col1.X + a.col2.X * b.col1.Y + a.col3.X * b.col1.Z,
			a.col1.Y * b.col1.X + a.col2.Y * b.col1.Y + a.col3.Y * b.col1.Z,
			a.col1.Z * b.col1.X + a.col2.Z * b.col1.Y + a.col3.Z * b.col1.Z
		),
		Vec3(
			a.col1.X * b.col2.X + a.col2.X * b.col2.Y + a.col3.X * b.col2.Z,
			a.col1.Y * b.col2.X + a.col2.Y * b.col2.Y + a.col3.Y * b.col2.Z,
			a.col1.Z * b.col2.X + a.col2.Z * b.col2.Y + a.col3.Z * b.col2.Z
		),
		Vec3(
			a.col1.X * b.col3.X + a.col2.X * b.col3.Y + a.col3.X * b.col3.Z,
			a.col1.Y * b.col3.X + a.col2.Y * b.col3.Y + a.col3.Y * b.col3.Z,
			a.col1.Z * b.col3.X + a.col2.Z * b.col3.Y + a.col3.Z * b.col3.Z
		)
	);
}

inline Vec3 operator*	( const Matr3& m, const Vec3& v ){
	return 	Vec3(
		m.col1.X * v.X + m.col2.X * v.Y + m.col3.X * v.Z,
		m.col1.Y * v.X + m.col2.Y * v.Y + m.col3.Y * v.Z,
		m.col1.Z * v.X + m.col2.Z * v.Y + m.col3.Z * v.Z
	);
}

#endif
