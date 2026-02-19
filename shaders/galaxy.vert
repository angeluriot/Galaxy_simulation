#version 430
precision mediump float;

in vec4 a_position;
in vec4 a_speed;
in int a_starType; // Add this line to receive star type

out float v_brightness;
flat out int v_starType; // Add this line to pass star type to fragment shader

uniform mat4 u_mvp;

void main()
{
    v_brightness = length(vec3(a_speed));
    v_starType = a_starType; // Pass star type to fragment shader
    gl_Position = u_mvp * vec4(a_position.xyz, 1.);
}