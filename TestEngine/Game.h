#pragma once
#include "Entry.h"
#include "Scene.h"
#include "Window.h"
#include <memory>
#include <vector>
#include <algorithm>
#include "AbstractRenderer.h"
#include "CameraComponent.h"

class Game
{
private:
	static std::unique_ptr<Game> Instance;
	std::vector<std::unique_ptr<Entry<Scene>>> Scenes;
	std::unique_ptr<AbstractRenderer> renderer;
	GameObject* selectedCamera;
	Scene* currentScene;
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
	static Game* GetInstance();
	static void ResetInstance();
	void CreateNewScene(std::string name);
	void SetCurrentScene(std::string name);
	template <class Renderer>
	void setRenderer(bool FlipTexture);
	int Run();
	Scene* SceneGetSceneByName(std::string name);
	Scene* GetCurrentScene();
	void setWindowTitle(char* _title);
	void setWindowSize(int w, int h);
	std::pair<int, int> getWindowSize();
	void BindEvent(EventType type, void* func);
	void processInput();
	void moveCamera(int direction, float deltaTime);
	void rotateCamera(float xOffset, float yOffset);
	void SelectCamera(std::string name);
	GameObject* getSelectedCamera();
	GameObject* GetObjectByName(std::string name);
	template<class T>
	std::vector<GameObject*> GetGameObjectsWithComponent() {
		auto gos = currentScene->GetCollapsedObjectTree();
		std::vector<GameObject*> objects = std::vector<GameObject*>();
		for (auto go : gos) {
			if (go->GetComponent<T>() != nullptr) {
				objects.push_back(go);
			}
		}
		return objects;
	}
};

template<class Renderer>
inline void Game::setRenderer(bool FlipTexture)
{
	renderer =std::unique_ptr<AbstractRenderer>(new Renderer(FlipTexture));
}