#pragma once

#include <vector>
#include <glm/glm.hpp>

using glm::mat4;
using glm::vec2;
using std::vector;

class Renderer
{
public:
	static double lastFrameTime;
	static void renderWithUniforms(unsigned int shaderProgramId, mat4 projectionMatrix, mat4 modelMatrix, float currentTime, vec2 resolution);

private:
	Renderer() = default;
	~Renderer() = default;
};
