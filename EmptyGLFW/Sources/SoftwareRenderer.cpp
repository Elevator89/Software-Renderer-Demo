#include "Common.h"
#include "SoftwareRenderer.h"

using namespace std;

float aspect;
float dx, dy;
float xs, ys;


SoftwareRenderer::SoftwareRenderer( int width, int height, const Color& bgColor ):
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

SoftwareRenderer::~SoftwareRenderer(){}

void SoftwareRenderer::Frustum( float left, float right, float top, float bottom, float near, float far ){
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


void SoftwareRenderer::InitSelf(){
	glfwSetMousePos( _width/2, _height/2 );
}

void SoftwareRenderer::DisposeSelf(){}

void SoftwareRenderer::Resize( int width, int height ){
	buffer.Resize( width, height );

	aspect = float(_width) / float(_height);
	xs = -aspect;
	ys = 1.0f;

	dx = 2.0f * aspect / float(_width);
	dy = -2.0f / float(_height);

	Renderer::Resize( width, height );

	glLoadIdentity();
	gluOrtho2D( -aspect, aspect, -1.0f, 1.0f );
}


void SoftwareRenderer::BeginDraw(){
	buffer.Clear();

}

void SoftwareRenderer::EndDraw(){
	float xf, yf;
	yf = ys;

	glBegin( GL_POINTS );
	for( float y = 0; y <= _height; ++y ){
		xf = xs;
		for( uint x = 0; x <= _width; ++x ){
			Color col = buffer.Get( Dot(x,y) );
			glColor4f( col.R, col.G, col.B, col.A );
			glVertex2f ( xf, yf );
			xf += dx;
		}
		yf += dy;
	}
	glEnd();

	glfwSwapBuffers();
}

void SoftwareRenderer::Refresh( const Transform& tf ){
	float aspect = float( _width ) / float( _height );
	Frustum( -aspect, aspect, -1.0f, 1.0f, 2.0f, 500.0f );
	_model = tf.GetMatrix();
	_composite = _projection * _model;
}

void SoftwareRenderer::Push(){
	_matrStack.push( _model );
}
void SoftwareRenderer::Pop(){
	_model = _matrStack.top();
	_matrStack.pop();
}

void SoftwareRenderer::Load( const Matr4& model ){
	_model = model;
}

void SoftwareRenderer::Mult( const Matr4& model ){
	_model = _model * model;
	_composite = _projection * _model;
}

void SoftwareRenderer::AddLight( const LightDef& light ){
	lights[ light.Index ] = &light;
}

void SoftwareRenderer::LitUp( const LightDef& light ){
}
void SoftwareRenderer::LitDown( const LightDef& light ){
}

void SoftwareRenderer::DrawPoint( const Vec3& point, const Color& color, float size ){
	Dot dot = CamToScreen( WorldToCam( point ) );
	buffer.Set( dot, color );
}

void SoftwareRenderer::DrawLine( const Vec3& start, const Vec3& end, const Color& color ){
	Dot dot0 = CamToScreen( WorldToCam( start ) );
	Dot dot1 = CamToScreen( WorldToCam( end ) );
	DrawBitmapLine( dot0, dot1, color );
}




void SoftwareRenderer::DrawPolygon( const Vec3* vertices, uint count, const Color& color ){
	Dot* dots = new Dot[count];
	Dot center;
	for ( int i = 0; i < count; i++ ){
		dots[i] = CamToScreen( WorldToCam( vertices[i] ) );
		center += dots[i];
	}
	center /= count;
	DrawBitmapPolygon( dots, count, center, Vec3( 0.0f, 0.0f, 1.0f ), color );
	delete dots;
}

void SoftwareRenderer::DrawPolygon( const Vec3* vertices, uint count, const Color& color, const Material& material ){
	Vec3 normal;
	Vec3 center;

	normal = ( ( vertices[ 2 ] - vertices[ 0 ] ) ^ ( vertices[ 1 ] - vertices[ 0 ] ) ).Normalize();

	for ( int i = 0; i < count; i++ ) center += vertices[i];
	center /= count;

	Color col;

	Vec3 lightDir;
	for( uint i = 0; i < LightDef::Count; ++i ){
		const LightDef* def = lights[i];
		lightDir = def->Pos.Vec - center;
		lightDir.Normalize();
		float cosL = normal * lightDir;

		col += material.Ambt * def->Ambient + material.Diff * def->Diffuse * cosL;

	}


	Dot* dots = new Dot[count];
	Dot centerDot;
	for ( int i = 0; i < count; i++ ){
		dots[i] = CamToScreen( WorldToCam( vertices[i] ) );
		centerDot += dots[i];
	}
	centerDot /= count;
	DrawBitmapPolygon( dots, count, centerDot, normal, color );
	delete dots;
}

void SoftwareRenderer::DrawPolygons( const Vec3* vertices, uint polyCount, uint vertCount, const Color& color, const Material& material ){
	for( uint i = 0; i < polyCount; ++i, vertices += vertCount ){
		DrawPolygon( vertices, vertCount, color, material );
	}
}

void SoftwareRenderer::DrawBitmapLine( const Dot& p0, const Dot& p1, const Color& color ){
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
		if( Det( dot - dots[i], dots[ (i + 1) % count ] - dots[i] ) > 1 )
			return false;
	}
	return true;
}

void SoftwareRenderer::DrawBitmapPolygon( const Dot* dots, uint count, const Dot& center, const Vec3& normal, const Color& color ){
	int x0, y0, x1, y1;
	x0 = x1 = center.X;
	y0 = y1 = center.Y;
	for( int i = 0; i < count; ++i ){
		if( dots[i].X < x0 ) x0 = dots[i].X;
		if( dots[i].Y < y0 ) y0 = dots[i].Y;
		if( dots[i].X > x1 ) x1 = dots[i].X;
		if( dots[i].Y > y1 ) y1 = dots[i].Y;
	}

	Dot p;
	for( p.Y = y0; p.Y < y1; ++p.Y )
		for( p.X = x0; p.X < x1; ++p.X ){
			if( InsideConvex( dots, count, p ) ){
				p.Z = -( normal.X * ( p.X - center.X ) + normal.Y * ( p.Y - center.Y ) ) / normal.Z - center.Z;
				buffer.Set( p, color );
			}
		}
}
