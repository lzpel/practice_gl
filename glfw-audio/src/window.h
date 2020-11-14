#pragma once

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window
{
public:
	GLFWwindow* window;

	Window(int x, int y, const char* title);
	~Window();
	void Resize();
	int Close();
};

