#include "Common.h"
#include "Vec3.h"

const Vec3 Vec3::ZERO	( 0.0f, 0.0f, 0.0f );
const Vec3 Vec3::UP		( 0.0f, 1.0f, 0.0f );
const Vec3 Vec3::DOWN	( 0.0f,-1.0f, 0.0f );
const Vec3 Vec3::LEFT	( -1.0f, 0.0f, 0.0f );
const Vec3 Vec3::RIGHT	( 1.0f, 0.0f, 0.0f );
const Vec3 Vec3::FORWARD( 0.0f, 0.0f, -1.0f );
const Vec3 Vec3::BACK	( 0.0f, 0.0f, 1.0f );

Vec3 Vec3::operator +=( const Vec3& v ){
	X += v.X;
	Y += v.Y;
	Z += v.Z;
	return *this;
}

Vec3 Vec3::operator -=( const Vec3& v ){
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;
	return *this;
}

Vec3 Vec3::operator *=( float a ){
	X *= a;
	Y *= a;
	Z *= a;
	return *this;
}

Vec3 Vec3::operator /=( float a ){
	X /= a;
	Y /= a;
	Z /= a;
	return *this;
}

Vec3 Vec3::Normalize(){
	float len = Len();
	X /= len;
	Y /= len;
	Z /= len;
	return *this;
}
