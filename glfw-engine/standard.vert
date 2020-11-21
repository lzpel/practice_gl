#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout(location=0) uniform mat4 mvp;
// layout(location=1) uniform vec3 lp;
// layout(location=2) uniform vec3 lc;
// layout(binding=0) uniform sampler2D tex;

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