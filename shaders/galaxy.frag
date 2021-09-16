#version 430
precision mediump float;

in vec3 v_position;
in float v_brightness;

out vec4 frag_color;

void main()
{
	if (v_brightness == 0.)
		discard;

	frag_color = vec4(v_brightness, 0., 0., 1.);
}
