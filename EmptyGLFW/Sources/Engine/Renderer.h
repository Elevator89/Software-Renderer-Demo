#ifndef RENDERER_H
#define RENDERER_H

#include "Common.h"
#include "Math/Math.h"
#include "Interfaces/Interfaces.h"
#include "Color.h"
#include "Entities/LightDef.h"


class Renderer : public Initializable {
public:
	Renderer( int width, int height, const Color& bgColor );
	~Renderer();

	virtual void Resize( int newWidth, int newHeight );
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;
	virtual void Refresh( const Transform& tf ) = 0;

	virtual void Push() = 0;
	virtual void Pop() = 0;
	virtual void Load( const Matr4& model ) = 0;
	virtual void Mult( const Matr4& model ) = 0;

	virtual void DrawPoint( const Vec3& point, const Color& color, float size = 1.0f ) = 0;
	virtual void DrawLine( const Vec3& start, const Vec3& end, const Color& color ) = 0;
	virtual void DrawPolygon( const Vec3* vertices, uint count, const Color& color ) = 0;
	virtual void DrawPolygon( const Vec3* vertices, uint count, const Material& material ) = 0;
	virtual void DrawPolygons( const Vec3* vertices, uint polyCount, uint vertCount, const Material& material ) = 0;

protected:

	static const int MAX_LIGHTS_COUNT = 16;

	Color _bgColor;
	int _width;
	int _height;

	virtual void InitSelf() = 0;
	virtual void DisposeSelf() = 0;

};

#endif