#ifndef RGB_BUFFER_H
#define RGB_BUFFER_H

#include "Common.h"
#include "Math/Vec3.h"
#include "Engine/Color.h"

#define MAX_WIDTH 1600
#define MAX_HEIGHT 1200
//

struct Dot{
	int X;
	int Y;
	float Z;
	Dot() : X(0), Y(0), Z(1.0f){}
	Dot( int x, int y, float z = 1.0f ) : X(x), Y(y), Z(z){}

	Dot operator += ( const Dot& d ){ X += d.X; Y += d.Y; Z += d.Z; return *this; }
	Dot operator -= ( const Dot& d ){ X -= d.X; Y -= d.Y; Z -= d.Z; return *this; }
	Dot operator *= ( int a ){ X *= a; Y *= a; Z *= a; return *this; }
	Dot operator /= ( int a ){ X /= a; Y /= a; Z /= a; return *this; }


	inline float Len()		const { return ( float ) sqrt( Norm() ); }
	inline float Norm()		const { return ( float ) ( X*X + Y*Y + Z*Z ); }
	inline Vec3 Normalize()	{ 
		float len = Len();
		return Vec3( X / len, Y / len, Z / len ); 
	}


	inline bool Check( int width, int height ) const { return Z >= 0.1f && 0 < X && X < width && 0 < Y && Y < height; }
//	inline bool Check( int width, int height ) const { return 0 < X && X < width && 0 < Y && Y < height; }
};

inline Dot operator + ( const Dot& a, const Dot& b ){ return Dot( a.X + b.X, a.Y + b.Y, a.Z + b.Z ); }
inline Dot operator - ( const Dot& a, const Dot& b ){ return Dot( a.X - b.X, a.Y - b.Y, a.Z - b.Z ); }
inline Vec3 operator ^ ( const Dot& a, const Dot& b ){ return Vec3( a.Z * b.Y - a.Y * b.Z, a.X * b.Z - a.Z * b.X, a.Y * b.X - a.X * b.Y ); }
inline Dot operator * ( const Dot& d, int a ){ return Dot( d.X * a, d.Y * a, d.Z * a ); }
inline Dot operator / ( const Dot& d, int a ){ return Dot( d.X / a, d.Y / a, d.Z / a ); }
inline bool operator == ( const Dot& a, const Dot& b ){ return a.X == b.X && a.Y == b.Y; }
inline bool operator != ( const Dot& a, const Dot& b ){ return !( a == b ); }
inline int Det( const Dot& a, const Dot& b ){ return det2x2( a.X, a.Y, b.X, b.Y ); }

typedef Color Map[MAX_WIDTH * MAX_HEIGHT];
typedef float ZBuff[MAX_WIDTH * MAX_HEIGHT];

class RGBBuffer {
protected:
	uint _width;
	uint _height;
	float _aspect;

	Map _map;
	ZBuff _z;

	Color _bgColor;
	
public:
	RGBBuffer( uint width, uint height, const Color& bg = Color::BLACK );
	~RGBBuffer() {}

	void Clear();
	void Resize( uint width, uint height );

	inline Color Get( const Dot& dot ) { if( dot.Check( _width, _height ) ) return _map[ dot.Y * _width + dot.X ]; else return Color::WHITE; }
	inline void Set( const Dot& dot, const Color& col ) { 
		if( dot.Check( _width, _height ) ){
			int i = dot.Y * _width + dot.X;
			if( dot.Z < _z[i] ) {
				_map[i] = col; 
				_z[i] = dot.Z;
			}
		}
	}

	void Draw();
};

#endif
