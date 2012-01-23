#include "Common.h"
#include "Rotation.h"


Rotation Rotation::operator += ( const Rotation& rot ){
	Y += rot.Y;
	P += rot.P;
	R += rot.R;
	return *this;
}

Rotation Rotation::operator -= ( const Rotation& rot ){
	Y -= rot.Y;
	P -= rot.P;
	R -= rot.R;
	return *this;
}

Rotation Rotation::operator *= ( float a ){
	Y *= a;
	P *= a;
	R *= a;
	return *this;
}

Rotation Rotation::operator /= ( float a ){
	Y /= a;
	P /= a;
	R /= a;
	return *this;
}

Matr4 Rotation::GetMatrix() const{
	float sy = sin(Y);
	float cy = cos(Y);

	float sp = sin(P);
	float cp = cos(P);

	float sr = sin(R);
	float cr = cos(R);

	return Matr4(
		Vec4( cy*cr, -sp*sy*cr - cp*sr, -cp*sy*cr + sp*sr, 0.0f ),
		Vec4( cy*sr, -sp*sy*sr + cp*cr, -cp*sy*sr - sp*cr, 0.0f ),
		Vec4( sy,     sp*cy,             cp*cy,            0.0f ),
		Vec4( 0.0f,   0.0f,              0.0f,             1.0f )
	);
}
