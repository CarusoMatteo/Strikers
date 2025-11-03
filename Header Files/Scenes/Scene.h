#pragma once

class Scene
{
public:
	virtual ~Scene() = default;
	virtual void updateGameObjects(float deltaTime) = 0;
	virtual void renderScene(float currentTime) = 0;

protected:
	Scene() = default;
};