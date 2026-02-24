#include "Window.h"

Window::Window(int SizeX, int SizeY, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SizeX, SizeY, title, NULL, NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if(window != NULL)
	{
		WindowCreated = true;
	}
	this->SizeX = SizeX;
	this->SizeY = SizeY;
	this->title = title;
	if (!Use())
	{
		Error();
		delete this;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		delete this;
	}
	glViewport(0, 0, SizeX, SizeY);
}

std::pair<int, int> Window::GetWindowSize()
{
	return std::pair<int, int>(SizeX, SizeY);
}

void Window::SetWindowSize(int w, int h)
{
	SizeX = w;
	SizeY = h;
	glfwSetWindowSize(window, w, h);
}

void Window::SetWindowTitle(char* _title) {
	title = _title;
	glfwSetWindowTitle(window, _title);
}

void Window::SetKeyCallback(void (*f)(GLFWwindow*, int, int, int, int)) {
	glfwSetKeyCallback(window, f);
}

void Window::SetMouseCallback(void(*f)(GLFWwindow*, double, double))
{
	glfwSetCursorPosCallback(window, f);
}

void Window::SetScrollCallback(void(*f)(GLFWwindow*, double, double))
{
	glfwSetScrollCallback(window, f);
}

int Window::Use()
{
	if (WindowCreated)
	{
		glfwMakeContextCurrent(window);
		return true;
	}
	return false;
}

void Window::Error()
{
	std::cout << "Failed to Create Window" << std::endl;
	glfwTerminate();
}

void Window::RenderEnding()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

int Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::CallFramebufferSizeCallback(int width, int height) {
	FramebufferSizeCallback(window, width, height);
}