#ifndef BASICS_H
#define BASICS_H

#include "Common.h"

static const float PI = 3.1415926535897932384626433832795f; // Oh fuck...
#define degree(radian) ((radian)*180/PI)
#define radian(degree) ((degree)*PI/180)

static const float EPSILON = 1E-7f;

#define fleq( a,b ) ( fabs( ( a ) - ( b ) ) <= EPSILON )
#define det2x2( a11, a12, a21, a22 ) ( ( a11 )*( a22 ) - ( a12 )*( a21 ) )

template< typename T >
T Max( const T& a, const T& b ){
	return (a > b)? a : b;
}
template< typename T >
T Min( const T& a, const T& b ){
	return (a < b)? a : b;
}
inline int abs( uint x ){
	return (x < 0) ? -x : x;
}

template< typename T >
void Swap( T& a, T& b ){
	T temp = b;
	b = a;
	a = temp;
}

#endif