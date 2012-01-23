#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "Renderer.h"

class GlRenderer: public Renderer {
public:
	GlRenderer( int width, int height, const Color& bgColor );
	~GlRenderer();

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
	virtual void InitSelf();
	virtual void DisposeSelf();
};

#endif