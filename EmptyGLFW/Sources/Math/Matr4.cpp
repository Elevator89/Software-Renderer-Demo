#include "Common.h"
#include "Matr4.h"

const Matr4 Matr4::ZERO		= Matr4();
const Matr4 Matr4::IDENTITY	= Matr4(
	Vec4( 1.0f, 0.0f, 0.0f, 0.0f ), 
	Vec4( 0.0f, 1.0f, 0.0f, 0.0f ), 
	Vec4( 0.0f, 0.0f, 1.0f, 0.0f ), 
	Vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );

Matr4 Matr4::operator += ( const Matr4& v ){
	col1 += v.col1;
	col2 += v.col2;
	col3 += v.col3;
	col4 += v.col4;
	return *this;
}

Matr4 Matr4::operator -= ( const Matr4& v ){
	col1 -= v.col1;
	col2 -= v.col2;
	col3 -= v.col3;
	col4 -= v.col4;
	return *this;
}

Matr4 Matr4::operator *= ( const Matr4& m ){
	col1 = Vec4(
		col1.X * m.col1.X + col2.X * m.col1.Y + col3.X * m.col1.Z + col4.X * m.col1.W,
		col1.Y * m.col1.X + col2.Y * m.col1.Y + col3.Y * m.col1.Z + col4.Y * m.col1.W,
		col1.Z * m.col1.X + col2.Z * m.col1.Y + col3.Z * m.col1.Z + col4.Z * m.col1.W,
		col1.W * m.col1.X + col2.W * m.col1.Y + col3.W * m.col1.Z + col4.W * m.col1.W
	);
	col2 = Vec4(
		col1.X * m.col2.X + col2.X * m.col2.Y + col3.X * m.col2.Z + col4.X * m.col2.W,
		col1.Y * m.col2.X + col2.Y * m.col2.Y + col3.Y * m.col2.Z + col4.Y * m.col2.W,
		col1.Z * m.col2.X + col2.Z * m.col2.Y + col3.Z * m.col2.Z + col4.Z * m.col2.W,
		col1.W * m.col2.X + col2.W * m.col2.Y + col3.W * m.col2.Z + col4.W * m.col2.W
	);
	col3 = Vec4(
		col1.X * m.col3.X + col2.X * m.col3.Y + col3.X * m.col3.Z + col4.X * m.col3.W,
		col1.Y * m.col3.X + col2.Y * m.col3.Y + col3.Y * m.col3.Z + col4.Y * m.col3.W,
		col1.Z * m.col3.X + col2.Z * m.col3.Y + col3.Z * m.col3.Z + col4.Z * m.col3.W,
		col1.W * m.col3.X + col2.W * m.col3.Y + col3.W * m.col3.Z + col4.W * m.col3.W
	);
	col4 = Vec4(
		col1.X * m.col4.X + col2.X * m.col4.Y + col3.X * m.col4.Z + col4.X * m.col4.W,
		col1.Y * m.col4.X + col2.Y * m.col4.Y + col3.Y * m.col4.Z + col4.Y * m.col4.W,
		col1.Z * m.col4.X + col2.Z * m.col4.Y + col3.Z * m.col4.Z + col4.Z * m.col4.W,
		col1.W * m.col4.X + col2.W * m.col4.Y + col3.W * m.col4.Z + col4.W * m.col4.W
	);
	return *this;
}


Matr4 Matr4::operator *= ( float a ){
	col1 *= a;
	col2 *= a;
	col3 *= a;
	col4 *= a;
	return *this;
}

Matr4 Matr4::operator /= ( float a ){
	col1 /= a;
	col2 /= a;
	col3 /= a;
	col4 /= a;
	return *this;
}

float Matr4::Det() const { 
	return
		col1.X * col2.Y * col3.Z +
		col1.Z * col2.X * col3.Y +
		col1.Y * col2.Z * col3.X -
		col1.Z * col2.Y * col3.X -
		col1.Y * col2.X * col3.Z -
		col1.X * col2.Z * col3.Y;
}

Matr4 Matr4::Transpose() {
	Vec4 c1 = Vec4( col1.X, col2.X, col3.X, col4.X );
	Vec4 c2 = Vec4( col1.Y, col2.Y, col3.Y, col4.Y );
	Vec4 c3 = Vec4( col1.Z, col2.Z, col3.Z, col4.Z );
	Vec4 c4 = Vec4( col1.W, col2.W, col3.W, col4.W );
	col1 = c1;
	col2 = c2;
	col3 = c3;
	col4 = c4;
	return *this;
}

Matr4 Matr4::GetTransposed() {
	return Matr4( 
		Vec4( col1.X, col2.X, col3.X, col4.X ),
		Vec4( col1.Y, col2.Y, col3.Y, col4.Y ),
		Vec4( col1.Z, col2.Z, col3.Z, col4.Z ),
		Vec4( col1.W, col2.W, col3.W, col4.W )
	);
}
