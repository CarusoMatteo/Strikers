#include "../../Header Files/Game Objects/ProjectileExplosion.h"

#include "../../Header Files/Mesh.h"

ProjectileExplosion::ProjectileExplosion(string vertexName, string fragmentName, Shape shape, fvec3 position, fvec3 scaleVector, ivec2 windowSize)
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
	this->creationTime = static_cast<float>(glfwGetTime());
}

ProjectileExplosion::~ProjectileExplosion()
{
	delete this->mesh;
}

void ProjectileExplosion::update(float deltaTime)
{
	return;
}

void ProjectileExplosion::render(float currentTime)
{
	this->mesh->render(currentTime);
}

bool ProjectileExplosion::shouldDelete()
{
	float currentTime = static_cast<float>(glfwGetTime());
	return (currentTime - this->creationTime) >= this->timeToLiveSeconds;
}
