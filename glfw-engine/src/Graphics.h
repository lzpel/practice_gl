/// @file
/// Created by misum on 2020/11/15.
/// 現状二つの目的が混じっているので解消すること
/// GLFWを省き、gl関数と数学関数をインクルードする
///
///

#ifndef GLPRACTICE_GRAPHICS_H
#define GLPRACTICE_GRAPHICS_H

#include <glad/gl.h>

typedef float mat4[16];
typedef float vec3[3];
void identity(mat4&o);
void product(mat4&o,mat4&a,mat4&b);
void translate(mat4&o,vec3&v);
void cross(vec3&o,vec3&a,vec3&b);
void add(vec3&o,vec3&a,vec3&b);
void sub(vec3&o,vec3&a,vec3&b);
void modelview(mat4&TR,vec3&l,vec3&e,vec3&u);
void perspective(mat4&P,float fovy,float aspect,float near,float far);
void transpose(mat4&o);
signed	genProgram(const char*vsrc,const char*fsrc);
signed  genProgramFromFile(const char*vsrc,const char*fsrc);
GLenum  glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#endif //GLPRACTICE_GRAPHICS_H
