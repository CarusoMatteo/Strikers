#pragma once

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "InputEventsType.h"
#include "Mesh.h"

using namespace glm;
using std::array;
using ButtonStates = std::array<bool, static_cast<size_t>(InputEventsType::count)>;

class InputEvents
{
public:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
	static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
	// Add more callbacks as needed here

	static ButtonStates *getButtonStates()
	{
		return buttonStates;
	}
	static dvec2 *getCursorPosition()
	{
		return cursorPosition;
	}

private:
	static ButtonStates *buttonStates;
	static dvec2 *cursorPosition;

	InputEvents() = default;
	~InputEvents() = default;
};
