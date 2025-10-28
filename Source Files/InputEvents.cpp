#include "../Header Files/InputEvents.h"

vector<bool> *InputEvents::inputEvents = new vector<bool>(static_cast<size_t>(InputEventsType::count), false);

void InputEvents::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
}

void InputEvents::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
}

void InputEvents::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
}
