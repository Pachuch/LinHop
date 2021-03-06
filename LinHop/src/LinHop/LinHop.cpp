// LinHop.cpp : Defines the entry point for the application.
// Project uses some of C++17 features
#include "Windows.h"
#include "LinHop.h"
#include "Game.h"

#include "FileManager.h"
#include "../glm/glm.hpp"

constexpr int GAME_WIDTH = 480; /*3*/
constexpr int GAME_HEIGHT = 720; /*4*/

LinHop linhop(GAME_WIDTH, GAME_HEIGHT);
GLFWwindow* window;
extern glm::vec2 mousePos;
extern GameData gameData;

void sizeCallback(GLFWwindow* window, int width, int height)
{
	Info.width = width;
	Info.height = height;
	glViewport(0, 0, width, height);
	linhop.ResetPlayer();
}
void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	mousePos.x = xpos;
	mousePos.y = ypos;
	linhop.Message(666);
}
void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		linhop.Message(key);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		linhop.Message(button);
}

// int main(int argc, char* argv[])
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, static_cast<int>(gameData.unlockResizing));

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(GAME_WIDTH, GAME_HEIGHT, "LinHop", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, sizeCallback);
	glfwSwapInterval(1);
	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetKeyCallback(window, inputCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	
	if (glewInit() != GLEW_OK)
		return -1;

	/* Set view parameters */
	GLCall(glClearColor(0.1f, 0.4f, 0.5f, 1.0f));
	GLCall(glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT));
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	GLCall(glEnable(GL_DEPTH_TEST));

	/* Set texturing parameters */
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	/* Set debug mode */
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorOccurredGL, NULL);

	/* Init */
	linhop.Init();

	/* deltaTime variables */
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/* Poll for and process events */
		glfwPollEvents();

		/* Update game state */
		linhop.Update(deltaTime);

		/* Rendering */
		linhop.ClearScreen(deltaTime);
		linhop.Render(deltaTime);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	linhop.Quit();
	glfwTerminate();
	return 0;
}
