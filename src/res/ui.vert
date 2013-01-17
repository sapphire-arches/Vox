uniform mat4 MView;
uniform mat4 MProj;

varying vec3 norm;
varying vec3 barycentric;
varying vec3 pos;

void main(void) {
    gl_Position = MProj * MView * gl_Vertex;
    norm = gl_Normal;
    barycentric = gl_Vertex.xyz - floor(gl_Vertex.xyz);
    pos = gl_Vertex.xyz;
    gl_FrontColor = gl_Color;
    gl_FogFragCoord = gl_Position.z;
}
