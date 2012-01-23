#ifndef SOFWARE_RENDERER_H
#define SOFWARE_RENDERER_H

#include "Renderer.h"
#include "CpuRendering/RGBBuffer.h"

class CpuRenderer: public Renderer {
public:
	CpuRenderer( int width, int height, const Color& bgColor );
	~CpuRenderer();

	RGBBuffer buffer;

	virtual void Resize( int width, int height );
	virtual void BeginDraw();
	virtual void EndDraw();
	virtual void Refresh( const Transform& tf );

	virtual void Push();
	virtual void Pop();
	virtual void Load( const Matr4& model );
	virtual void Mult( const Matr4& model );

	virtual void DrawPoint( const Vec3& point, const Color& color, float size = 1.0f );
	virtual void DrawLine( const Vec3& start, const Vec3& end, const Color& color );
	virtual void DrawPolygon( const Vec3* vertices, uint count, const Color& color );
	virtual void DrawPolygon( const Vec3* vertices, uint count, const Material& material );
	virtual void DrawPolygons( const Vec3* vertices, uint polyCount, uint vertCount, const Material& material );

protected:

	static const int MAX_VERTEX_COUNT = 64;

	std::stack<Matr4> _matrStack;

	Matr4 _projection;
	Matr4 _model;
	Matr4 _composite;

	Vec4 lightCoordsCam[ 64 ];

	void Frustum( float left, float right, float top, float bottom, float near, float far );

	virtual void InitSelf();
	virtual void DisposeSelf();

	//void CropLine( const Dot& p0, const Dot& p1, const Color& color );
	//void CropPolygon( const Dot& p0, const Dot& p1, const Color& color );

	void DrawBitmapLine( const Dot& p0, const Dot& p1, const Color& color );
	void DrawBitmapPolygon( const Dot* dots, uint count, const Dot& center, const Color& color );

	inline Vec4 WorldToCam( const Vec3& world ){
		return _model * Vec4( world );
	}
	inline Vec4 CamToProjection( const Vec4& cam ){
		Vec4 screen = _projection * cam;
		return screen /= screen.W;
	}

	inline int GetScreenCoord( float c, int size ){ return int( ( c + 1.0f ) * float( size ) / 2.0f ); }
	inline Dot ProjecionToScreen( const Vec4& cam ){
		return Dot( GetScreenCoord( cam.X, _width ), GetScreenCoord( cam.Y, _height ), cam.Z );
	}

};

#endif