#include "Common.h"
#include "Matr3.h"

const Matr3 Matr3::ZERO		= Matr3();
const Matr3 Matr3::IDENTITY	= Matr3(
	Vec3( 1.0f, 0.0f, 0.0f ), 
	Vec3( 0.0f, 1.0f, 0.0f ), 
	Vec3( 0.0f, 0.0f, 1.0f ) );

Matr3 Matr3::operator += ( const Matr3& v ){
	col1 += v.col1;
	col2 += v.col2;
	col3 += v.col3;
	return *this;
}

Matr3 Matr3::operator -= ( const Matr3& v ){
	col1 -= v.col1;
	col2 -= v.col2;
	col3 -= v.col3;
	return *this;
}

Matr3 Matr3::operator *= ( float a ){
	col1 *= a;
	col2 *= a;
	col3 *= a;
	return *this;
}

Matr3 Matr3::operator /= ( float a ){
	col1 /= a;
	col2 /= a;
	col3 /= a;
	return *this;
}

float Matr3::Det() const { 
	return
		col1.X * col2.Y * col3.Z +
		col1.Z * col2.X * col3.Y +
		col1.Y * col2.Z * col3.X -
		col1.Z * col2.Y * col3.X -
		col1.Y * col2.X * col3.Z -
		col1.X * col2.Z * col3.Y;
}

Matr3 Matr3::Transpose() {
	Vec3 c1 = Vec3( col1.X, col2.X, col3.X );
	Vec3 c2 = Vec3( col1.Y, col2.Y, col3.Y );
	Vec3 c3 = Vec3( col1.Z, col2.Z, col3.Z );
	col1 = c1;
	col2 = c2;
	col3 = c3;
	return *this;
}

Matr3 Matr3::GetTransposed() {
	return Matr3( 
		Vec3( col1.X, col2.X, col3.X ),
		Vec3( col1.Y, col2.Y, col3.Y ),
		Vec3( col1.Z, col2.Z, col3.Z )
	);
}
