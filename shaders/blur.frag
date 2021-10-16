#version 430
precision mediump float;

in vec2 v_blur_texcoord[17];

out vec4 frag_color;

uniform sampler2D u_texture;

const float weight[17] = float[]
(
	0.00101, 0.00331, 0.00925, 0.02204, 0.04486,
	0.07795, 0.11568, 0.14659, 0.15863, 0.14659,
	0.11568, 0.07795, 0.04486, 0.02204, 0.00925,
	0.00331, 0.00101
);

void main()
{
	vec2 result = vec2(0.);

	for (int i = 0; i < 17; i++)
		result += texture2D(u_texture, v_blur_texcoord[i]).rg * weight[i];

	frag_color = vec4(result, 0., 1.);
}
