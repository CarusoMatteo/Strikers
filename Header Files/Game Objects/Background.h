#pragma once
#include "IGameObject.h"

#include <vector>
#include <glm/glm.hpp>

#include "../InputEvents.h"

using glm::fvec4;

class Background : public IGameObject
{
public:
	Background(Mesh *mesh);
	~Background() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	Mesh *mesh;
};