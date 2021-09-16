#version 430
precision mediump float;

attribute vec3 a_position;
attribute vec2 a_texcoord;

out vec2 v_blur_texcoord[17];

uniform sampler2D u_texture;
uniform int u_horizontal;

void main()
{
	vec2 tex_offset = 1. / textureSize(u_texture, 0);

	for (int i = -8; i <= 8; i++)
		v_blur_texcoord[i + 8] = a_texcoord + vec2(u_horizontal * tex_offset.x * i, (1. - u_horizontal) * tex_offset.y * i);

	gl_Position = vec4(a_position, 1.);
}
