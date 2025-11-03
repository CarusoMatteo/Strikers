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
	this->mesh = new MeshBB(
		vertexName,
		fragmentName,
		shape.vertices,
		shape.colors,
		position,
		scaleVector,
		GL_TRIANGLES,
		windowSize,
		fmat4(1));
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