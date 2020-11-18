#version 330 core

//uniform mat4 mvp;
uniform vec3 lp,lc;
uniform sampler2D tex;

//in vec3 pos;
//in vec3 nor;
//in vec2 txy;

in vec3 mnor;
in vec2 mtxy;

out vec4 color;

void main() {
    color = vec4(texture(tex, mtxy).xyz * (0.3 + 0.7 * max(dot(mnor, normalize(lp)), 0.0)) * lc,1.0);
    //color = vec4(1,0,0,1);
}