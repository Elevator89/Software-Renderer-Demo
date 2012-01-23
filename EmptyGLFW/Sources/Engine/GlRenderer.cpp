#include "Common.h"
#include "GlRenderer.h"

using namespace std;

GlRenderer::GlRenderer( int width, int height, const Color& bgColor ):
	Renderer( width, height, bgColor ) 
{}

GlRenderer::~GlRenderer(){}

void GlRenderer::InitSelf(){
	glClearColor( _bgColor.R, _bgColor.G, _bgColor.B, _bgColor.A );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	//glEnable(GL_FOG);					// Включает туман (GL_FOG)
	//glFogi(GL_FOG_MODE, GL_LINEAR );	// Выбираем тип тумана
	//float fogColor[4] = { _bgColor.R, _bgColor.G, _bgColor.B, _bgColor.A };
	//glFogfv(GL_FOG_COLOR, fogColor );	// Устанавливаем цвет тумана
	//glFogf(GL_FOG_DENSITY, 0.25f );		// Насколько густым будет туман
	//glHint(GL_FOG_HINT, GL_NICEST );	// Вспомогательная установка тумана
	//glFogf(GL_FOG_START, 1.0f);			// Глубина, с которой начинается туман
	//glFogf(GL_FOG_END, 30.0f);			// Глубина, где туман заканчивается.

	glShadeModel (GL_SMOOTH);
	glEnable ( GL_DEPTH_TEST );
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE );
	glEnable ( GL_CULL_FACE );	
	glEnable( GL_ALPHA_TEST );
	glEnable (GL_LIGHTING);

	printf( "%s\n", glGetString( GL_RENDERER ) );
}

void GlRenderer::DisposeSelf(){}

void GlRenderer::BeginDraw(){}

void GlRenderer::EndDraw(){
	glfwSwapBuffers();
}

void GlRenderer::Refresh( const Transform& tf ){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity();
	float aspect = float( _width ) / float( _height );
	glFrustum( -aspect, aspect, -1.0f, 1.0f, 2.0f, 500.0f );

	glMatrixMode ( GL_MODELVIEW );
	glLoadMatrixf( tf.GetCamMatrix().Array() );


	for( uint i = 0; i < LightDef::Count; ++i ){
		LightDef* def = LightDef::lights[i];


		glLightfv( GL_LIGHT0 + def->Index, GL_AMBIENT, def->Ambient.Array() );	
		glLightfv( GL_LIGHT0 + def->Index, GL_DIFFUSE, def->Diffuse.Array() );
		glLightfv( GL_LIGHT0 + def->Index, GL_SPECULAR, def->Specular.Array() );
		glEnable( GL_LIGHT0 + def->Index );



		Vec4 lPos = Vec4( def->Pos.Vec, 1.0f );
		glLightfv (GL_LIGHT0 + i, GL_POSITION, lPos.Array() );
	}
}

void GlRenderer::Push(){ glPushMatrix(); }
void GlRenderer::Pop(){ glPopMatrix(); }
void GlRenderer::Load( const Matr4& model ){ glLoadMatrixf( model.Array() ); }
void GlRenderer::Mult( const Matr4& model ){ glMultMatrixf( model.Array() ); }

void GlRenderer::DrawPoint( const Vec3& point, const Color& color, float size ){
	glColor4f( color.R, color.G, color.B, color.A );
	float s = 0.5f * size;
	glBegin( GL_LINES );
	glVertex3f( point.X - s, point.Y, point.Z );
	glVertex3f( point.X + s, point.Y, point.Z );
	glVertex3f( point.X, point.Y - s, point.Z );
	glVertex3f( point.X, point.Y + s, point.Z );
	glVertex3f( point.X, point.Y, point.Z - s );
	glVertex3f( point.X, point.Y, point.Z + s );
	glEnd();
}

void GlRenderer::DrawLine( const Vec3& start, const Vec3& end, const Color& color ){
	glColor4fv( color.Array() );

	glBegin( GL_LINES );
	glVertex3f( start.X, start.Y, start.Z );
	glVertex3f( end.X, end.Y, end.Z );
	glEnd();
	glPointSize( 1.0f );
}

void GlRenderer::DrawPolygon( const Vec3* vertices, uint count, const Color& color ){
	glColor4fv( color.Array() );

	glBegin( GL_TRIANGLE_FAN );
	for ( uint i = 0; i < count; ++i )
		glVertex3f( vertices[i].X, vertices[i].Y, vertices[i].Z );
	glEnd();
}

void GlRenderer::DrawPolygon( const Vec3* vertices, uint count, const Material& material ){
	glMaterialfv(GL_FRONT, GL_AMBIENT, material.Ambt.Array() );
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material.Diff.Array() );
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.Spec.Array() );
    glMaterialfv(GL_FRONT, GL_SHININESS, &material.Shin );


	glColor4fv( material.Diff.Array() );
	glEnable( GL_LIGHTING );

	Vec3 n;
	Vec3 vert;
	Vec3 a,b;

	a = ( vertices[ 2 ] - vertices[ 0 ] );
	b = ( vertices[ 1 ] - vertices[ 0 ] );
	n = ( a ^ b ).Normalize();

	glBegin( GL_TRIANGLE_FAN );
	glNormal3f ( n.X, n.Y, n.Z );
	for ( uint i = 0; i < count; ++i ){
		glVertex3fv( vertices[i].Array() );
	}
	glEnd();
	glDisable( GL_LIGHTING );
}

void GlRenderer::DrawPolygons( const Vec3* vertices, uint polyCount, uint vertCount, const Material& material ){
	glMaterialfv(GL_FRONT, GL_AMBIENT, material.Ambt.Array() );
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material.Diff.Array() );
    glMaterialfv(GL_FRONT, GL_SPECULAR, material.Spec.Array() );
    glMaterialfv(GL_FRONT, GL_SHININESS, &material.Shin );

	glColor4fv( material.Diff.Array() );
	glEnable( GL_LIGHTING );

	Vec3 n;
	Vec3 a,b;
	for( uint i = 0; i < polyCount; ++i ){
		a = ( vertices[ i * vertCount + 2 ] - vertices[ i * vertCount ] );
		b = ( vertices[ i * vertCount + 1 ] - vertices[ i * vertCount ] );
		n = ( a ^ b ).Normalize();
		glBegin( GL_TRIANGLE_FAN );
		glNormal3fv ( n.Array() );
		for ( uint j = 0; j < vertCount; ++j ){
			glVertex3fv( vertices[ i * vertCount + j ].Array() );
		}
		glEnd();
	}

	glDisable( GL_LIGHTING );
}


