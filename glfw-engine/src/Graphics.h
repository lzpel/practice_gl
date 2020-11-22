/// @file
/// Created by misum on 2020/11/15.
/// 現状二つの目的が混じっているので解消すること
/// GLFWを省き、gl関数と数学関数をインクルードする
///
///

#ifndef GLPRACTICE_GRAPHICS_H
#define GLPRACTICE_GRAPHICS_H

#include <glad/gl.h>

typedef float mat4[16],vec3[3],vec4[4];
void identity(mat4&o);
void copy(mat4&o,const double*a);
void copy(mat4&o,const float*y);
void product(mat4&o,const mat4&a,const mat4&b);
void productscale(mat4&o,const vec3&a,const mat4&b);
void productrotation(mat4&o,const vec4&a,const mat4&b);
void producttranslation(mat4&o,const vec3&a,const mat4&b);
void cross(vec3&o,const vec3&a,const vec3&b);
void add(vec3&o,const vec3&a,const vec3&b);
void sub(vec3&o,const vec3&a,const vec3&b);
void modelview(mat4&TR,vec3&l,vec3&e,vec3&u);
void perspective(mat4&P,float fovy,float aspect,float near,float far);
void transpose(mat4&o);
signed	genProgram(const char*vsrc,const char*fsrc);
signed  genProgramFromFile(const char*vsrc,const char*fsrc);
GLenum  glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#endif //GLPRACTICE_GRAPHICS_H
