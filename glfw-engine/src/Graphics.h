/// @file
/// Created by misum on 2020/11/15.
/// 現状二つの目的が混じっているので解消すること
/// GLFWを省き、gl関数と数学関数をインクルードする
///
///

#ifndef GLPRACTICE_GRAPHICS_H
#define GLPRACTICE_GRAPHICS_H

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>
signed	genProgram(const char*vsrc,const char*fsrc);
signed  genProgramFromFile(const char*vsrc,const char*fsrc);
GLenum  glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#endif //GLPRACTICE_GRAPHICS_H
