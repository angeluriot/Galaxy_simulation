#version 430
precision mediump float;

in vec2 v_texcoord;

out vec4 frag_color;

uniform sampler2D u_texture;

void main()
{
	frag_color = texture2D(u_texture, v_texcoord);
}
