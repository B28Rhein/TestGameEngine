#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <glad/glad.h>


enum class EventType {
	mouseCallback,
	scrollCallback,
	keyCallback,
};

class Window
{
private:
	int SizeX;
	int SizeY;
	const char* title;
	
public:
	bool WindowCreated = false;
	GLFWwindow* window;
	Window(int SizeX, int SizeY, const char* title);
	std::pair<int, int> GetWindowSize();
	void SetWindowSize(int w, int h);
	void SetWindowTitle(char* _title);
	int Use();
	void Error();
	void RenderEnding();
	int ShouldClose();
	void SetKeyCallback(void (*f)(GLFWwindow*, int, int, int, int));
	void SetMouseCallback(void (*f)(GLFWwindow*, double, double));
	void SetScrollCallback(void (*f)(GLFWwindow*, double, double));
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void CallFramebufferSizeCallback(int width, int height);
	~Window();
};