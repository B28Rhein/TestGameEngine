#pragma once
#include "Entry.h"
#include "Scene.h"
#include "Window.h"
#include <memory>
#include <vector>
#include "AbstractRenderer.h"

class Game
{
private:
	static std::shared_ptr<Game> Instance;
	std::vector<std::shared_ptr<Entry<Scene>>> Scenes;
	std::shared_ptr <Entry<Scene>> currentScene;
	std::unique_ptr<AbstractRenderer> renderer;
	Window* window;
	int CreateWindow(int width, int height, char* title);
	char* windowTitle = (char*)"Game";
	std::pair<int, int> windowSize = std::pair<int, int>(800, 600);
	int GetWindowShouldClose();
	GLFWwindow* getWindow();
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
public:
	Game();
	static std::shared_ptr<Game> GetInstance();
	static void ResetInstance();
	void CreateNewScene(std::string name);
	void SetCurrentScene(std::string name);
	template <class Renderer>
	void setRenderer(bool FlipTexture);
	int Run();
	std::shared_ptr<Entry<Scene>> GetSceneByName(std::string name);
	std::shared_ptr<Entry<Scene>> GetCurrentScene();
	void setWindowTitle(char* _title);
	void setWindowSize(int w, int h);
	std::pair<int, int> getWindowSize();
	void BindEvent(EventType type, void* func);
	void processInput();
	void SelectCamera(std::string name);
	AbstractCamera* getSelectedCamera();
	
};

template<class Renderer>
inline void Game::setRenderer(bool FlipTexture)
{
	renderer =std::unique_ptr<AbstractRenderer>(new Renderer(FlipTexture));
}