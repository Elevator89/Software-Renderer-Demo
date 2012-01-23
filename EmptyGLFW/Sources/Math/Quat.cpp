#include "Common.h"
#include "Quat.h"

const Quat Quat::IDENTITY	( 0.0f, 0.0f, 0.0f, 1.0f );

Quat Quat::operator +=( const Quat& v ){
	vec += v.vec;
	w += v.w;
	return *this;
}

Quat Quat::operator -=( const Quat& v ){
	vec -= v.vec;
	w -= v.w;
	return *this;
}

Quat Quat::operator *=( float a ){
	vec *= a;
	w *= a;
	return *this;
}

Quat Quat::operator /=( float a ){
	vec /= a;
	w /= a;
	return *this;
}

Quat Quat::operator *= ( const Quat& a ){
	Vec3 v( vec );
	vec = ( v ^ a.vec ) + a.vec * w + v * a.w;
	w = w * a.w - v * a.vec;
	return *this;
}


Quat Quat::Normalize(){
	float len = Len();
	vec /= len;
	w /= len;
	return *this;
}

Quat Quat::Conjugate() {
	vec *= -1.0f;
	return *this;
}

Quat Quat::Invert() {
	float n = Norm();
	Conjugate() /= n;
	return *this;
}

Quat Quat::CreateQuat( const Vec3& axis, float angle ) {
    float sinA = sin( 0.5f * angle );
    float cosA = cos( 0.5f * angle );
	return Quat( axis * sinA, cosA );
}

void Quat::GetAxisRot( Vec3& axis, float& angle ) const {
	float len = Len();
	if( w < 0.0f )
		angle = 2.0f*(float)atan2(-len, -w); //-PI,0 
	else
		angle = 2.0f*(float)atan2( len,  w); //0,PI 
	axis = vec / len;
}

Quat Slerp( const Quat& a, const Quat& b, float t ){
	// =  (b sin((1Цt)a) Ц a sin(ta)) / sin(a) 

	Vec4 p1;
	double omega, cosom, sinom, scale0, scale1;

	// косинус угла
	cosom = Inner( a , b );
	if ( cosom < 0.0 ){
		cosom = -cosom;
		p1 = -QuatToVec4( b );
		p1.W = -b.w;
	} else {
		p1 = QuatToVec4( b );
		p1.W = b.w;
	}

	if ( ( 1.0 - cosom ) > EPSILON ) {
		// стандартный случай (slerp)
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	} else {
		// если маленький угол - линейна€ интерпол€ци€
		scale0 = 1.0 - t;
		scale1 = t;
	}
	return Quat(
		scale0 * a.vec.X + scale1 * p1.X,
		scale0 * a.vec.Y + scale1 * p1.Y,
		scale0 * a.vec.Z + scale1 * p1.Z,
		scale0 * a.w	 + scale1 * p1.W 
	);
}

Matr4 Quat::GetMatrix() const {
	float wx, wy, wz, xx, yy, yz, xy, xz, zz;
	xx = vec.X * vec.X;
	xy = vec.X * vec.Y;
	xz = vec.X * vec.Z;
	yy = vec.Y * vec.Y;
	yz = vec.Y * vec.Z;
	zz = vec.Z * vec.Z;

	wx = vec.X * w;
	wy = vec.X * w;
	wz = vec.X * w;

	return Matr4(
		Vec4( 1.0f - 2.0f * ( yy + zz ), 2.0f * ( xy + wz ), 2.0f * ( xz - wy ), 0.0f ),
		Vec4( 2.0f * ( xy - wz ), 1.0f - 2.0f * ( xx + zz ), 2.0f * ( yz + wx ), 0.0f ),
		Vec4( 2.0f * ( xz + wy ), 2.0f * ( yz - wx ), 1.0f - 2.0f * ( xx + yy ), 0.0f ),
		Vec4( 0.0f, 0.0f, 0.0f, 1.0f )
	);
}
