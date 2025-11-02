#include "../../Header Files/Game Objects/Heart.h"

Heart::Heart(fvec3 position, MeshBB *mesh) : position(position), mesh(mesh)
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