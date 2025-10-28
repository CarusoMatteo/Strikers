#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
	Window() = default;
	~Window() = default;

private:
	GLFWwindow *window;

	void initializeWindow();
	void initializeGui();
};
