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
void copy(mat4&o,const double*a){
	for(int i=0;i<16;++i)o[i]=a[i];
}
void copy(mat4&o,const float*a){
	for(int i=0;i<16;++i)o[i]=a[i];
}

void product(mat4 &o, const mat4 &a, const mat4 &b) {
	for(int g=0;g<4;g++){
		for(int r=0;r<4;r++){
			float &m=o[g+4*r]=0;
			for(int k=0;k<4;k++)m+=a[g+4*k]*b[k+r*4];
		}
	}
}

void productscale(mat4&o,const vec3&a,const mat4&b){
	o[0]=b[0]*a[0];
	o[1]=b[1]*a[1];
	o[2]=b[2]*a[2];
	o[3]=b[3];
	o[4]=b[4]*a[0];
	o[5]=b[5]*a[1];
	o[6]=b[6]*a[2];
	o[7]=b[7];
	o[8]=b[8]*a[0];
	o[9]=b[9]*a[1];
	o[10]=b[10]*a[2];
	o[11]=b[11];
	o[12]=b[12]*a[0];
	o[13]=b[13]*a[1];
	o[14]=b[14]*a[2];
	o[15]=b[15];
}
void productrotation(mat4&o,const vec4&a,const mat4&b){
	//https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	const float &qx=a[0],&qy=a[1],&qz=a[2],&qw=a[3];
	mat4 am={
			1- 2*qz*qz- 2*qy*qy,2*qx*qy+ 2*qw*qz,2*qx*qz- 2*qw*qy,0,
			- 2* qz*qw+2*qy*qx,	1 - 2*qz*qz - 2*qx*qx,2*qy*qz + 2*qw*qx,0,
			2*qy*qw +2* qz*qx,	2*qz*qy- 2*qx*qw,	1- 2*qy*qy- 2*qx*qx,0,
			0,0,0,1
	};
	product(o,am,b);
}
void producttranslation(mat4&o,const vec3&a,const mat4&b){
	o[0]=b[0];
	o[1]=b[1];
	o[2]=b[2];
	o[3]=b[3];
	o[4]=b[4];
	o[5]=b[5];
	o[6]=b[6];
	o[7]=b[7];
	o[8]=b[8];
	o[9]=b[9];
	o[10]=b[10];
	o[11]=b[11];
	o[12]=b[12]+a[0];
	o[13]=b[13]+a[1];
	o[14]=b[14]+a[2];
	o[15]=b[15];
}

void cross(vec3 &o, const vec3 &a, const vec3 &b) {
	o[0] = a[1] * b[2] - a[2] * b[1];
	o[1] = a[2] * b[0] - a[0] * b[2];
	o[2] = a[0] * b[1] - a[1] * b[0];
}

void add(vec3 &o, const vec3 &a, const vec3 &b) {
	o[0] = a[0] + b[0];
	o[1] = a[1] + b[1];
	o[2] = a[2] + b[2];
}

void sub(vec3 &o, const vec3 &a, const vec3 &b) {
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

void modelview(mat4 &RT, vec3 &l, vec3 &e, vec3 &u) {
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
	//transpose(R);
	mat4 T = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-e[0], -e[1], -e[2], 1
	};
	//transpose(T);
	product(RT, R, T);
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
	//transpose(P);
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