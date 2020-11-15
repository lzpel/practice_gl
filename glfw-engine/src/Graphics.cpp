//
// Created by misum on 2020/11/15.
//

#include "Graphics.h"
#include <stdio.h>

signed genProgram(const char*vsrc,const char*fsrc){
	char message[256];
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	glShaderSource(VertexShaderID, 1, &vsrc, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, message);
		printf("%s\n", message);
	}

	// Compile Fragment Shader
	glShaderSource(FragmentShaderID, 1, &fsrc, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, message);
		printf("%s\n", message);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, message);
		printf("%s\n", message);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	//glUseProgram(ProgramID);
	return  ProgramID;
	//shadermvpid = glGetUniformLocation(shaderid, "MVP");
}