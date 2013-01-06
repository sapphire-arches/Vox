varying vec3 barycentric;
varying vec3 pos;

#define MIN 0.05
#define MAX 0.95

bool inrange(float f) {
    return f < MIN || f > MAX;
}

void main(void) {
//    if (!gl_FrontFacing)
//        discard;
    vec3 v= pos - floor(pos);
    bool x = inrange(v.x);
    bool y = inrange(v.y);
    bool z = inrange(v.z);
    float fac = 0.;

    if (false
            || (x && !y && !z)
            || (!x && y && !z)
            || (!x && !y && z))
        fac = 1.;

    gl_FragColor = mix(gl_Color, vec4(0.1, 0.1, 0.1, 0.), fac);
}
