//
// Created by misum on 2020/11/15.
//

#include "Engine.h"

#include "Node/Axis.h"
#include "Node/Camera.h"

#include "Graphics.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <math.h>

static void error_callback(int error, const char* description){
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Engine::Engine(int w, int h, const char *title) :Node(true){
	Stat&windowinfo=NodeState("WINDOW");
	windowinfo.x=w;
	windowinfo.y=h;
	windowinfo.text=title;
}

void Engine::Run(){
	Stat&windowinfo=NodeState("WINDOW");
	GLFWwindow** window=(GLFWwindow**)(&Window);
	if (!glfwInit())Log("Initiation Failed",LOGERROR);
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	*window = glfwCreateWindow(windowinfo.x, windowinfo.y, windowinfo.text, NULL, NULL);
	if (!window){
		glfwTerminate();
		Log("window creation failed",LOGERROR);
	}

	glfwSetKeyCallback(*window, key_callback);

	glfwMakeContextCurrent(*window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);
	Init();
	while (!glfwWindowShouldClose(*window)){
		float ratio;
		int width, height;
		//mat4x4 m, p, mvp;
		glfwGetFramebufferSize(*window, &width, &height);
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		this->NodeDraw();
		glfwSwapBuffers(*window);
		glfwPollEvents();
	}
	this->NodeTerminate();
}
void Engine::Init(){
	Node*camera;
	NodeNew(camera=new Camera());
	NodeNew(new Axis());
	camera->Move(0,1,5);
}
void Engine::Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	double t=glfwGetTime();
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5+0.5*sin(5*M_PI*t), 0.5+0.5*sin(7*M_PI*t), 0.5+0.5*sin(11*M_PI*t));
	glVertex2f(sin(2*M_PI*t), sqrt(3));
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
	glFlush();
}
void Engine::Terminate() {
	glfwDestroyWindow(*(GLFWwindow **)(Window));
	glfwTerminate();
}

char Log(const char *message, LOGLEVEL level) {
	fputs(message,stderr);
	return 0;
}
