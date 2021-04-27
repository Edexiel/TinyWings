#version 330

// #ifdef GL_ES
// precision mediump float;
// #endif

uniform int u_stepping;
uniform float u_map[1000];

// Output fragment color
out vec4 myOutputColor;

void main()
{
    vec3 red = vec3(0.9f, 0.1f, 0.1f);
    vec3 blue = vec3(0.1f, 0.1f, 1.f);

    float y = smoothstep(gl_FragCoord.y,gl_FragCoord.y+2,u_map[int(gl_FragCoord.x)]);
    vec3 color = red;
    myOutputColor = vec4(color,y);

}