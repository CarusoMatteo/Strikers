#include "../../Header Files/Game Objects/Background.h"

#include "../../Header Files/InputEvents.h"

Background::Background(Mesh *mesh) : mesh(mesh)
{
}

Background::~Background()
{
	delete this->mesh;
}

void Background::update(float deltaTime)
{
	this->mesh->updateScreenSize(InputEvents::getCurrentWindowSize());
}

void Background::render(float currentTime)
{
	this->mesh->render(currentTime);
}