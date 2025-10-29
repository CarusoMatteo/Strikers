#include "../Header Files/InputEvents.h"

vector<bool> *InputEvents::buttonActions = new vector<bool>(static_cast<size_t>(InputEventsType::count), false);
dvec2 *InputEvents::cursorPosition = new dvec2(0.0);

void InputEvents::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		// Close window
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;

	case GLFW_KEY_W | GLFW_KEY_UP:
		if (action == GLFW_PRESS)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_UP)) = true;
		else if (action == GLFW_RELEASE)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_UP)) = false;
		break;

	case GLFW_KEY_S | GLFW_KEY_DOWN:
		if (action == GLFW_PRESS)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_DOWN)) = true;
		else if (action == GLFW_RELEASE)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_DOWN)) = false;
		break;

	case GLFW_KEY_A | GLFW_KEY_LEFT:
		if (action == GLFW_PRESS)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_LEFT)) = true;
		else if (action == GLFW_RELEASE)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_LEFT)) = false;
		break;

	case GLFW_KEY_D | GLFW_KEY_RIGHT:
		if (action == GLFW_PRESS)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_RIGHT)) = true;
		else if (action == GLFW_RELEASE)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::MOVE_RIGHT)) = false;
		break;

	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::SHOOT)) = true;
		else if (action == GLFW_RELEASE)
			InputEvents::buttonActions->at(static_cast<size_t>(InputEventsType::SHOOT)) = false;
		break;

	default:
		break;
	}
}

void InputEvents::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
	// Get screen resolution
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	InputEvents::cursorPosition->x = xpos;
	// Invert y-coordinate to match OpenGL's coordinate system
	InputEvents::cursorPosition->y = height - ypos;
}
