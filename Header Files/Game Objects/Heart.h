#pragma once
#include "IGameObject.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../Shape.h"

using glm::fvec3;
using glm::fvec4;
using glm::ivec2;
using std::string;
using std::vector;

class MeshBB;

class Heart : public IGameObject
{
public:
	Heart(
		string vertexName,
		string fragmentName,
		Shape shape,
		fvec3 position,
		fvec3 scaleVector,
		ivec2 windowSize);
	~Heart() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	MeshBB *mesh;
};
