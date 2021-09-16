#version 430
precision mediump float;

attribute vec3 a_position;

uniform mat4 u_mvp;
uniform sampler2D u_texture;

void main()
{
	gl_Position = u_mvp * vec4(texture2D(u_texture, a_position.xy).rgb, 1.);
}
