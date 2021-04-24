#version 330

#ifdef GL_ES
precision mediump float;
#endif

in vec2 VertexTexCoord;
in vec4 VertexColor;

uniform int u_stepping;
uniform float u_map[1000];

// Output fragment color
//out vec4 gl_FragColor;

// NOTE: Add here your custom variables

void main()
{
//     u_map;
//     u_size;
//     // Texel color fetching from texture sampler
//     vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
//
//     // Convert texel color to grayscale using NTSC conversion weights
//     float gray = dot(texelColor.rgb, vec3(0.299, 0.587, 0.114));
//
//     // Calculate final fragment color
//            gl_FragColor = vec4(0.9, 0.1, 0.1, 1);

int x = 0;
for(int i = 0;i<1000;++i)
{
    vec3 color = vec3(0.0);
    float up = step(x,gl_FragCoord.x);
    float down = step(u_map[i],gl_FragCoord.y);

    color=vec3(up*down);
    gl_FragColor = vec4(color,1.0);
//       gl_FragColor = vec4(0.9, 0.1, 0.1, 1);


    x+=u_stepping;
}
}