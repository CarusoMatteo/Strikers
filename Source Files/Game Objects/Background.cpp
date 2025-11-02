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
}

void Background::render(float currentTime)
{
	this->mesh->render(currentTime);
}