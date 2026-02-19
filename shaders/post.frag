#version 430
precision mediump float;

in vec2 v_texcoord;

out vec4 frag_color;

uniform sampler2D u_galaxy;
uniform sampler2D u_blur;

void main()
{
    vec4 galaxy_data = texture(u_galaxy, v_texcoord);
    vec3 stars = galaxy_data.rgb;
    vec3 blur = texture(u_blur, v_texcoord).rgb;
    // Boost blue-channel bloom so positive stars get a glow comparable to negatives.
    vec3 glow = vec3(0.20 * blur.r, 0.20 * blur.g, 0.22 * blur.b);
    frag_color = vec4(0.7 * (stars + glow), 1.0);
}
