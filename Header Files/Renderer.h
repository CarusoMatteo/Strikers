#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"

using namespace glm;
using std::vector;

class Renderer
{
public:
	static double lastFrameTime;

	static void render(unsigned int shaderProgramId,
					   GLuint projectionMatrixUniformLocation, mat4 *projectionMatrix,
					   GLuint modelMatrixUniformLocation, mat4 *modelMatrix,
					   vec2 resolution,
					   vec3 *scaleVector, float rotationAngleDegrees,
					   GLuint vaoAddress, GLenum renderMode, int numberOfPoints);

private:
	Renderer() = default;
	~Renderer() = default;

	static void renderWithUniforms(unsigned int shaderProgramId,
								   GLuint projectionMatrixUniformLocation, mat4 *projectionMatrix,
								   GLuint modelMatrixUniformLocation, mat4 *modelMatrix,
								   vec2 resolution);

	static void applyTransformaiton(mat4 *modelMatrix, vec3 *scaleVector, float rotationAngleDegrees);

	static void renderWithBoundingBox(GLuint vaoAddress, GLenum renderMode, int numberOfPoints);
};
