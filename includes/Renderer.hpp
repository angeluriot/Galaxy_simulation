#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "libraries.hpp"

class Renderer
{
public:
	static dim::Shader			galaxy_shader;
	static dim::VertexBuffer	galaxy_vbo;
	static dim::Shader			test_shader;
	static dim::VertexBuffer	test_vbo;

	static void init();
	static void draw();
};

#endif
