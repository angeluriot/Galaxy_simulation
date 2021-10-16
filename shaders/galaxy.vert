#version 430
precision mediump float;

attribute vec4 a_position;
attribute vec4 a_speed;

out float v_brightness;

uniform mat4 u_mvp;

void main()
{
	v_brightness = length(vec3(a_speed));
	gl_Position = u_mvp * vec4(a_position.xyz, 1.);
}
