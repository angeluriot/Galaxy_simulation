#version 430
precision mediump float;

attribute vec3 a_position;
attribute vec2 a_texcoord;

out vec2 v_texcoord;

void main()
{
	v_texcoord = a_texcoord;
	gl_Position = vec4(a_position, 1.);
}
