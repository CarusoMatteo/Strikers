#include "../Header Files/Window.h"

#include "../Header Files/Mesh.h"
#include "../Header Files/InputEvents.h"

Window::Window(string windowTitle)
{
	this->initializeWindow(windowTitle, 0.8, 0.8);
	this->initInputEvents();
	this->initializeGui();
	this->initOpenGL();

	InputEvents::setCurrentWindowSize(ivec2(this->windowWidth, this->windowHeight));
	Mesh::setProjectionMatrix(createProjectionMatrix(this->windowWidth, this->windowHeight));
}

Window::~Window()
{
	// Free ImGui resources
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Destroy window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::shouldWindowClose()
{
	return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(this->window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::initializeWindow(string windowTitle, double monitorPercentageWidth, double monitorPercentageHeight)
{
	// If glfwInit fails, throw an exception.
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	// Set the context version and profile properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Enable double buffering
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();

	// Gets the resolution of the monitor
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	// Sets the window dimensions to a fixed game size
	this->windowWidth = 1920;
	this->windowHeight = 1080;

	// Create a window and its OpenGL context
	this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, windowTitle.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwSetWindowAspectRatio(window, this->windowWidth, this->windowHeight);

	/*
	 * Creates the current context and associates it to window.
	 * In OpenGL a rendering context is a state machine that stores all the necessary information and resources for graphic rendering.
	 */
	glfwMakeContextCurrent(window);

	// Check if GLAD is able to load the OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw new std::runtime_error("Failed to load OpenGL function pointers");
	}

	// Choose cursor mode (normal, hidden, disabled, infinte), and its initial position
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// glfwSetCursorPos(window, 0, 0);

	// Resize window to fraction of monitor size
	int newWidth = static_cast<int>(mode->width * monitorPercentageWidth);
	int newHeight = static_cast<int>(mode->height * monitorPercentageHeight);
	glfwSetWindowSize(this->window, newWidth, newHeight);

	glViewport(0, 0, newWidth, newHeight);

	// Enable V-Sync
	glfwSwapInterval(1);
}

void Window::initInputEvents()
{
	glfwSetKeyCallback(window, InputEvents::keyCallback);
	glfwSetCursorPosCallback(window, InputEvents::cursorPositionCallback);
	glfwSetFramebufferSizeCallback(window, InputEvents::framebufferSizeCallback);
}

void Window::initializeGui()
{
	// Check ImGui compatibility
	IMGUI_CHECKVERSION();
	// Create ImGui context
	ImGui::CreateContext();
	// Get ImGui IO object for configuration and input handling
	ImGuiIO &io = ImGui::GetIO();
	// Sets global font scale
	io.FontGlobalScale = 2.0f;
	// Set GUI color style
	ImGui::StyleColorsDark();

	// Initializes ImGui integration with GLFW for OpenGL
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	// Sets OpenGL version for ImGui
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Window::initOpenGL()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

fmat4 Window::createProjectionMatrix(int windowWidth, int windowHeight)
{
	return ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
}
