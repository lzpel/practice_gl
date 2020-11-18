//
// Created by misum on 2020/11/15.
//

#include "Graphics.h"
#include <stdio.h>
#include <fstream>

signed genProgram(const char*vsrc,const char*fsrc){
	printf("GL_VERSION=%s\nGL_SHADING_LANGUAGE_VERSION=%s\n",glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	char message[1024];
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	printf("Compile Vertex Shader\n");
	glShaderSource(VertexShaderID, 1, &vsrc, NULL);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		glGetShaderInfoLog(VertexShaderID, sizeof(message), NULL, message);
		glDeleteShader(VertexShaderID);
		printf("%s\n", message);
		return -1;
	}

	printf("Compile Fragment Shader\n");
	glShaderSource(FragmentShaderID, 1, &fsrc, NULL);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, message);
		glDeleteShader(FragmentShaderID);
		printf("%s\n", message);
		return -1;
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, message);
		glDeleteProgram(ProgramID);
		printf("%s\n", message);
		return -1;
	}
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glCheckError();
	return  ProgramID;
}
std::string readAll(std::string filePath){
	std::ifstream ifs(filePath);
	return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}

signed genProgramFromFile(const char*vsrc,const char*fsrc){
	return genProgram(readAll(vsrc).c_str(),readAll(fsrc).c_str());
}
GLenum glCheckError_(const char *file, int line){
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR){
		const char* error;
		switch (errorCode){
			case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		printf_s("%s|%s(%d)\n",error,file,line);
	}
	return errorCode;
}