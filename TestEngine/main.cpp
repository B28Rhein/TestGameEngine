#define GLM_ENABLE_EXPERIMENTAL
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
#include "Renderer3D.h"

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
	auto currentScene = g->GetCurrentScene();
	g->setRenderer<Renderer3D>(true);

	std::pair<int, int> WindowSize = g->getWindowSize();
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	//Camera* tmp = new Camera(1.5f, 0.1f, cameraPos, cameraFront, cameraUp, CameraMode::Flying3DCamera, WindowSize);
	Shader* shader = new Shader("default.vs", "default.frs");

	GameObject* camera = new GameObject(0, 0, 0);
	camera->AddComponent<MeshComponent>();

	camera->AddComponent<CameraComponent>();
	camera->GetComponent<CameraComponent>()->setFront(cameraFront);
	camera->GetComponent<CameraComponent>()->setUpVector(cameraUp);
	camera->GetComponent<CameraComponent>()->setOffset(glm::vec3(0,0,0));
	camera->GetComponent<MeshComponent>()->setMesh(cubeVerts);
	camera->GetComponent<MeshComponent>()->AssignTexture("testTexture.png");
	camera->GetComponent<MeshComponent>()->setShader(shader);
	currentScene->AddObject(std::shared_ptr<GameObject>(camera), "camera1");
	g->SelectCamera("camera1");


	g->BindEvent(EventType::mouseCallback, mouse_callback);


	std::shared_ptr<GameObject> p = std::shared_ptr<GameObject>(new GameObject(0, -1, 0));
	p->AddComponent<MeshComponent>();
	p->GetComponent<MeshComponent>()->setMesh(cubeVerts);
	p->GetComponent<MeshComponent>()->AssignTexture("testTexture.png");
	p->GetComponent<MeshComponent>()->setShader(shader);
	p->GetComponent<TransformComponent>()->SetScale(glm::vec3(1000, 1, 1000));
	std::shared_ptr<GameObject> go = std::shared_ptr<GameObject>(new GameObject(5, 0, 0));
	go->AddComponent<MeshComponent>();
	go->GetComponent<MeshComponent>()->setMesh(cubeVerts);
	go->GetComponent<MeshComponent>()->AssignTexture("testTexture.png");
	go->GetComponent<MeshComponent>()->setShader(shader);
	go->GetComponent<TransformComponent>()->SetScale(glm::vec3(1, 1, 1));
	go->GetComponent<MeshComponent>()->setTexMod(glm::vec3(1, 1, 1), 0.5);
	std::shared_ptr<GameObject> go2 = std::shared_ptr<GameObject>(new GameObject(0, 0, 0));
	go2->AddComponent<MeshComponent>();
	go2->GetComponent<MeshComponent>()->setMesh(cubeVerts);
	go2->GetComponent<MeshComponent>()->AssignTexture("testTexture.png");
	go2->GetComponent<MeshComponent>()->setShader(shader);
	go2->GetComponent<TransformComponent>()->SetScale(glm::vec3(1, 1, 1));
	go2->GetComponent<MeshComponent>()->setTexMod(glm::vec3(1, 1, 1), 0.5);
	currentScene->AddObject(go, "cube1");
	currentScene->AddObject(go2, "cube2");
	currentScene->AddObject(p, "plane1");

	//currentScene->AddObject(p, "plane1");


	g->Run();
	
	//glDeleteBuffers(1, &VBO);
	//glDeleteVertexArrays(1, &lightVAO);
	//delete ourShader;
	//delete LightShader;
	//delete texture1;
	delete shader;
	glfwTerminate();
	currentScene->GetObjectByName("cube1")->removeChild("plane1");
	p = nullptr;
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

	g->rotateCamera(xoffset, yoffset);
}


