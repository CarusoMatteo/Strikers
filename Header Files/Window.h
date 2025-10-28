#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "InputEvents.h"

using std::string;

class Window
{
public:
	Window(string windowTitle);
	~Window();

	bool shouldWindowClose();
	void swapBuffers();
	void pollEvents();

private:
	GLFWwindow *window;
	int windowWidth;
	int windowHeight;

	void initializeWindow(string windowTitle, double monitorPercentageWidth, double monitorPercentageHeight);
	void initInputEvents();
	void initializeGui();
	void initOpenGL();
};
