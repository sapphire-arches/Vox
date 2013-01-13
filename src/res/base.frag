varying vec3 barycentric;
varying vec3 pos;

#define MIN 0.07
#define MAX (1. - MIN)
#
#define FOG_START 10.
#define FOG_END 100.

bool inrange(float f) {
    return f < MIN || f > MAX;
}

void main(void) {
    vec4 c = vec4(0.1, 0.1, 0.1, 0.);
    if (!gl_FrontFacing)
        discard;
    vec3 v= pos - floor(pos);
    bool x = inrange(v.x);
    bool y = inrange(v.y);
    bool z = inrange(v.z);
    float fac = 0.;

    if (
               (x && !y && !z)
            || (!x && y && !z)
            || (!x && !y && z))
        fac = 1.;
    vec4 col = mix(gl_Color, c, fac);
    //GL_LINEAR
    float fog = clamp((FOG_END - gl_FogFragCoord) / (FOG_END - FOG_START), 0., 1.);
    gl_FragColor = col;
    gl_FragColor = mix(vec4(0., 0., 0., 0.), col, fog);
}
