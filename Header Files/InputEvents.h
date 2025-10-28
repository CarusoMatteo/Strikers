#pragma once

#include <vector>
#include <GLFW/glfw3.h>

#include "InputEventsType.h"

using std::vector;

class InputEvents
{
public:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
	static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
	// Add more callbacks as needed here

	vector<bool> *getInputEvents() { return inputEvents; }

private:
	static vector<bool> *inputEvents;

	InputEvents() = default;
	~InputEvents() = default;
};
