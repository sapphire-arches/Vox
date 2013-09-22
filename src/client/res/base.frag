varying vec3 barycentric;
varying vec3 pos;

#define SIZE 0.9
#
#define FOG_START 10.
#define FOG_END 75.
#

void main(void) {
    if (!gl_FrontFacing)
        discard;
    vec3 v = abs(pos - floor(pos) - vec3(0.5, 0.5, 0.5));

    //GL_LINEAR
    float fog = clamp((FOG_END - gl_FogFragCoord) / (FOG_END - FOG_START), 0., 1.);
    gl_FragColor = mix(vec4(0., 0., 0., 0.), gl_Color, fog);
}
