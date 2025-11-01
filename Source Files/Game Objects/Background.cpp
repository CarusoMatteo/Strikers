#include "../../Header Files/Game Objects/Background.h"

Background::Background(Mesh *mesh) : mesh(mesh)
{
}

void Background::update(float deltaTime)
{
}

void Background::render(float currentTime)
{
	this->mesh->render(currentTime);
}