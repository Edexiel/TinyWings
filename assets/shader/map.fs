#version 330

// #ifdef GL_ES
// precision mediump float;
// #endif

// in vec2 VertexTexCoord;
// in vec4 VertexColor;

uniform int u_stepping;
uniform float u_map[1000];

// Output fragment color
//out vec4 gl_FragColor;

// NOTE: Add here your custom variables

void main()
{
//    if(gl_FragCoord.y <= u_map[int(gl_FragCoord.x)])
//    {
//        gl_FragColor = vec4(0.9, 0.1, 0.1, 1);
//    }
    float y = smoothstep(gl_FragCoord.y,gl_FragCoord.y+5,u_map[int(gl_FragCoord.x)]);
    vec4 color = vec4(y) * vec4(0.9f, 0.1f, 0.1f,1.f);
    gl_FragColor = color;

}
//
//    //#version 330
//    #ifdef GL_ES
//precision mediump float;
//#endif
//
//uniform int u_stepping;
//uniform float u_map[1000];
//
//void main()
//{
//
//}