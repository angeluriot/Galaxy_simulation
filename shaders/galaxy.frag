#version 430
precision mediump float;

in float v_brightness;

out vec4 frag_color;

void main()
{
	frag_color = vec4(v_brightness / 5., 0., 0., 1.);
}
