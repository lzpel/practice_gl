#version 330 core

uniform mat4 mvp;
//uniform vec3 lp,lc;
//uniform sampler2D tex;

layout(location=0) in vec3 pos;
layout(location=1) in vec3 nor;
layout(location=2) in vec2 txy;

out vec3 mnor;
out vec2 mtxy;

void main() {
    gl_Position=(mvp * vec4(pos,1));
    mnor=mat3(mvp)*nor;
    mtxy=txy;
}