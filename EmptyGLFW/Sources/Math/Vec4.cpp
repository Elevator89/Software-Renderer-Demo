#include "Common.h"
#include "Vec4.h"

const Vec4 Vec4::ZERO_VEC	( 0.0f, 0.0f, 0.0f, 0.0f );
const Vec4 Vec4::ZERO_POINT	( 0.0f, 0.0f, 0.0f, 1.0f );
const Vec4 Vec4::UP			( 0.0f, 1.0f, 0.0f, 0.0f );
const Vec4 Vec4::DOWN		( 0.0f,-1.0f, 0.0f, 0.0f );
const Vec4 Vec4::LEFT		( -1.0f, 0.0f, 0.0f, 0.0f );
const Vec4 Vec4::RIGHT		( 1.0f, 0.0f, 0.0f, 0.0f );
const Vec4 Vec4::FORWARD	( 0.0f, 0.0f, 1.0f, 0.0f );
const Vec4 Vec4::BACK		( 0.0f, 0.0f, -1.0f, 0.0f );

Vec4 Vec4::operator +=( const Vec4& v ){
	X += v.X;
	Y += v.Y;
	Z += v.Z;
	W += v.W;
	return *this;
}

Vec4 Vec4::operator -=( const Vec4& v ){
	X -= v.X;
	Y -= v.Y;
	Z -= v.Z;
	W -= v.W;
	return *this;
}

Vec4 Vec4::operator *=( float a ){
	X *= a;
	Y *= a;
	Z *= a;
	W *= a;
	return *this;
}

Vec4 Vec4::operator /=( float a ){
	X /= a;
	Y /= a;
	Z /= a;
	W /= a;
	return *this;
}

Vec4 Vec4::Normalize(){
	float len = Len();
	X /= len;
	Y /= len;
	Z /= len;
	W /= len;
	return *this;
}

Vec4 ToQuat( const Vec4& rot ){
    float sin_a = sin( 0.5f * rot.W );
    float cos_a = cos( 0.5f * rot.W );
	return Vec4( rot.X * sin_a, rot.Y * sin_a, rot.Z * sin_a, cos_a );
}

Vec4 ToRot( const Vec4& quat ){
	float len = quat.Len();
	float angle;
	if( quat.W < 0.0f )
		angle = 2.0f*(float)atan2(-len, -quat.W); //-PI,0 
	else
		angle = 2.0f*(float)atan2( len,  quat.W); //0,PI 
	return Vec4( quat.X / len, quat.Y / len, quat.Z / len, angle );
}

