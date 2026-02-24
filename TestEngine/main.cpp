#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <format>
#include <string>
#include "Shader.h"
#include "Window.h"
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"
#include "Renderer3D.h"
#include "Renderer2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define SIZE(array) (sizeof(array) / sizeof(array[0]))

#define WindowSizeX 800.0f
#define WindowSizeY 600.0f

#define DarkGreen 0.2f, 0.3f, 0.3, 1.0f
#define DeepBlue 0.0f, 0.0f, 1.0f, 1.0f
#define DeepGreen 0.0f, 1.0f, 0.0f, 1.0f
#define DeepRed 1.0f, 0.0f, 0.0f, 1.0f
#define Black 0.1f, 0.1f, 0.1f, 1.0f




float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;

bool firstCamera = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(AbstractRenderer* rend, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float planeVerts[] = {
	-0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
	 0.5f, -1.0f,  0.5f,  1.0f, 0.0f,
	 0.5f, -1.0f, -0.5f,  1.0f, 1.0f,
	 0.5f, -1.0f,  0.5f,  1.0f, 0.0f,
	-0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
	-0.5f, -1.0f,  0.5f,  0.0f, 0.0f,
};

float cubeVerts[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
};

class MyGame : public Game {
public:
	MyGame() : Game() {};
};

int main()
{
	auto g = MyGame::GetInstance();
	g->setWindowSize(800, 600);
	g->setWindowTitle((char*)"Test Engine");

	g->CreateNewScene("Scene1");
	g->SetCurrentScene("Scene1");
	auto currentScene = g->GetCurrentScene()->Object;
	g->setRenderer<Renderer3D>(true);

	std::pair<int, int> WindowSize = g->getWindowSize();
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera* tmp = new Camera(1.5f, 0.1f, cameraPos, cameraFront, cameraUp, CameraMode::Flying3DCamera, WindowSize);
	currentScene->AddObject(std::shared_ptr<GameObject>(tmp), "camera1");
	g->SelectCamera("camera1");


	g->BindEvent(EventType::mouseCallback, mouse_callback);

	Shader* shader = new Shader("default.vs", "default.frs");

	std::shared_ptr<GameObject> p = std::shared_ptr<GameObject>(new GameObject(0, -1, 0));
	p->AddComponent<MeshComponent>();
	p->GetComponent<MeshComponent>()->setMesh(cubeVerts);
	p->GetComponent<MeshComponent>()->AssignTexture("testTexture.png");
	p->GetComponent<MeshComponent>()->setShader(shader);
	p->GetComponent<MeshComponent>()->setScale(glm::vec3(1000, 1, 1000));
	currentScene->AddObject(p, "plane1");
	std::shared_ptr<GameObject> go = std::shared_ptr<GameObject>(new GameObject(5, 5, 5));
	go->AddComponent<MeshComponent>();
	go->GetComponent<MeshComponent>()->setMesh(cubeVerts);
	go->GetComponent<MeshComponent>()->AssignTexture("testTexture.png");
	go->GetComponent<MeshComponent>()->setShader(shader);
	go->GetComponent<MeshComponent>()->setScale(glm::vec3(1, 1, 1));
	go->GetComponent<MeshComponent>()->setTexMod(glm::vec3(1, 1, 1), 0.3);
	currentScene->AddObject(go, "cube1");
	
	//currentScene->AddObject(p, "plane1");


	g->Run();
	
	//glDeleteBuffers(1, &VBO);
	//glDeleteVertexArrays(1, &lightVAO);
	//delete ourShader;
	//delete LightShader;
	//delete texture1;
	delete shader;
	glfwTerminate();
	currentScene->GetObjectByName("cube1").Object->removeChild("plane1");
	p = nullptr;
	auto l = currentScene->GetObjectByName("cube1").Object->getPos();
	go = nullptr;
	currentScene->RemoveObject("cube1");
	return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	auto g = Game::GetInstance();

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	g->getSelectedCamera()->rotateCamera(xoffset, yoffset);
}


