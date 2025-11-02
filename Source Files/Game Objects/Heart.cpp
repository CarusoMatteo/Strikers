#include "../../Header Files/Game Objects/Heart.h"

Heart::Heart(MeshBB *mesh) : mesh(mesh)
{
}

Heart::~Heart()
{
	delete this->mesh;
}

void Heart::update(float deltaTime)
{
}

void Heart::render(float currentTime)
{
	this->mesh->render(currentTime);
}