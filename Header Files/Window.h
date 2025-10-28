#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
	Window() = default;
	~Window() = default;

	bool shouldWindowClose();
	void swapBuffers();
	void pollEvents();

private:
	GLFWwindow *window;

	void initializeWindow();
	void initializeGui();
};
