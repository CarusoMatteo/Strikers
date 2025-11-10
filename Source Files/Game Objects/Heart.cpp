#include "../../Header Files/Game Objects/Heart.h"

#include "../../Header Files/MeshBB.h"

Heart::Heart(
	string vertexName,
	string fragmentName,
	Shape shape,
	fvec3 position,
	fvec3 scaleVector,
	ivec2 windowSize)
{
	this->mesh = new Mesh(
		vertexName,
		fragmentName,
		shape.first,
		shape.second,
		position,
		0.0f,
		scaleVector,
		GL_TRIANGLE_FAN,
		windowSize);
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