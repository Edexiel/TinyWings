#version 330

#ifdef GL_ES
precision mediump float;
#endif

#define BUFFER_SIZE 512
uniform vec2 u_resolution;
uniform vec2 u_offset;
uniform float u_precision;
uniform float u_map[BUFFER_SIZE];

// Output fragment color
out vec4 myOutputColor;

void main()
{
    vec3 red = vec3(0.9f, 0.1f, 0.1f);
    float x = gl_FragCoord.x /u_precision; //(gl_FragCoord.x + u_offset.x) /float(u_precision);
    //float x = (gl_FragCoord.x+ u_offset.x) /float(u_precision);
    float height = mix(u_map[int(floor(x))],u_map[int(ceil(x))],fract(x));
    float targety = gl_FragCoord.y + u_offset.y;
    float y = smoothstep(targety-1, targety+1, u_resolution.y - height);
    //vec3 color = red;
    myOutputColor = vec4(red, y);

}