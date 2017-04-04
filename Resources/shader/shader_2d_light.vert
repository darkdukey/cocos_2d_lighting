
#ifdef GL_ES
attribute mediump vec4 a_position;
attribute mediump vec2 a_texcoord;
attribute mediump vec4 a_color;

varying mediump vec4 v_color;
varying mediump vec2 v_texcoord;
varying mediump vec4 v_light;

#else

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec4 a_color;

varying vec4 v_color;
varying vec2 v_texcoord;
varying vec4 v_light;

#endif

uniform vec4 u_light_pos;
uniform vec2 window;

void main()
{
    v_color = a_color;
    
    v_texcoord = a_texcoord;

    // Convert from world space to gl_FragCoord space
    // Vertex in clip-space
    v_light = CC_MVPMatrix * u_light_pos;
    
    // Vertex in NDC-space
    v_light.xyz /= v_light.w;       // Rescale: [-1,1]^3
    v_light.w    = 1.0 / v_light.w; // Invert W
    
    // Vertex in window-space
    v_light.xyz *= vec3(0.5);       // Rescale: [0,1]^3
    v_light.xyz += vec3(0.5);
    v_light.xy  *= window;

    gl_Position = CC_MVPMatrix * a_position;
}
