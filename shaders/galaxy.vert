#version 430
precision mediump float;

attribute vec3 a_position;
attribute vec3 a_texcoord;

out vec3 v_position;
out float v_brightness;

uniform mat4 u_mvp;

void main()
{
	v_position = a_position;
	v_brightness = a_texcoord.x;
	gl_Position = u_mvp * vec4(a_position, 1.);
}
