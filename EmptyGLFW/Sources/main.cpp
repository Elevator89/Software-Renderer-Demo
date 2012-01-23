#include "Common.h"
#include "Engine/Camera.h"
#include "Engine/Renderer.h"
#include "Engine/GlRenderer.h"
#include "Engine/CpuRenderer.h"
#include "Engine/Scene.h"

static void ShowFPS( float dt ){
	printf( "FPS = %4.2f\r", 1.0f / dt );
}

static float GetDT(){
	static float t0 = 0.0f;
	static float t1 = 0.0f;
	t0 = t1;
	t1 = glfwGetTime();
	return t1 - t0;
}

int main( int argc, char* argv[] )
{

	if( !glfwInit() )	exit( EXIT_FAILURE );
//	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );

	if( !glfwOpenWindow( 800, 600,8,8,8,8,8,8,GLFW_WINDOW ) ){
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glfwSetWindowPos( 0,0 );
	glfwSwapInterval( 0 );

	if( argc > 1 ){
		if( strcmp( argv[1], "/GL" ) == 0 )
			Scene::Create( new Camera(), new GlRenderer( 800, 600, Color::WHITE ) );
		if( strcmp( argv[1], "/CPU" ) == 0 )
			Scene::Create( new Camera(), new CpuRenderer( 800, 600, Color::WHITE ) );
	} else
		Scene::Create( new Camera(), new CpuRenderer( 800, 600, Color::WHITE ) );
	Scene::Self()->Init();
	int running = GL_TRUE;

	float dt;
	while( Scene::Self()->Tick( dt = GetDT() ) ){
		Scene::Self()->Draw();
		ShowFPS( dt );
	}
	Scene::Self()->Dispose();

	glfwTerminate();
	exit( EXIT_SUCCESS );
	return 0;
}
