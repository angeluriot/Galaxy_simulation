#version 430
precision mediump float;

in vec2 v_texcoord;

out vec4 frag_color;

uniform sampler2D u_galaxy;
uniform sampler2D u_blur;

void main()
{
	float stars = texture2D(u_galaxy, v_texcoord).r;
	float glow = texture2D(u_blur, v_texcoord).r * 0.4;

	vec3 stars_color = vec3(max(stars - 2.5 + stars * 0.2, 0.), max(stars - 1. + stars * 0.2, 0.), max(stars + stars * 0.2, 0.));
	vec3 glow_color = vec3(max(glow - 2.5 + glow * 0.2, 0.), max(glow - 1. + glow * 0.2, 0.), max(glow + glow * 0.2, 0.));

	frag_color = vec4(stars_color * 0.7 + glow_color * 0.3, 1.);
}
