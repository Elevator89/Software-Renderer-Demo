#include "Common.h"
#include "Scene.h"

Camera* Scene::_camera;
Renderer* Scene::_renderer;
Scene* Scene::_self;

std::vector<Entity*> Scene::_entities;


void Scene::Create( Camera* camera, Renderer* renderer  ){
	_self = new Scene(); 
	_camera = camera;
	_renderer = renderer;

}

void Scene::InitSelf(){
	_renderer->Init();

	glfwSetKeyCallback			( Keyboard::CatchKeyboard );
	glfwSetWindowSizeCallback	( Scene::Resize );
	glfwSetMouseButtonCallback	( Mouse::CatchMouseButtons );
	glfwSetMousePosCallback		( Mouse::CatchMousePos );
	glfwSetMouseWheelCallback	( Mouse::CatchMouseWheel );

	Keyboard::AddListener( _camera );
	Mouse::AddListener( _camera );


	Polygon poly;
	poly.AddVertex( Vec3( 0.0f, -3.0f, -5.0f ) );
	poly.AddVertex( Vec3( 10.0f, -3.0f, -5.0f ) );
	poly.AddVertex( Vec3( 10.0f, -3.0f, -15.0f ) );
	poly.AddVertex( Vec3( 0.0f, -3.0f, -15.0f ) );

	Shape* polyShape = new Shape( Transform(), Transform(), Color::BLUE, Material( Color::BLACK, Color::WHITE, Color::WHITE, 30.0f ) );
	polyShape->AddPolygon( poly );
	_entities.push_back( polyShape );


	_entities.push_back( new Light( Transform(), Transform(), Color::BLUE , Color::WHITE, Color::WHITE ) );
	_entities.push_back( new Light( Transform( Vec3( 40.0f, 3.0f, -10.0f ), Rotation() ), Transform(), Color::BLACK , Color::RED, Color::GREEN ) );
	_entities.push_back( new Thorus( Transform( Vec3( 5.0f, -3.0f, -10.0f ), Rotation( PI * 0.1f, PI * 0.25f, 0.0f ) ), Transform(), 3.0f, 1.0f, 100, Color::BLUE, Material( Color::BLACK, Color::GREY, Color::GREEN, 30.0f ) ) );
//	_entities.push_back( new Thorus( Transform( Vec3( 3.0f, -1.0f, 5.0f ), Rotation( PI * 0.1f, PI * 0.25f, 0.0f ) ), Transform(), 3.0f, 1.0f, 10, Color::GREY, Material( Color::BLACK, Color::GREY, Color::WHITE, 30.0f ) ) );
}


void Scene::DisposeSelf(){

}

bool Scene::Tick( float dt ){
	_camera->Tick( dt );

	for( uint i = 0; i < _entities.size(); ++i )
		_entities[i]->Tick( dt );
	
	return !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
}

void Scene::Draw(){
	_renderer->Refresh( _camera->Pos );
	_renderer->BeginDraw();

	for( uint i = 0; i < _entities.size(); ++i )
		_entities[i]->Draw( _renderer );

	_renderer->EndDraw();

}

void GLFWCALL Scene::Resize( int width, int height ){
	_renderer->Resize( width, height );
}
