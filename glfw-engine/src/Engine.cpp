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

static void glfwerror_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Engine::Engine(int w, int h, const char *title) : Node::Node(true) {
	StateInt("WIDTH")=w;
	StateInt("HEIGHT")=h;
	name = "Engine";
}

void Engine::Run() {
	int &width = StateInt("WIDTH"),&height = StateInt("HEIGHT");
	GLFWwindow *window;
	{
		glfwInit();
		glfwSetErrorCallback(glfwerror_callback);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(width ,height, "title", NULL, NULL);
		glfwSetKeyCallback(window, key_callback);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
	}
	gladLoadGL(glfwGetProcAddress);
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);axisが表示されないのでコメントアウト
		//glEnable(GL_BLEND);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glUseProgram(genProgramFromFile("standard.vert","standard.frag"));
	}
	Init();
	while (!glfwWindowShouldClose(window)) {
		StateDouble("TIME")=glfwGetTime();
		glfwGetFramebufferSize(window, &width, &height);
		{
			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->NodeDraw();
			glFlush();
			//glCheckError();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDisable(GL_DEPTH_TEST);
	this->NodeTerminate();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Engine::Init() {
	Node *camera;
	NodeNew(camera = new Camera());
	NodeNew(new Axis());
	NodeNew(new Triangle());
	camera->Move(0, 1, 5);
}

void Engine::Draw() {
}

void Engine::Terminate() {
}
