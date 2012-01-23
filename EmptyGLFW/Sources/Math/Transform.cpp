#include "Common.h"
#include "Transform.h"

Transform Transform::operator += ( const Transform& tf ){
	Vec += tf.Vec;
	Rot += tf.Rot;
	return *this;
}

Transform Transform::operator -= ( const Transform& tf ){
	Vec -= tf.Vec;
	Rot -= tf.Rot;
	return *this;

}

Transform Transform::operator *= ( const Transform& tf ){
	Vec += tf.Vec * Rot;
	Rot += tf.Rot;
	return *this;
}

Transform Transform::operator *= ( const float a ){
	Vec *= a;
	Rot *= a;
	return *this;
}


Matr4 Transform::GetMatrix() const {
	Matr4 matr = Rot.GetMatrix();
	matr.col4 = Vec4( Vec, 1.0f );
	return matr;
}


Matr4 Transform::GetCamMatrix() const {
	//Matr4 rot = Rot.GetMatrix();

	//Matr4 trans(
	//	Vec4( 1.0f, 0.0f, 0.0f, 0.0f),
	//	Vec4( 0.0f, 1.0f, 0.0f, 0.0f),
	//	Vec4( 0.0f, 0.0f, 1.0f, 0.0f),
	//	Vec4( -Vec.X, -Vec.Y, -Vec.Z, 1.0f)
	//);

	Matr4 matr = Rot.GetMatrix();
	matr.col4.X = - Vec.X * matr.col1.X - Vec.Y * matr.col2.X - Vec.Z * matr.col3.X;
	matr.col4.Y = - Vec.X * matr.col1.Y - Vec.Y * matr.col2.Y - Vec.Z * matr.col3.Y;
	matr.col4.Z = - Vec.X * matr.col1.Z - Vec.Y * matr.col2.Z - Vec.Z * matr.col3.Z;
	return matr;
}
