#pragma once
#include "IGameObject.h"

#include <vector>
#include <glm/glm.hpp>

using glm::vec4;

class Background : public IGameObject
{
public:
	Background(MeshBB *mesh);
	~Background() override;

	void update(float deltaTime) override;
	void render(float currentTime) override;

private:
	MeshBB *mesh;
};