#pragma once
#include "ITemporaryGameObject.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../Shape.h"

using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class MeshCurveBB;

/**
 * @brief Represents a projectile gameObject in the game.
 * Has a Bounding Box.
 */
class Projectile : public ITemporaryGameObject
{
public:
	Projectile(
		string vertexName,
		string fragmentName,
		Shape shape,
		fvec3 position,
		fvec3 scaleVector,
		ivec2 windowSize);
	~Projectile() override;

	MeshCurveBB *getMesh() const
	{
		return this->mesh;
	}

	void update(float deltaTime) override;
	void render(float currentTime) override;
	bool shouldDelete() override;

private:
	MeshCurveBB *mesh;
	float speed = 2500.0f;
	ivec2 windowSize;
};
