#include "Common.h"
#include "Renderer.h"

Renderer::Renderer( int width, int height, const Color& bgColor ):
	_bgColor( bgColor ),
	_width( width ),
	_height( height )
{}

Renderer::~Renderer(void){}

void Renderer::Resize( int width, int height ){
	_width = width;
	_height = height;
	glfwSetWindowSize( width, height );
	glViewport( 0, 0, width, height );
}
