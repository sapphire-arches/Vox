varying vec3 barycentric;
varying vec3 pos;

#define SIZE 0.9
#
#define FOG_START 10.
#define FOG_END 75.
#

void main(void) {
    vec4 c = vec4(0.1, 0.1, 0.1, 0.);
    if (!gl_FrontFacing)
        discard;
    vec3 v = abs(pos - floor(pos) - vec3(0.5, 0.5, 0.5));
    float fac = smoothstep(0., SIZE, v.x) + smoothstep(0., SIZE, v.y) + smoothstep(0., SIZE, v.z);
    fac /= 3.;
    fac = smoothstep(0.0, 1.0, fac);
    fac = 1. - fac;

    vec4 col = mix(gl_Color, c, fac);
    //GL_LINEAR
    float fog = clamp((FOG_END - gl_FogFragCoord) / (FOG_END - FOG_START), 0., 1.);
    gl_FragColor = col;
    gl_FragColor = mix(vec4(0., 0., 0., 0.), col, fog);
}
