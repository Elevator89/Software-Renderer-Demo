#include "Common.h"
#include "CpuRenderer.h"

using namespace std;

float aspect;
float dx, dy;
float xs, ys;


CpuRenderer::CpuRenderer( int width, int height, const Color& bgColor ):
	Renderer( width, height, bgColor ),
	buffer( width, height, bgColor ),
	_projection(),
	_model()
{
	aspect = float(_width) / float(_height);
	xs = -aspect;
	ys = 1.0f;

	dx = 2.0f * aspect / float(_width);
	dy = -2.0f / float(_height);
}

CpuRenderer::~CpuRenderer(){}

void CpuRenderer::Frustum( float left, float right, float top, float bottom, float near, float far ){
	float r_l = right - left;
	float t_b = top - bottom;
	float f_n = far - near;
	_projection = Matr4::IDENTITY;
	_projection.col1.X = 2.0f * near / r_l;
	_projection.col2.Y = 2.0f * near / t_b;
	_projection.col3.X = ( right + left ) / r_l;
	_projection.col3.Y = ( top + bottom ) / t_b;
	_projection.col3.Z = -( far + near ) / f_n;
	_projection.col3.W = -1.0f;
	_projection.col4.Z = -2.0f * far * near / f_n;
	_projection.col4.W = 0.0f;
}


void CpuRenderer::InitSelf(){
	glfwSetMousePos( _width/2, _height/2 );
}

void CpuRenderer::DisposeSelf(){}

void CpuRenderer::Resize( int width, int height ){
	buffer.Resize( width, height );
	Renderer::Resize( width, height );

	aspect = float(_width) / float(_height);

	glLoadIdentity();
	gluOrtho2D( -aspect, aspect, -1.0f, 1.0f );
}


void CpuRenderer::BeginDraw(){
	buffer.Clear();

}

void CpuRenderer::EndDraw(){
	float xf, yf;
	yf = ys;

	buffer.Draw();

	glfwSwapBuffers();
}

void CpuRenderer::Refresh( const Transform& tf ){
	float aspect = float( _width ) / float( _height );
	Frustum( -aspect, aspect, -1.0f, 1.0f, 2.0f, 500.0f ); //пирамида отсечения сцены, генерация проекционной матрицы
	_model = tf.GetCamMatrix();
	_composite = _projection * _model;


	for( uint i = 0; i < LightDef::Count; ++i ){
		lightCoordsCam[i] = _model * Vec4( LightDef::lights[i]->Pos.Vec, 1.0f );
	}


}

void CpuRenderer::Push(){
	_matrStack.push( _model );
}
void CpuRenderer::Pop(){
	_model = _matrStack.top();
	_matrStack.pop();
}

void CpuRenderer::Load( const Matr4& model ){
	_model = model;
}

void CpuRenderer::Mult( const Matr4& model ){
	_model = _model * model;
	_composite = _projection * _model;
}

void CpuRenderer::DrawPoint( const Vec3& point, const Color& color, float size ){
	Dot dot = ProjecionToScreen( CamToProjection( WorldToCam( point ) ) );
	buffer.Set( dot, color );
}

void CpuRenderer::DrawLine( const Vec3& start, const Vec3& end, const Color& color ){
	Dot dot0 = ProjecionToScreen( CamToProjection( WorldToCam( start ) ) );
	Dot dot1 = ProjecionToScreen( CamToProjection( WorldToCam( end ) ) );
	DrawBitmapLine( dot0, dot1, color );
}

void CpuRenderer::DrawPolygon( const Vec3* vertices, uint count, const Color& color ){
	static Vec4 cam[MAX_VERTEX_COUNT];
	static Dot screen[MAX_VERTEX_COUNT];

	Vec4 center = Vec4::ZERO_VEC;
	for ( int i = 0; i < count; i++ )
		center += cam[i] = WorldToCam( vertices[i] );
	center /= count;

	for ( int i = 0; i < count; i++ )
		screen[i] = ProjecionToScreen( CamToProjection( cam[i] ) );
	Dot centerDot = ProjecionToScreen( CamToProjection( center ) );

	DrawBitmapPolygon( screen, count, centerDot, color );
}

