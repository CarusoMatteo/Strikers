#include "../Header Files/Stage.h"

Stage::Stage(SceneType startingScene, vec3 clearColor, string windowTitle)
{
	this->window = new Window(windowTitle);
	this->clearColor = clearColor;

	createScenes();
	this->changeScene(startingScene);
}

Stage::~Stage()
{
	delete this->window;
}

void Stage::createScenes()
{
	this->scenes = Scenes{};

	scenes.at(static_cast<size_t>(SceneType::MENU)) = std::make_unique<Scene>(
		new Background(MeshBuilder::buildPlane(
			".\\Shader Files\\Background\\BackgroundVertex.glsl",
			".\\Shader Files\\Background\\BackgroundFragment.glsl",
			true,
			this->window->getWindowSize(),
			fvec3(this->window->getWindowSize().x, this->window->getWindowSize().y, 1.0f),
			fvec4(1, 0, 0, 1),
			fvec4(0, 1, 0, 1),
			fvec4(0, 0, 1, 1),
			fvec4(1, 1, 1, 1),
			mat4(1.0f))),
		new vector<IGameObject *>(),
		new MenuGui(&this->clearColor));

	scenes.at(static_cast<size_t>(SceneType::GAME)) = std::make_unique<Scene>(
		new Background(MeshBuilder::buildPlane(
			".\\Shader Files\\Default\\DefaultVertex.glsl",
			".\\Shader Files\\Default\\DefaultFragment.glsl",
			true,
			this->window->getWindowSize(),
			fvec3(this->window->getWindowSize().x, this->window->getWindowSize().y, 1.0f),
			fvec4(1, 1, 0, 1),
			fvec4(0, 1, 1, 1),
			fvec4(1, 0, 1, 1),
			fvec4(0, 0, 0, 1),
			mat4(1.0f))),
		new vector<IGameObject *>(),
		new MenuGui(&this->clearColor));
}

void Stage::updateGameObjects(float deltaTime)
{
	scenes.at(static_cast<size_t>(currentScene))->updateGameObjects(deltaTime);
}

void Stage::renderCurrentScene(float currentTime)
{
	scenes.at(static_cast<size_t>(currentScene))->renderScene(currentTime);
}

void Stage::changeScene(SceneType nextScene)
{
	this->currentScene = nextScene;
}

void Stage::drawClearColor() const
{
	glClearColor(this->clearColor.x, this->clearColor.y, this->clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Stage::shouldWindowClose()
{
	return this->window->shouldWindowClose();
}

void Stage::swapBuffers()
{
	this->window->swapBuffers();
}

void Stage::pollEvents()
{
	this->window->pollEvents();
}
