#include "../../Header Files/Game Objects/Projectile.h"

#include "../../Header Files/MeshCurveBB.h"
#include "../../Header Files/InputEvents.h"

Projectile::Projectile(
	string vertexName,
	string fragmentName,
	Shape shape,
	fvec3 position,
	fvec3 scaleVector,
	ivec2 windowSize) : windowSize(windowSize)
{
	this->mesh = new MeshCurveBB(
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

Projectile::~Projectile()
{
	delete this->mesh;
}

void Projectile::update(float deltaTime)
{
	this->mesh->setPosition(this->mesh->getPosition() + fvec3(this->speed * deltaTime, 0, 0));
}

void Projectile::render(float currentTime)
{
	this->mesh->render(currentTime);
}

bool Projectile::shouldDelete()
{
	return this->mesh->getPosition().x > static_cast<float>(this->windowSize.x) - 10;
}