#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Common.h"
#include "Math.h"

class Transform {
public:
	Vec3 Vec;
	Rotation Rot;

	Transform(): Vec(), Rot() {}
	Transform( const Vec3& vec, const Rotation rot ): Vec( vec ), Rot( rot ){}
	Transform( const Transform& transform ): Vec( transform.Vec ), Rot( transform.Rot ){}
	~Transform() {}

	Transform operator += ( const Transform& tf );
	Transform operator -= ( const Transform& tf );
	Transform operator *= ( const Transform& tf );
	Transform operator *= ( const float a );

	Matr4 GetMatrix() const;
	Matr4 GetCamMatrix() const;
};

inline Transform operator + ( const Transform& a, const Transform& b ){
	return Transform( a.Vec + b.Vec, a.Rot + b.Rot );
}

inline Transform operator - ( const Transform& a, const Transform& b ){
	return Transform( a.Vec - b.Vec, a.Rot - b.Rot );
}

inline Transform operator * ( const Transform& a, const Transform& b ){
	return Transform( a.Vec + b.Vec * a.Rot, a.Rot + b.Rot );
}

inline Transform operator * ( const Transform& tf, const float a ){
	return Transform( tf.Vec * a, tf.Rot * a );
}

#endif