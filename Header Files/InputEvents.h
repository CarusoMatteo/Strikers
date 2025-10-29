#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "InputEventsType.h"
#include "Mesh.h"

using namespace glm;
using std::vector;

class InputEvents
{
public:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
	static void framebufferSizeCallback(GLFWwindow *window, int windowWidth, int windowHeight);
	// Add more callbacks as needed here

	static vector<bool> *getButtonActions()
	{
		return buttonActions;
	}
	static dvec2 *getCursorPosition()
	{
		return cursorPosition;
	}
	static void setStartingWindowSize(int width, int height)
	{
		InputEvents::startingWindowSize = new fvec2(static_cast<float>(width), static_cast<float>(height));
	}

private:
	static vector<bool> *buttonActions;
	static dvec2 *cursorPosition;
	// Starting [Width, Height] of window (and world).
	static fvec2 *startingWindowSize;

	InputEvents() = default;
	~InputEvents() = default;
};
