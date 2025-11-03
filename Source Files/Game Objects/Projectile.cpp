#include "../../Header Files/Game Objects/Projectile.h"

#include "../../Header Files/ShapeMaker.h"
#include "../../Header Files/MeshBB.h"
#include "../../Header Files/InputEvents.h"

Projectile::Projectile(
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

bool Projectile::isOffScreen()
{
	return this->mesh->getPosition().x > static_cast<float>(this->windowSize.x) - 10;
}