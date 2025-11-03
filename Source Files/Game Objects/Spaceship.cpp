#include "../../Header Files/Game Objects/Spaceship.h"

#include "../../Header Files/MeshBB.h"
#include "../../Header Files/InputEvents.h"

Spaceship::Spaceship(
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
		shape.first,
		shape.second,
		position,
		scaleVector,
		GL_TRIANGLE_FAN,
		windowSize,
		fmat4(1));
}

Spaceship::~Spaceship()
{
	delete this->mesh;
}

fvec3 Spaceship::getPosition() const
{
	return mesh ? mesh->getPosition() : fvec3(0.0f);
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
