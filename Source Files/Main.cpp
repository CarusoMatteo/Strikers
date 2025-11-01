using namespace std;

#include <string>
#include <glm/glm.hpp>
#include "../Header Files/Stage.h"

using glm::vec3;
using std::string;

int main(void)
{
	SceneType startingScene = SceneType::MENU;
	vec3 clearColor = vec3(0.1f, 0.1f, 0.1f);
	string windowTitle = "Shooter Game";

	Stage *stage = new Stage(startingScene, clearColor, windowTitle);

	float lastFrameTime = 0.0f;
	while (!stage->shouldWindowClose())
	{
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
