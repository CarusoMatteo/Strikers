#include "../../Header Files/Game Objects/Spaceship.h"

#include "../../Header Files/MeshBB.h"
#include "../../Header Files/InputEvents.h"

Spaceship::Spaceship(
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
		windowSize);
}

Spaceship::~Spaceship()
{
	delete this->mesh;
}

fvec3 Spaceship::getPosition() const
{
	return mesh ? mesh->getPosition() : fvec3(0.0f);
}

fvec3 Spaceship::getProjectileSpawnPosition() const
{
	return mesh->getBBRight();
}

void Spaceship::update(float deltaTime)
{
	fvec3 movementDirection = fvec3(0.0f, 0.0f, 0.0f);
	if (InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::MOVE_UP)))
	{
		movementDirection.y += 1.0f;
	}
	if (InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::MOVE_DOWN)))
	{
		movementDirection.y -= 1.0f;
	}
	if (InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::MOVE_LEFT)))
	{
		movementDirection.x -= 1.0f;
	}
	if (InputEvents::getButtonStates()->at(static_cast<size_t>(InputEventsType::MOVE_RIGHT)))
	{
		movementDirection.x += 1.0f;
	}

	if (movementDirection != fvec3(0.0f))
		movementDirection = normalize(movementDirection);

	fvec3 newPosition = this->mesh->getPosition() + movementDirection * this->speed * deltaTime;
	fvec3 clampedPosition = fvec3(
		clamp(newPosition.x, 0.0f, static_cast<float>(this->windowSize.x) + this->mesh->getSizeWorld().x),
		clamp(newPosition.y, 0.0f, static_cast<float>(this->windowSize.y) - this->mesh->getSizeWorld().y),
		newPosition.z);
	this->mesh->setPosition(clampedPosition);

	if (this->isInvincible)
	{
		this->invincibilityTimer -= deltaTime;
		this->mesh->setIsVisible(this->isVisible());
	}

	if (this->invincibilityTimer <= 0)
	{
		this->isInvincible = false;
	}
}

bool Spaceship::isVisible() const
{
	return static_cast<int>(this->invincibilityTimer * this->invincibleBlinkFrequencyHz * 2) % 2 == 0;
}

void Spaceship::render(float currentTime)
{
	this->mesh->render(currentTime);
}

void Spaceship::takeDamage(int amount)
{
	if (this->isInvincible)
		return;

	this->health -= amount;

	this->isInvincible = true;
	this->invincibilityTimer = this->invincibilityTime;
}
