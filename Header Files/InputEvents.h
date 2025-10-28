#pragma once

#include <vector>
#include <GLFW/glfw3.h>

using std::vector;

class InputEvents
{
public:
	static vector<bool> inputEvents;

	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	// Add more callbacks as needed here

private:
	InputEvents() = default;
	~InputEvents() = default;
};
