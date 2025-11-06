#include "../../Header Files/Game Objects/Background.h"

#include "../../Header Files/ShapeMaker.h"
#include "../../Header Files/Mesh.h"
#include "../../Header Files/InputEvents.h"

Background::Background(
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
		scaleVector,
		GL_TRIANGLE_FAN,
		windowSize);
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