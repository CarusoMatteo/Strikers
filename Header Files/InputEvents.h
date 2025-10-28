#pragma once

#include <vector>
#include <GLFW/glfw3.h>

using std::vector;

class InputEvents
{
public:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
	// Add more callbacks as needed here

	vector<bool> *getInputEvents() { return &inputEvents; }

private:
	static vector<bool> inputEvents;

	InputEvents() = default;
	~InputEvents() = default;
};
