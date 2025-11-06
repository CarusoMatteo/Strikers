#include "../../Header Files/Game Objects/EnemyExplosion.h"

#include "../../Header Files/Mesh.h"

EnemyExplosion::EnemyExplosion(string vertexName, string fragmentName, Shape shape, fvec3 position, fvec3 scaleVector, ivec2 windowSize)
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

EnemyExplosion::~EnemyExplosion()
{
	delete this->mesh;
}

void EnemyExplosion::update(float deltaTime)
{
	return;
}

void EnemyExplosion::render(float currentTime)
{
	this->mesh->render(currentTime);
}

bool EnemyExplosion::shouldDelete()
{
	float currentTime = static_cast<float>(glfwGetTime());
	return (currentTime - this->creationTime) >= this->timeToLiveSeconds;
}
