#include "Game.h"

std::unique_ptr<Game> Game::Instance = nullptr;

int Game::CreateWindow(int width, int height, char* title)
{
	window = new Window(width, height, title);
	
	std::pair<int, int> WindowSize = window->GetWindowSize();

	return 0;
}

Game::Game()
{
	
	CreateWindow(windowSize.first, windowSize.second, windowTitle);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Game* Game::GetInstance()
{
	if (Instance == nullptr) {
		Instance = std::make_unique<Game>();
	}
	return Game::Instance.get();
}

void Game::ResetInstance()
{
	Instance = nullptr;
}

void Game::CreateNewScene(std::string name)
{
	//std::unique_ptr<Entry<Scene>> e = std::unique_ptr<Entry<Scene>>(new Entry<Scene>(name, std::shared_ptr<Scene>(new Scene())));
	Scenes.push_back(std::make_unique<Entry<Scene>>(name, std::make_shared<Scene>()));
}

void Game::SetCurrentScene(std::string name)
{
	Scene* s = SceneGetSceneByName(name);
	if (s == nullptr) {
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
		auto go = this->currentScene->GetObjectByName("cube2");
		TransformComponent* tc = go->GetComponent<TransformComponent>();
		tc->ChangeRotBy(glm::vec3(1, 1, 1));
		//rendering

		RendererManager::GetInstance()->Render();
		window->RenderEnding();
		//end rendering

	}
	return 0;

}

Scene* Game::SceneGetSceneByName(std::string name)
{
	for (int i = 0; i < Scenes.size(); i++) {
		if (Scenes[i]->name == name) {
			return Scenes[i]->Object.get();
		}
	}
	return nullptr;
}

Scene* Game::GetCurrentScene()
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
	moveCamera(direction, deltaTime);
}

void Game::moveCamera(int direction, float deltaTime)
{
	CameraComponent* cc = selectedCamera->GetComponent<CameraComponent>();
	glm::vec3 front = cc->getFront();
	glm::vec3 up = cc->getUpVector();

	glm::vec3 moveVector = glm::vec3(0.0f, 0.0f, 0.0f);
	moveVector += front * (float)(direction % 2);
	direction >>= 1;
	moveVector -= front * (float)(direction % 2);
	direction >>= 1;
	moveVector -= glm::normalize(glm::cross(front, up)) * (float)(direction % 2);
	direction >>= 1;
	moveVector += glm::normalize(glm::cross(front, up)) * (float)(direction % 2);
	direction >>= 1;
	float currentSpeed = 2 + 2 * direction;
	if (moveVector != glm::vec3(0.0f))
	{
		moveVector = glm::normalize(moveVector) * currentSpeed * deltaTime;
		selectedCamera->GetComponent<TransformComponent>()->ChangePosBy(moveVector);
	}
}

void Game::rotateCamera(float xOffset, float yOffset)
{
	xOffset *= 0.1;
	yOffset *= 0.1;

	CameraComponent* cc = selectedCamera->GetComponent<CameraComponent>();
	glm::vec3 front = cc->getFront();
	glm::vec3 pyr = cc->getPitchYawRoll();
	float yaw = pyr.y;
	float pitch = pyr.x;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cc->setFront(glm::normalize(direction));
	cc->setPitchYawRoll(pitch, yaw, pyr.z);
}

void Game::SelectCamera(std::string name)
{
	GameObject* go = GetObjectByName(name);
	CameraComponent* cc = go->GetComponent<CameraComponent>();
	if (cc != nullptr) {
		selectedCamera = go;
	}
}

GameObject* Game::getSelectedCamera()
{
	return selectedCamera;
}

GameObject* Game::GetObjectByName(std::string name)
{
	return currentScene->GetObjectByName(name);
}

