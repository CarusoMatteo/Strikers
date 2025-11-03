#include "../../Header Files/Game Objects/Heart.h"

#include "../../Header Files/MeshBB.h"

Heart::Heart()
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