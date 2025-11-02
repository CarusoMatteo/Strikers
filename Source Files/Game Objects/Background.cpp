#include "../../Header Files/Game Objects/Background.h"

Background::Background(MeshBB *mesh) : mesh(mesh)
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