#include "Game.h"

std::shared_ptr<Game> Game::Instance = nullptr;

int Game::CreateWindow(int width, int height, char* title)
{
	window = new Window(width, height, title);
	
	std::pair<int, int> WindowSize = window->GetWindowSize();

	return 0;
}

Game::Game()
{
	
	CreateWindow(windowSize.first, windowSize.second, windowTitle);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

std::shared_ptr<Game> Game::GetInstance()
{
	if (Instance == nullptr) {
		Instance = std::shared_ptr<Game>(new Game);
	}
	return Game::Instance;
}

void Game::ResetInstance()
{
	Instance = nullptr;
}

void Game::CreateNewScene(std::string name)
{
	std::shared_ptr<Entry<Scene>> e = std::shared_ptr<Entry<Scene>>(new Entry<Scene>(name, std::shared_ptr<Scene>(new Scene())));
	Scenes.push_back(e);
}

void Game::SetCurrentScene(std::string name)
{
	std::shared_ptr<Entry<Scene>> s = GetSceneByName(name);
	if (s->Object == nullptr) {
		std::cout << "Scene with name " << name << " not found\n";
		return;
	}
	currentScene = s;
}

int Game::Run()
{
	while (!GetWindowShouldClose())
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//input
		processInput();
		//end input
		//rendering

		renderer->Render();
		window->RenderEnding();
		//end rendering

	}
	return 0;

}

std::shared_ptr<Entry<Scene>> Game::GetSceneByName(std::string name)
{
	for (auto s : Scenes) {
		if (s->name == name) {
			return s;
		}
	}
	return std::shared_ptr<Entry<Scene>>(new Entry<Scene>("Not Found", nullptr));
}

std::shared_ptr<Entry<Scene>> Game::GetCurrentScene()
{
	return currentScene;
}

void Game::setWindowTitle(char* _title)
{
	windowTitle = _title;
	if (window != nullptr) {
		window->SetWindowTitle(_title);
	}
}

void Game::setWindowSize(int w, int h)
{
	windowSize = std::pair<int, int>(w, h);
	if (window != nullptr) {
		window->SetWindowSize(w, h);
	}
}

std::pair<int, int> Game::getWindowSize()
{
	return windowSize;
}

int Game::GetWindowShouldClose()
{
	return window->ShouldClose();
}

GLFWwindow* Game::getWindow()
{
	return window->window;
}

void Game::BindEvent(EventType type, void* func)
{
	void (*fi)(GLFWwindow*, int, int, int, int);
	void (*fd)(GLFWwindow*, double, double);
	switch (type) {
	case EventType::keyCallback:
		fi = ((void(*)(GLFWwindow*, int, int, int, int))func);
		window->SetKeyCallback(fi);
		break;
	case EventType::mouseCallback:
		fd = ((void(*)(GLFWwindow*, double, double))func);
		window->SetMouseCallback(fd);
		break;
	case EventType::scrollCallback:
		fd = ((void(*)(GLFWwindow*, double, double))func);
		window->SetScrollCallback(fd);
		break;
	}
}

void Game::processInput()
{
	int direction = 0;
	GLFWwindow* window = getWindow();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_KP_ADD)) {
		auto size = getWindowSize();
		size.first += 10;
		size.second += 10;
		setWindowSize(size.first, size.second);
		//renderer->getSelectedCamera()->setWindowSize(size);
		this->window->CallFramebufferSizeCallback( size.first, size.second);
	}
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT)) {
		auto size = getWindowSize();
		size.first -= 10;
		size.second -= 10;
		setWindowSize(size.first, size.second);
		//renderer->getSelectedCamera()->setWindowSize(size);
		this->window->CallFramebufferSizeCallback( size.first, size.second);
	}

	direction = glfwGetKey(window, GLFW_KEY_W) * 0b00001 +
		glfwGetKey(window, GLFW_KEY_S) * 0b00010 +
		glfwGetKey(window, GLFW_KEY_A) * 0b00100 +
		glfwGetKey(window, GLFW_KEY_D) * 0b01000 +
		glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) * 0b10000;
	renderer->getSelectedCamera()->moveCamera(direction, deltaTime);
}

void Game::SelectCamera(std::string name)
{
	renderer->SelectCameraByName(name);
}

AbstractCamera* Game::getSelectedCamera()
{
	return renderer->getSelectedCamera();
}

