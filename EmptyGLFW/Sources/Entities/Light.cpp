#include "Common.h"
#include "Light.h"

Light::Light( const Transform& pos, const Transform& vel, const Color& ambient, const Color& diffuse, const Color& specular ):
	Entity( pos, vel ),
	Def( pos, vel, ambient, diffuse, specular ),
	added( false )
{}

Light::Light( const Light& light ):
	Entity( light.Pos, light.Vel ),
	Def( light.Def ),
	added( false )
{}

void Light::DrawSelf(){
	_renderer->DrawPoint( Pos.Vec, Def.Diffuse );
}
