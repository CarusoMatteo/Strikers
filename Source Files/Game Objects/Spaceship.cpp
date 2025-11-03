#include "../../Header Files/Game Objects/Spaceship.h"

#include "../../Header Files/MeshBB.h"
#include "../../Header Files/InputEvents.h"

Spaceship::Spaceship()
{
}

Spaceship::~Spaceship()
{
	delete this->mesh;
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

	this->mesh->setPosition(this->mesh->getPosition() + movementDirection * this->speed * deltaTime);
}

void Spaceship::render(float currentTime)
{
	this->mesh->render(currentTime);
}
