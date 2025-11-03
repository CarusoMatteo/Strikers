#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

using glm::fmat4;
using glm::ivec2;
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
	static fmat4 createProjectionMatrix(int windowWidth, int windowHeight);
};
