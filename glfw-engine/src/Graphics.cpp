//
// Created by misum on 2020/11/15.
//

#include "Graphics.h"
#include <stdio.h>
#include <string>
#include <math.h>

void identity(mat4 &o) {
	o[1] = o[2] = o[3] = o[4] = o[6] = o[7] = o[8] = o[9] = o[11] = o[12] = o[13] = o[14] = 0;
	o[0] = o[5] = o[10] = o[15] = 1;
}

void product(mat4 &o, mat4 &a, mat4 &b) {
	o[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
	o[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
	o[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
	o[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];

	o[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
	o[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
	o[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
	o[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];

	o[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
	o[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
	o[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
	o[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];

	o[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
	o[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
	o[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
	o[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];
}

void translate(mat4 &o, vec3 &v) {
	identity(o);
	o[11] = v[0];
	o[12] = v[0];
	o[13] = v[0];
}

void cross(vec3 &o, vec3 &a, vec3 &b) {
	o[0] = a[1] * b[2] - a[2] * b[1];
	o[1] = a[2] * b[0] - a[0] * b[2];
	o[2] = a[0] * b[1] - a[1] * b[0];
}

void add(vec3 &o, vec3 &a, vec3 &b) {
	o[0] = a[0] + b[0];
	o[1] = a[1] + b[1];
	o[2] = a[2] + b[2];
}

void sub(vec3 &o, vec3 &a, vec3 &b) {
	o[0] = a[0] - b[0];
	o[1] = a[1] - b[1];
	o[2] = a[2] - b[2];
}

void normalize(vec3 &o) {
	float f = sqrt(o[1] * o[1] + o[2] * o[2] + o[0] * o[0]);
	o[0] /= f;
	o[1] /= f;
	o[2] /= f;
}

void modelview(mat4 &TR, vec3 &l, vec3 &e, vec3 &u) {
	vec3 x, y, z;//新座標での基底
	sub(z, e, l);
	normalize(z);
	cross(x, u, z);
	normalize(x);
	cross(y, z, x);
	normalize(y);
	mat4 R = {
			x[0], y[0], z[0], 0,
			x[1], y[1], z[1], 0,
			x[2], y[2], z[2], 0,
			0, 0, 0, 1,
	};
	mat4 T = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-e[0], -e[1], -e[2], 1
	};
	product(TR, T, R);
}

void perspective(mat4 &P, float fovy, float aspect, float near, float far) {
	float f = 1.0 / tan((fovy / 180 * M_PI) / 2.0);
	P[0] = f / aspect;
	P[1] = 0;
	P[2] = 0;
	P[3] = 0;

	P[4] = 0;
	P[5] = f;
	P[6] = 0;
	P[7] = 0;

	P[8] = 0;
	P[9] = 0;
	P[10] = (far + near) / (near - far);
	P[11] = -1;

	P[12] = 0;
	P[13] = 0;
	P[14] = 2 * far * near / (near - far);
	P[15] = 0;
}

void transpose(mat4 &o) {
	for (int i = 1; i < 4; ++i) {
		for (int j = 0; j < i; ++j) {
			float t, &a = o[i * 4 + j], &b = o[j * 4 + i];
			t = a;
			a = b;
			b = t;
		}
	}
}

signed genProgram(const char *vsrc, const char *fsrc) {
	printf("GL_VERSION=%s\nGL_SHADING_LANGUAGE_VERSION=%s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
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
	return ProgramID;
}

std::string readAll(const char *filePath) {
	FILE *fp;
	fopen_s(&fp, filePath, "r");
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	std::string str(size, '\0');
	fread((void *) str.c_str(), 1, size, fp);
	fclose(fp);
	return str;
}

signed genProgramFromFile(const char *vsrc, const char *fsrc) {
	return genProgram(readAll(vsrc).c_str(), readAll(fsrc).c_str());
}

GLenum glCheckError_(const char *file, int line) {
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR) {
		const char *error;
		switch (errorCode) {
			case GL_INVALID_ENUM:
				error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				error = "INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:
				error = "STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:
				error = "STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:
				error = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "INVALID_FRAMEBUFFER_OPERATION";
				break;
		}
		printf_s("%s|%s(%d)\n", error, file, line);
	}
	return errorCode;
}