#pragma once

class IScene
{
public:
	virtual ~IScene() = default;
	virtual void updateGameObjects(float deltaTime) = 0;
	virtual void renderScene(float currentTime) = 0;
};