void CpuRenderer::DrawPolygon( const Vec3* vertices, uint count, const Material& material ){
	static Vec4 cam[MAX_VERTEX_COUNT];
	static Dot screen[MAX_VERTEX_COUNT];

	Vec4 normal;
	Vec4 center = Vec4::ZERO_VEC;

	for ( int i = 0; i < count; i++ )
		center += cam[i] = WorldToCam( vertices[i] );
	center /= count;


	normal = - ( ( cam[ 2 ] - cam[ 0 ] ) ^ ( cam[ 1 ] - cam[ 0 ] ) ).Normalize();

	Color col;
	static Vec4 lightDir;
	static Vec4 reflectedDir;
	static Vec4 eyeDir;
	for( uint i = 0; i < LightDef::Count; ++i ){
		//diffise
		LightDef* def = LightDef::lights[i];
		lightDir = ( lightCoordsCam[i] - center ).Normalize();
		float cosL = normal * lightDir;
		
		//specular
		reflectedDir = lightDir + ( normal * cosL - lightDir ) * 2.0f;
		eyeDir = -center;
		eyeDir.Normalize();

		col +=	material.Ambt * def->Ambient + 
				material.Diff * def->Diffuse * cosL + 
				material.Spec * def->Specular * pow( Max<float>( 0, reflectedDir * eyeDir ), material.Shin );

	}

	for ( int i = 0; i < count; i++ )
		screen[i] = ProjecionToScreen( CamToProjection( cam[i] ) );
	Dot centerDot = ProjecionToScreen( CamToProjection( center ) );

	DrawBitmapPolygon( screen, count, centerDot, col );
}

void CpuRenderer::DrawPolygons( const Vec3* vertices, uint polyCount, uint vertCount, const Material& material ){
	for( uint i = 0; i < polyCount; ++i, vertices += vertCount ){
		DrawPolygon( vertices, vertCount, material );
	}
}

void CpuRenderer::DrawBitmapLine( const Dot& p0, const Dot& p1, const Color& color ){
	int x1, y1, x2, y2;
	x1 = p0.X;
	y1 = p0.Y;
	x2 = p1.X;
	y2 = p1.Y;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int e = dx - dy;
	while ( x1 != x2 || y1 != y2 ){
		if( 0 < x1 && x1 < _width && 0 < y1 && y1 < _height )
			buffer.Set( Dot( x1, y1 ), color );
		int e2 = e * 2;
		if ( e2 > -dy ){
			e -= dy;
			x1 += signX;
		}
		if ( e2 < dx ){
			e += dx;
			y1 += signY;
		}
	}
}

static bool InsideConvex( const Dot* dots, uint count, const Dot& dot ) {
	for( int i = 0; i < count; ++i ){
		if( Det( dot - dots[i], dots[ (i + 1) % count ] - dots[i] ) < 0 ){
			return false;
		}
	}
	return true;
}

void CpuRenderer::DrawBitmapPolygon( const Dot* dots, uint count, const Dot& center, const Color& color ){
	int x0, y0, x1, y1;
	x0 = x1 = center.X;
	y0 = y1 = center.Y;
	for( int i = 0; i < count; ++i ){
		if( dots[i].X < x0 ) x0 = dots[i].X;
		if( dots[i].Y < y0 ) y0 = dots[i].Y;
		if( dots[i].X > x1 ) x1 = dots[i].X;
		if( dots[i].Y > y1 ) y1 = dots[i].Y;
	}

	Dot d21 = dots[ 1 ] - dots[ 0 ];
	Dot d31 = dots[ 2 ] - dots[ 0 ];

	int dx, dy;

	Dot p;
	for( p.Y = y0; p.Y < y1; ++p.Y )
		for( p.X = x0; p.X < x1; ++p.X ){
			if( InsideConvex( dots, count, p ) ){
				dx = p.X - dots[0].X;
				dy = p.Y - dots[0].Y;

				p.Z = (	  dx * d21.Y * d31.Z
						+ d31.X * dy * d21.Z
						- d21.X * dy * d31.Z
						- dx * d31.Y * d21.Z ) /
						float( d31.X * d21.Y - d21.X * d31.Y ) + dots[0].Z;

				buffer.Set( p, color );
			}
		}
}
