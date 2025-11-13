using namespace std;

#include <GLFW/glfw3.h>

#include "../Header Files/Stage.h"

using glm::fvec3;
using std::string;

int main(void)
{
	const SceneType startingScene = SceneType::MENU;
	SceneType currentScene = startingScene;
	bool startGame = false;
	fvec3 clearColor = fvec3(0.1f, 0.1f, 0.1f);
	string windowTitle = "Strikers";

	Stage *stage = new Stage(startingScene, clearColor, windowTitle, &startGame);

	float lastFrameTime = 0.0f;

	while (!stage->shouldWindowClose())
	{
		if (startGame && currentScene == SceneType::MENU)
		{
			stage->changeScene(SceneType::GAME, &startGame);
			startGame = false;
			currentScene = SceneType::GAME;
		}
		else if (startGame && currentScene == SceneType::GAME)
		{
			stage->changeScene(SceneType::MENU, &startGame);
			startGame = false;
			currentScene = SceneType::MENU;
		}

		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - lastFrameTime;

		stage->drawClearColor();
		stage->updateGameObjects(deltaTime);
		stage->renderCurrentScene(currentTime);
		stage->swapBuffers();
		stage->pollEvents();

		lastFrameTime = currentTime;
	}

	delete stage;
	return 0;
}
