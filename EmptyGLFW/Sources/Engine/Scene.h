#ifndef SCENE_H
#define SCENE_H

#include "Common.h"
#include "Math/Math.h"
#include "Interfaces/Interfaces.h"

#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Renderer.h"
#include "GlRenderer.h"
#include "CpuRenderer.h"

#include "Entities/Entities.h"

class Scene: public Initializable, public Tickable {
protected:
	static Scene* _self;
	Scene(){}
	~Scene(){}
public:

	static Scene* Self() { return _self; }
	static void Create( Camera* camera, Renderer* renderer );
	
	static void GLFWCALL Resize( int width, int height );

	virtual void InitSelf();
	virtual void DisposeSelf();

	virtual bool Tick( float dt = DEFAULT_DT );
	virtual void Draw();


protected:
	static std::vector<Entity*> _entities;
	static Camera* _camera;
	static Renderer* _renderer;

};

#endif
