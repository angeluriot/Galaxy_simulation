#version 430
precision mediump float;

in vec2 v_texcoord;

out vec4 frag_color;

uniform int u_color_type;
uniform sampler2D u_galaxy;
uniform sampler2D u_blur;

void main()
{
	float stars = texture2D(u_galaxy, v_texcoord).r;
	float glow = texture2D(u_blur, v_texcoord).r * 0.2;
	vec3 color_1;
	vec3 color_2;

	if (u_color_type == 0)
	{
		color_1 = vec3(0.05, 0.05, 0.3);
		color_2 = vec3(0.05, 0.3, 0.3);
		frag_color = vec4(0.7 * mix(color_1, color_2 , 0.05 * (stars + glow)) * (stars + glow), 1.);
	}

	else if (u_color_type == 1)
	{
		color_1 = vec3(0.3, 0.05, 0.05);
		color_2 = vec3(0.3, 0.3, 0.05);
		frag_color = vec4(0.7 * mix(color_1, color_2 , 0.1 * (stars + glow)) * (stars + glow), 1.);
	}

	else
	{
		color_1 = vec3(0.05, 0.05, 0.3);
		color_2 = vec3(0.3, 0.05, 0.3);
		frag_color = vec4(0.7 * mix(color_1, color_2 , 0.1 * (stars + glow)) * (stars + glow), 1.);
	}
}
