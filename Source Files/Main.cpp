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

	while (!stage->shouldWindowClose())
	{
		stage->drawClearColor();
		stage->renderCurrentScene();
		stage->swapBuffers();
		stage->pollEvents();
	}

	delete stage;
	return 0;
}
