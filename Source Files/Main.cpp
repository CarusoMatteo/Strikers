using namespace std;

#include "../Header Files/Stage.h"

int main(void)
{
	Stage *stage = new Stage(SceneType::MENU, vec4(0.1f, 0.1f, 0.1f, 1.0f));

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
