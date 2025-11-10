#include "../../Header Files/Game Objects/EnemyExplosion.h"

#include "../../Header Files/Mesh.h"

EnemyExplosion::EnemyExplosion(
	string vertexName,
	string fragmentName,
	Shape shape,
	fvec3 positionTop,
	fvec3 positionBottom,
	float rotationDegreesTop,
	float rotationDegreesBottom,
	fvec3 scaleVector,
	ivec2 windowSize) : windowSize(windowSize)
{
	this->creationTime = static_cast<float>(glfwGetTime());
	this->meshTop = new Mesh(
		vertexName,
		fragmentName,
		shape.first,
		shape.second,
		positionTop,
		rotationDegreesTop,
		scaleVector,
		GL_TRIANGLE_FAN,
		windowSize);
	this->meshBottom = new Mesh(
		vertexName,
		fragmentName,
		shape.first,
		shape.second,
		positionBottom,
		rotationDegreesBottom,
		scaleVector,
		GL_TRIANGLE_FAN,
		windowSize);
}

EnemyExplosion::~EnemyExplosion()
{
	delete this->meshTop;
	delete this->meshBottom;
}

void EnemyExplosion::update(float deltaTime)
{
	float currentTime = static_cast<float>(glfwGetTime());
	float elapsed = currentTime - this->creationTime;
	float t = glm::clamp(elapsed / this->timeToLiveSeconds, 0.0f, 1.0f);

	// Linear interpolation
	float horizontalSpeed = this->maxHorizontalSpeed * (1.0f - t);
	float verticalSpeed = this->maxVerticalSpeed * (1.0f - t);

	this->meshTop->setPosition(this->meshTop->getPosition() + fvec3(-horizontalSpeed * deltaTime, verticalSpeed * deltaTime, 0));
	this->meshBottom->setPosition(this->meshBottom->getPosition() + fvec3(-horizontalSpeed * deltaTime, -verticalSpeed * deltaTime, 0));
}

void EnemyExplosion::render(float currentTime)
{
	this->meshTop->render(currentTime);
	this->meshBottom->render(currentTime);
}

bool EnemyExplosion::shouldDelete()
{
	float currentTime = static_cast<float>(glfwGetTime());
	return (currentTime - this->creationTime) >= this->timeToLiveSeconds;
}
