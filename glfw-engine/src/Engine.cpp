//
// Created by misum on 2020/11/15.
//

#include "Engine.h"

#include "Node/Axis.h"
#include "Node/Camera.h"
#include "Node/Triangle.h"

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

Engine::Engine(int w, int h, const char *title):Node::Node(true){
	Stat&windowinfo=NodeState("WINDOW");
	windowinfo.x=w;
	windowinfo.y=h;
	windowinfo.text=title;
	name="Engine";
}

void Engine::Run(){
	Stat&windowinfo=NodeState("WINDOW");
	GLFWwindow** window=(GLFWwindow**)(&Window);
	if (!glfwInit())Log("Initiation Failed",LOGERROR);
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	*window = glfwCreateWindow(windowinfo.x, windowinfo.y, windowinfo.text, NULL, NULL);
	if (!*window){
		glfwTerminate();
		Log("window creation failed",LOGERROR);
	}
	glfwSetKeyCallback(*window, key_callback);
	glfwMakeContextCurrent(*window);
	glfwSwapInterval(1);
	windowinfo.frq=glfwGetTimerFrequency();
	gladLoadGL(glfwGetProcAddress);
	Init();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	while (!glfwWindowShouldClose(*window)){
		windowinfo.time=glfwGetTimerValue();
		glfwGetFramebufferSize(*window, &windowinfo.x, &windowinfo.y);
		glViewport(0, 0, windowinfo.x, windowinfo.y);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->NodeDraw();
		glFlush();
		glfwSwapBuffers(*window);
		glfwPollEvents();
	}
	glDisable(GL_DEPTH_TEST);
	this->NodeTerminate();
	glfwDestroyWindow(*(GLFWwindow **)(Window));
	glfwTerminate();
}
void Engine::Init(){
	Node*camera;
	NodeNew(camera=new Camera());
	NodeNew(new Axis());
	NodeNew(new Triangle());
	camera->Move(0,1,5);
}
void Engine::Draw() {
}
void Engine::Terminate() {
}

char Log(const char *message, LOGLEVEL level) {
	fputs(message,stderr);
	return 0;
}
