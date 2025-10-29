#include "../Header Files/InputEvents.h"

vector<bool> *InputEvents::buttonActions = new vector<bool>();
fvec2 *InputEvents::startingWindowSize = nullptr;
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

void InputEvents::framebufferSizeCallback(GLFWwindow *window, int newWidth, int newHeight)
{
	if (InputEvents::startingWindowSize == nullptr)
	{
		throw std::runtime_error("startingWindowSize not set in InputHandler.\nSet them when setting inputCallbacks in Window.");
	}

	float newWindowHeight = static_cast<float>(newWidth);
	float newWindowWidth = static_cast<float>(newHeight);
	float viewportWidth, wiewportHeight;

	// Offset to center the viewport
	float xOffset = 0.0, yOffset = 0.0;

	// Prevent division by zero
	if (newWindowHeight == 0)
		newWindowHeight = 1;

	// Calculate the aspect ratio of the "world"
	float worldAspectRatio = InputEvents::startingWindowSize->x / InputEvents::startingWindowSize->y;

	// Adjust the viewport based on the aspect ratio between the world and the window
	if (worldAspectRatio > newWindowWidth / newWindowHeight)
	{
		// The world is relatively wider than the window.
		// - Viewport width = Window width
		// - Viewport height is reduced
		viewportWidth = newWindowWidth;
		wiewportHeight = newWindowWidth / worldAspectRatio;
		// Calculate vertical offset to center the viewport in the taller framebuffer
		yOffset = (newWindowHeight - wiewportHeight) / 2.0f;
	}
	else
	{
		// The world is relatively narrower or taller than the window.
		// - Viewport height = Window height
		// - Viewport width is reduced

		wiewportHeight = newWindowHeight;
		viewportWidth = newWindowHeight * worldAspectRatio;
		// Calculate horizontal offset to center the viewport in the wider framebuffer
		xOffset = (newWindowWidth - viewportWidth) / 2.0f;
	}

	// Sets the OpenGL viewport with calculated offsets and dimensions to center it and maintain the correct aspect ratio
	glViewport(xOffset, yOffset, viewportWidth, wiewportHeight);
}
