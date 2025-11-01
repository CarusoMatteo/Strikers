#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>
#include <string>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "InputEvents.h"

using glm::mat4;
using std::string;

class Window
{
public:
	Window(string windowTitle);
	~Window();

	bool shouldWindowClose();
	void swapBuffers();
	void pollEvents();
	ivec2 getWindowSize()
	{
		int currentWidth, currentHeight;
		glfwGetWindowSize(this->window, &currentWidth, &currentHeight);
		return ivec2(this->windowWidth, this->windowHeight);
	}

private:
	GLFWwindow *window;
	int windowWidth;
	int windowHeight;

	void initializeWindow(string windowTitle, double monitorPercentageWidth, double monitorPercentageHeight);
	void initInputEvents();
	void initializeGui();
	void initOpenGL();
	glm::mat4 createProjectionMatrix() const;
};
