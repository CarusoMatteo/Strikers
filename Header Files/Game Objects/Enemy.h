#pragma once
#include "ITemporaryGameObject.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../Shape.h"
#include "../Parameters.h"

using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class MeshCurveBB;

/**
 * @brief Represents an enemy gameObject in the game.
 * Has a Bounding Box.
 */
class Enemy : public ITemporaryGameObject
{
public:
	Enemy(
		string vertexName,
		string fragmentName,
		Shape shape,
		fvec3 position,
		float rotationDegrees,
		fvec3 scaleVector,
		ivec2 windowSize);
	~Enemy() override;

	MeshCurveBB *getMesh() const
	{
		return this->mesh;
	}
	float getScore() const
	{
		return this->score;
	}

	fvec3 getSizeWorld() const;

	void update(float deltaTime) override;
	void render(float currentTime) override;

	bool shouldDelete() override;

private:
	MeshCurveBB *mesh;
	float speed = Parameters::enemySpeed;
	ivec2 windowSize;
	float score = 100.0f;
};
