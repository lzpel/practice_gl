#version 330 core
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_shading_language_420pack: enable

//layout(location=0) uniform mat4 mvp;
layout(location=1) uniform vec3 lp;
layout(location=2) uniform vec3 lc;
layout(binding=0) uniform sampler2D tex;

layout(location=0) in vec3 pos;
layout(location=1) in vec3 nor;
layout(location=2) in vec2 txy;

in vec3 mnor;
in vec2 mtxy;

out vec4 color;

void main() {
    color = vec4(texture(tex, mtxy).xyz * (0.3 + 0.7 * max(dot(mnor, normalize(lp)), 0.0)) * lc,1.0);
    //color = vec4(1,0,0,1);
}