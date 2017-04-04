
#ifdef GL_ES
// #extension GL_OES_standard_derivatives : enable

varying mediump vec4 v_color;
varying mediump vec2 v_texcoord;
varying mediump vec4 v_light;
#else
varying vec4 v_color;
varying vec2 v_texcoord;
varying vec4 v_light;
#endif

const float light_range = 100.0;

const float WHITE_RANGE = 4.0;
const float WHITE_FADE_RANGE = 8.0;

const float lightIntensity = 500.0;            // Distance between 'light position' and 'light end'

void main()
{
    // Get distance between rendering pixel and light position
    float dist = abs(distance(v_light.xy, gl_FragCoord.xy));
        
    if(0.0 <= dist && dist <= WHITE_RANGE)
    {
        // range 1. color is always white
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(WHITE_RANGE <= dist && dist <= WHITE_FADE_RANGE)
    {
        // range 2. Mix white and light color
        float ratio = ((dist - WHITE_RANGE) / (WHITE_FADE_RANGE - WHITE_RANGE));
        gl_FragColor = mix(vec4(1.0, 1.0, 1.0, 1.0), v_color, ratio);
    }
    else if(WHITE_FADE_RANGE <= dist && dist <= lightIntensity)
    {
        float ratio = ((dist - WHITE_FADE_RANGE) / (lightIntensity - WHITE_FADE_RANGE));
        gl_FragColor = mix(v_color, vec4(0.0, 0.0, 0.0, 0.0), ratio);
    }
    else
    {
        // light doesn't reach here
        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
}
