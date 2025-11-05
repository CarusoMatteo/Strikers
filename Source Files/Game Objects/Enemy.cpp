#include "../../Header Files/Game Objects/Enemy.h"

#include "../../Header Files/ShapeMaker.h"
#include "../../Header Files/MeshBB.h"
#include "../../Header Files/InputEvents.h"

Enemy::Enemy(
	string vertexName,
	string fragmentName,
	Shape shape,
	fvec3 position,
	fvec3 scaleVector,
	ivec2 windowSize) : windowSize(windowSize)
{
	this->mesh = new MeshBB(
		vertexName,
		fragmentName,
		shape.first,
		shape.second,
		position,
		scaleVector,
		GL_TRIANGLE_FAN,
		windowSize,
		fmat4(1));
}

Enemy::~Enemy()
{
	delete this->mesh;
}

void Enemy::update(float deltaTime)
{
	fvec3 oldPosition = this->mesh->getPosition();
	this->mesh->setPosition(fvec3(oldPosition.x - this->speed * deltaTime, oldPosition.y, oldPosition.z));
}

void Enemy::render(float currentTime)
{
	this->mesh->render(currentTime);
}

bool Enemy::shouldDelete()
{
	return this->mesh->getPosition().x < -50;
}